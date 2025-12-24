#pragma once

// #using <MySql.Data.dll>  <-- removed: don't rely on a hardcoded #using unless the DLL is placed where the compiler searches.
// Make sure the project has a reference to the MySql.Data assembly (preferred via NuGet):
//   Install-Package MySql.Data
// or add a Project Reference: Project -> Add Reference -> Browse -> MySql.Data.dll

namespace SIS {
    using namespace System;
    using namespace System::Collections::Generic;
    using namespace MySql::Data::MySqlClient;

    public ref class DataManager sealed
    {
    private:
        static String^ connStr = "";

        inline static MySqlConnection^ OpenConn()
        {
            array<String^>^ connectionAttempts = {
                connStr, // 1. Current (with AllowPublicKeyRetrieval and UseSSL=false)
                connStr->Replace("UseSSL=false", "SslMode=None"), // 2. Try SslMode=None
                connStr->Replace(";UseSSL=false", "")->Replace(";AllowPublicKeyRetrieval=True", ""), // 3. Basic connection
                connStr->Replace("UseSSL=false", "SslMode=0") // 4. Numeric SslMode
            };

            Exception^ lastEx = nullptr;
            for each (String^ attemptStr in connectionAttempts) {
                try {
                    MySqlConnection^ c = gcnew MySqlConnection(attemptStr);
                    c->Open();
                    return c;
                }
                catch (Exception^ ex) {
                    lastEx = ex;
                    // If it's a "Requested value not found" error, continue to next attempt
                    if (ex->Message->Contains("Requested value") || ex->Message->Contains("SslMode")) {
                        continue;
                    }
                    // If it's a database missing error, we handle that specifically
                    if (ex->Message->Contains("Unknown database")) {
                        try {
                            array<String^>^ parts = attemptStr->Split(';');
                            String^ baseConn = "";
                            String^ dbName = "";
                            for each (String^ p in parts) {
                                if (p->StartsWith("Database=")) dbName = p->Substring(9);
                                else if (!String::IsNullOrEmpty(p)) baseConn += p + ";";
                            }
                            MySqlConnection^ cBase = gcnew MySqlConnection(baseConn);
                            cBase->Open();
                            (gcnew MySqlCommand("CREATE DATABASE IF NOT EXISTS " + dbName, cBase))->ExecuteNonQuery();
                            cBase->Close();
                            
                            MySqlConnection^ cFinal = gcnew MySqlConnection(attemptStr);
                            cFinal->Open();
                            return cFinal;
                        } catch (...) { /* ignore and try next attempt string */ }
                    }
                    // For other errors (like Access Denied), we might want to try the next attempt too
                }
            }
            throw lastEx;
        }

    public:
        inline static void Configure(
            String^ host,
            String^ user,
            String^ pass,
            String^ db,
            int port
        )
        {
            connStr =
                "Server=" + host +
                ";Port=" + port.ToString() +
                ";Database=" + db +
                ";Uid=" + user +
                ";Pwd=" + pass + ";AllowUserVariables=True;AllowPublicKeyRetrieval=True;UseSSL=false;";
        }

        // Add this method to test the configured connection quickly
        inline static bool TestConnection()
        {
            try {
                auto c = OpenConn();
                c->Close();
                return true;
            }
            catch (...) {
                return false;
            }
        }

        // Ensures the database schema exists without dropping data.
        inline static void EnsureDatabaseInitialized()
        {
            try {
                auto c = OpenConn();

                // Check if the database is already populated
                bool isPopulated = false;
                try {
                    auto checkCmd = gcnew MySqlCommand("SELECT COUNT(*) FROM faculties", c);
                    int count = Convert::ToInt32(checkCmd->ExecuteScalar());
                    if (count > 0) isPopulated = true;
                }
                catch (...) {
                    isPopulated = false; // Tables probably don't exist
                }

                // If not populated, try to load from uni.sql first
                if (!isPopulated) {
                    String^ exePath = System::IO::Path::GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location);
                    String^ sqlPath = System::IO::Path::Combine(exePath, "uni.sql");
                    
                    // Also check project root (for development)
                    if (!System::IO::File::Exists(sqlPath)) {
                        sqlPath = "uni.sql"; 
                    }

                    if (System::IO::File::Exists(sqlPath)) {
                        String^ scriptText = System::IO::File::ReadAllText(sqlPath);
                        // MySqlScript can handle multiple statements and standard SQL dumps
                        MySqlScript^ script = gcnew MySqlScript(c, scriptText);
                        script->Execute();
                        c->Close();
                        return; // Successfully initialized from uni.sql
                    }
                }

                // Fallback to hardcoded schema if uni.sql is missing or DB already has data
                array<String^>^ queries = {
                    // 1. Academic Structure
                    "CREATE TABLE IF NOT EXISTS faculties ( faculty_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, faculty_code VARCHAR(10), faculty_name VARCHAR(100) NOT NULL ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS departments ( department_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, department_code VARCHAR(10), department_name VARCHAR(100) NOT NULL, faculty_id INT ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS academic_levels ( level_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, level_name VARCHAR(50) NOT NULL ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS academic_years ( academic_year_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, year_name VARCHAR(20), start_date DATE, end_date DATE ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS semesters ( semester_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, semester_name VARCHAR(20), start_date DATE, end_date DATE, academic_year_id INT ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS academic_calendar ( calendar_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, academic_year_id INT, semester_id INT, event_title VARCHAR(100), event_type VARCHAR(50), start_date DATE, end_date DATE ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    
                    // 2. People & Auth
                    "CREATE TABLE IF NOT EXISTS system_user ( user_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, username VARCHAR(100) UNIQUE, password_hash VARCHAR(255), user_type VARCHAR(20) ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS administration_users ( admin_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, full_name VARCHAR(100) NOT NULL, email VARCHAR(100) NOT NULL, role VARCHAR(50) ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS instructors ( instructor_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, full_name VARCHAR(100), instructor_type VARCHAR(20), specialization VARCHAR(50), email VARCHAR(100), phone VARCHAR(15), faculty_id INT, department_id INT, hire_date DATE ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS students ( student_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, full_name VARCHAR(100), national_id VARCHAR(20), email VARCHAR(100), phone VARCHAR(15), academic_year_id INT, semester_id INT, academic_level_id INT, faculty_id INT, department_id INT, group_number VARCHAR(10), section_number VARCHAR(10), enrollment_date DATE, GPA DECIMAL(3,2), final_grade VARCHAR(2) ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    
                    // 3. Courses
                    "CREATE TABLE IF NOT EXISTS courses ( course_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, course_code VARCHAR(10), course_name VARCHAR(100), description TEXT, course_type VARCHAR(50), max_degree INT, credit_hours DECIMAL(3,1) ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS student_course_enrollment ( student_course_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, student_id INT, course_id INT, academic_year_id INT, semester_id INT, enrollment_date DATE ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS instructor_course_assignment ( id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, instructor_id INT, course_id INT, academic_year_id INT, semester_id INT ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    
                    // 4. Academic Activities
                    "CREATE TABLE IF NOT EXISTS lecture_halls ( hall_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, product_id VARCHAR(20), hall_name VARCHAR(100) NOT NULL, description TEXT, capacity INT, seats INT, air_conditioning_units INT, fans INT, lighting_units INT ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS laboratories ( lab_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, product_id VARCHAR(20), lab_name VARCHAR(100) NOT NULL, description TEXT, capacity INT, computers_count INT, seats INT, air_conditioning_units INT, fans INT, lighting_units INT ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS locations ( location_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, location_type VARCHAR(10) NOT NULL, hall_id INT, lab_id INT ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS academic_schedule ( schedule_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, course_id INT, instructor_id INT, academic_year_id INT, semester_id INT, location_id INT, day_of_week VARCHAR(10) NOT NULL, start_time TIME NOT NULL, end_time TIME NOT NULL, group_number VARCHAR(10), section_number VARCHAR(10) ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS attendance ( attendance_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, student_id INT, course_id INT, semester_id INT, lecture_date DATE, status VARCHAR(10) ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS grades ( grade_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, student_id INT, course_id INT, semester_id INT, assignment1 DECIMAL(5,2), assignment2 DECIMAL(5,2), coursework DECIMAL(5,2), final_exam DECIMAL(5,2), total_score DECIMAL(5,2), grade_evaluation VARCHAR(2) ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    
                    // 5. Fees & News
                    "CREATE TABLE IF NOT EXISTS fees ( fee_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, student_id INT, academic_year_id INT, semester_id INT, total_amount DECIMAL(10,2), paid_amount DECIMAL(10,2), payment_date DATE, payment_status VARCHAR(50) ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;",
                    "CREATE TABLE IF NOT EXISTS news ( news_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, title VARCHAR(200), description TEXT, posted_by_user_id INT, post_date DATE, visible_to VARCHAR(50) ) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;"
                };

                for each (String^ q in queries) {
                    auto cmd = gcnew MySqlCommand(q, c);
                    cmd->ExecuteNonQuery();
                }
                c->Close();
                InsertInitialData();
            }
            catch (Exception^ ex) {
                throw ex; // Re-throw to allow caller (LoginForm) to handle connection issues
            }
        }

        // Insert initial data for faculties, departments, and a default admin user
        inline static void InsertInitialData() {
            try {
                auto c = OpenConn();
                
                // 1. Faculties
                if (Convert::ToInt32((gcnew MySqlCommand("SELECT COUNT(*) FROM faculties", c))->ExecuteScalar()) == 0) {
                    array<String^>^ queries = {
                        "INSERT INTO faculties (faculty_id, faculty_code, faculty_name) VALUES (1, 'CS', 'Faculty of Computer Science');",
                        "INSERT INTO faculties (faculty_id, faculty_code, faculty_name) VALUES (2, 'IT', 'Faculty of Information Technology');",
                        "INSERT INTO faculties (faculty_id, faculty_code, faculty_name) VALUES (3, 'ENG', 'Faculty of Engineering');",
                        "INSERT INTO faculties (faculty_id, faculty_code, faculty_name) VALUES (4, 'AI', 'Faculty of Artificial Intelligence');",
                        "INSERT INTO faculties (faculty_id, faculty_code, faculty_name) VALUES (5, 'BIS', 'Faculty of Business Information Systems');"
                    };
                    for each (String^ q in queries) (gcnew MySqlCommand(q, c))->ExecuteNonQuery();
                }


                // 2. Departments
                if (Convert::ToInt32((gcnew MySqlCommand("SELECT COUNT(*) FROM departments", c))->ExecuteScalar()) == 0) {
                    array<String^>^ queries = {
                        "INSERT INTO departments (department_id, department_code, department_name, faculty_id) VALUES (1, 'CS-SE', 'Software Engineering', 1);",
                        "INSERT INTO departments (department_id, department_code, department_name, faculty_id) VALUES (2, 'CS-DS', 'Data Science', 1);",
                        "INSERT INTO departments (department_id, department_code, department_name, faculty_id) VALUES (3, 'CS-IS', 'Information Systems', 1);",
                        "INSERT INTO departments (department_id, department_code, department_name, faculty_id) VALUES (4, 'IT-NET', 'Computer Networks', 2);",
                        "INSERT INTO departments (department_id, department_code, department_name, faculty_id) VALUES (5, 'IT-SEC', 'Cyber Security', 2);",
                        "INSERT INTO departments (department_id, department_code, department_name, faculty_id) VALUES (7, 'ENG-COM', 'Computer Engineering', 3);",
                        "INSERT INTO departments (department_id, department_code, department_name, faculty_id) VALUES (10, 'AI-ML', 'Machine Learning', 4);",
                        "INSERT INTO departments (department_id, department_code, department_name, faculty_id) VALUES (13, 'BIS-MIS', 'Management Information Systems', 5);"
                    };
                    for each (String^ q in queries) (gcnew MySqlCommand(q, c))->ExecuteNonQuery();
                }

                // 3. Academic Levels
                if (Convert::ToInt32((gcnew MySqlCommand("SELECT COUNT(*) FROM academic_levels", c))->ExecuteScalar()) == 0) {
                    array<String^>^ queries = {
                        "INSERT INTO academic_levels (level_id, level_name) VALUES (1, 'Level 1');",
                        "INSERT INTO academic_levels (level_id, level_name) VALUES (2, 'Level 2');",
                        "INSERT INTO academic_levels (level_id, level_name) VALUES (3, 'Level 3');",
                        "INSERT INTO academic_levels (level_id, level_name) VALUES (4, 'Level 4');",
                        "INSERT INTO academic_levels (level_id, level_name) VALUES (5, 'Graduate');",
                        "INSERT INTO academic_levels (level_id, level_name) VALUES (6, 'Postgraduate');"
                    };
                    for each (String^ q in queries) (gcnew MySqlCommand(q, c))->ExecuteNonQuery();
                }

                // 4. Academic Years
                if (Convert::ToInt32((gcnew MySqlCommand("SELECT COUNT(*) FROM academic_years", c))->ExecuteScalar()) == 0) {
                    array<String^>^ queries = {
                        "INSERT INTO academic_years (academic_year_id, year_name, start_date, end_date) VALUES (1, '2021/2022', '2021-09-01', '2022-06-30');",
                        "INSERT INTO academic_years (academic_year_id, year_name, start_date, end_date) VALUES (2, '2022/2023', '2022-09-01', '2023-06-30');",
                        "INSERT INTO academic_years (academic_year_id, year_name, start_date, end_date) VALUES (3, '2023/2024', '2023-09-01', '2024-06-30');",
                        "INSERT INTO academic_years (academic_year_id, year_name, start_date, end_date) VALUES (4, '2024/2025', '2024-09-01', '2025-06-30');",
                        "INSERT INTO academic_years (academic_year_id, year_name, start_date, end_date) VALUES (5, '2025/2026', '2025-09-01', '2026-06-30');"
                    };
                    for each (String^ q in queries) (gcnew MySqlCommand(q, c))->ExecuteNonQuery();
                }

                // 5. Semesters
                if (Convert::ToInt32((gcnew MySqlCommand("SELECT COUNT(*) FROM semesters", c))->ExecuteScalar()) == 0) {
                    array<String^>^ queries = {
                        "INSERT INTO semesters (semester_id, semester_name, academic_year_id) VALUES (1, 'First Semester 2021', 1);",
                        "INSERT INTO semesters (semester_id, semester_name, academic_year_id) VALUES (2, 'Second Semester 2022', 1);",
                        "INSERT INTO semesters (semester_id, semester_name, academic_year_id) VALUES (3, 'First Semester 2022', 2);",
                        "INSERT INTO semesters (semester_id, semester_name, academic_year_id) VALUES (4, 'Second Semester 2023', 2);"
                    };
                    for each (String^ q in queries) (gcnew MySqlCommand(q, c))->ExecuteNonQuery();
                }

                // 6. Default Users
                if (Convert::ToInt32((gcnew MySqlCommand("SELECT COUNT(*) FROM system_user", c))->ExecuteScalar()) == 0) {
                    array<String^>^ queries = {
                        "INSERT INTO system_user (user_id, username, password_hash, user_type) VALUES (1, 'admin', '" + HashPassword("admin123") + "', 'Admin');",
                        "INSERT INTO system_user (user_id, username, password_hash, user_type) VALUES (2, 'omar', '" + HashPassword("omar123") + "', 'Student');",
                        "INSERT INTO system_user (user_id, username, password_hash, user_type) VALUES (3, 'ahmed', '" + HashPassword("ahmed123") + "', 'Student');",
                        "INSERT INTO system_user (user_id, username, password_hash, user_type) VALUES (4, 'mohamed', '" + HashPassword("mohamed123") + "', 'Instructor');",
                        "INSERT INTO system_user (user_id, username, password_hash, user_type) VALUES (5, 'sara', '" + HashPassword("sara123") + "', 'Student');"
                    };
                    for each (String^ q in queries) (gcnew MySqlCommand(q, c))->ExecuteNonQuery();
                }

                // 7. Sample Students
                if (Convert::ToInt32((gcnew MySqlCommand("SELECT COUNT(*) FROM students", c))->ExecuteScalar()) == 0) {
                    array<String^>^ queries = {
                        "INSERT INTO students (student_id, full_name, national_id, email, phone, academic_year_id, semester_id, academic_level_id, faculty_id, department_id, group_number, section_number, enrollment_date, GPA, final_grade) VALUES (1, 'Ahmed Hassan Ali', '30101010000001', 'ahmed1@gmail.com', '01010000001', 1, 1, 1, 1, 1, '1', '1', '2021-09-15', 3.10, 'B');",
                        "INSERT INTO students (student_id, full_name, national_id, email, phone, academic_year_id, semester_id, academic_level_id, faculty_id, department_id, group_number, section_number, enrollment_date, GPA, final_grade) VALUES (4, 'Omar Yasser Khidr', '30101010000003', 'omar1@gmail.com', '01010000003', 1, 2, 1, 2, 4, '2', '1', '2021-09-15', 3.80, 'A');"
                    };
                    for each (String^ q in queries) (gcnew MySqlCommand(q, c))->ExecuteNonQuery();
                }

                c->Close();
            }
            catch (Exception^) {
                // throw;
            }
        }

        // User class to represent system users
        ref class User
        {
        public:
            property int UserId;
            property String^ UserName;
            property String^ UserType;
            
            User(int id, String^ name, String^ type) {
                UserId = id;
                UserName = name;
                UserType = type;
            }
        };

        inline static int GetStudentIdByUserId(int userId) {
            try {
                auto c = OpenConn();
                // Since uni.sql doesn't have user_id in students, we look for matching email or name if possible,
                // but for now we fallback to returning the userId itself if it exists in students.
                auto cmd = gcnew MySqlCommand("SELECT student_id FROM students WHERE student_id=@uid", c);
                cmd->Parameters->AddWithValue("@uid", userId);
                auto val = cmd->ExecuteScalar();
                c->Close();
                return (val != nullptr) ? Convert::ToInt32(val) : userId;
            } catch(...) { return userId; }
        }

        inline static String^ GetStudentDetails(int sid) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT s.full_name, s.email, s.phone, s.national_id, f.faculty_name, d.department_name, l.level_name "
                    "FROM students s "
                    "JOIN faculties f ON s.faculty_id = f.faculty_id "
                    "JOIN departments d ON s.department_id = d.department_id "
                    "JOIN academic_levels l ON s.academic_level_id = l.level_id "
                    "WHERE s.student_id = @sid", c);
                cmd->Parameters->AddWithValue("@sid", sid);
                auto r = cmd->ExecuteReader();
                String^ result = nullptr;
                if (r->Read()) {
                    result = r["full_name"]->ToString() + "|" + 
                             r["email"]->ToString() + "|" + 
                             r["phone"]->ToString() + "|" + 
                             r["national_id"]->ToString() + "|" + 
                             r["faculty_name"]->ToString() + "|" + 
                             r["department_name"]->ToString() + "|" + 
                             r["level_name"]->ToString();
                }
                r->Close(); c->Close();
                return result;
            } catch(...) { return nullptr; }
        }

        inline static int GetInstructorIdByUserId(int userId) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT instructor_id FROM instructors WHERE instructor_id=@uid", c);
                cmd->Parameters->AddWithValue("@uid", userId);
                auto val = cmd->ExecuteScalar();
                c->Close();
                return (val != nullptr) ? Convert::ToInt32(val) : userId;
            } catch(...) { return userId; }
        }

        // Authentication - Simplified login using system_user table
        inline static String^ Login(String^ username, String^ password)
        {
            String^ hashedPassword = HashPassword(password);
            try {
                auto c = OpenConn();
                
                // First, check if there are any users at all
                auto cmdCount = gcnew MySqlCommand("SELECT COUNT(*) FROM system_user", c);
                int count = Convert::ToInt32(cmdCount->ExecuteScalar());
                if (count == 0) {
                    c->Close();
                    throw gcnew Exception("No users found in database. Please restart the application to initialize default data.");
                }

                String^ query = "SELECT user_id, user_type FROM system_user WHERE username=@u AND password_hash=@p";
                
                auto cmd = gcnew MySqlCommand(query, c);
                cmd->Parameters->AddWithValue("@u", username);
                cmd->Parameters->AddWithValue("@p", hashedPassword);
                
                auto r = cmd->ExecuteReader();
                String^ result = nullptr;
                if (r->Read()) {
                    result = r["user_id"]->ToString() + "|" + r["user_type"]->ToString();
                }
                r->Close();

                // FALLBACK: If login failed, check if the user exists with a plaintext password
                // This handles cases where the user manually inserted 'pass' or 'admin' into the DB
                if (result == nullptr) {
                    auto cmdFallback = gcnew MySqlCommand("SELECT user_id, user_type FROM system_user WHERE username=@u AND password_hash=@p_raw", c);
                    cmdFallback->Parameters->AddWithValue("@u", username);
                    cmdFallback->Parameters->AddWithValue("@p_raw", password);
                    auto r2 = cmdFallback->ExecuteReader();
                    if (r2->Read()) {
                        result = r2["user_id"]->ToString() + "|" + r2["user_type"]->ToString();
                    }
                    r2->Close();
                }

                c->Close();
                return result;
            }
            catch (Exception^) { 
                throw; 
            }
        }

        // Students
        inline static bool AddStudent(int sid, String^ user, String^ pass, String^ fullName, String^ email, String^ phone, String^ nationalId, int deptId, int facultyId, int levelId, int yearId, int semId, String^ groupNum, String^ sectionNum)
        {
            try {
                auto c = OpenConn();
                auto trans = c->BeginTransaction();
                try {
                    // 1. Insert into system_user - force user_id to match sid
                    String^ hashedPassword = HashPassword(pass);
                    auto cmdUser = gcnew MySqlCommand(
                        "INSERT INTO system_user(user_id, username, password_hash, user_type) VALUES(@sid, @u, @p, 'Student')", c, trans);
                    cmdUser->Parameters->AddWithValue("@sid", sid);
                    cmdUser->Parameters->AddWithValue("@u", user);
                    cmdUser->Parameters->AddWithValue("@p", hashedPassword);
                    cmdUser->ExecuteNonQuery();

                    // 2. Insert into students
                    auto cmdStudent = gcnew MySqlCommand(
                        "INSERT INTO students(student_id, full_name, national_id, email, phone, academic_year_id, semester_id, academic_level_id, faculty_id, department_id, group_number, section_number, enrollment_date) "
                        "VALUES(@sid, @fn, @nid, @e, @ph, @y, @s, @l, @f, @d, @gn, @sn, CURRENT_DATE)", c, trans);
                    cmdStudent->Parameters->AddWithValue("@sid", sid);
                    cmdStudent->Parameters->AddWithValue("@fn", fullName);
                    cmdStudent->Parameters->AddWithValue("@nid", nationalId);
                    cmdStudent->Parameters->AddWithValue("@e", email);
                    cmdStudent->Parameters->AddWithValue("@ph", phone);
                    cmdStudent->Parameters->AddWithValue("@y", yearId);
                    cmdStudent->Parameters->AddWithValue("@s", semId);
                    cmdStudent->Parameters->AddWithValue("@l", levelId);
                    cmdStudent->Parameters->AddWithValue("@f", facultyId);
                    cmdStudent->Parameters->AddWithValue("@d", deptId);
                    cmdStudent->Parameters->AddWithValue("@gn", groupNum);
                    cmdStudent->Parameters->AddWithValue("@sn", sectionNum);
                    cmdStudent->ExecuteNonQuery();

                    trans->Commit();
                    c->Close();
                    return true;
                }
                catch (Exception^ ex) {
                    trans->Rollback();
                    c->Close();
                    throw ex;
                }
            }
            catch (Exception^ ex) { throw ex; }
        }

        inline static bool UpdateStudent(int id, String^ fullName, String^ email, String^ phone, String^ nationalId, int deptId, int facultyId, int levelId, int yearId, int semId, String^ groupNum, String^ sectionNum)
        {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "UPDATE students SET full_name=@fn, email=@e, phone=@ph, national_id=@nid, department_id=@d, faculty_id=@f, academic_level_id=@l, academic_year_id=@y, semester_id=@s, group_number=@gn, section_number=@sn "
                    "WHERE student_id=@id", c);
                cmd->Parameters->AddWithValue("@id", id);
                cmd->Parameters->AddWithValue("@fn", fullName);
                cmd->Parameters->AddWithValue("@e", email);
                cmd->Parameters->AddWithValue("@ph", phone);
                cmd->Parameters->AddWithValue("@nid", nationalId);
                cmd->Parameters->AddWithValue("@d", deptId);
                cmd->Parameters->AddWithValue("@f", facultyId);
                cmd->Parameters->AddWithValue("@l", levelId);
                cmd->Parameters->AddWithValue("@y", yearId);
                cmd->Parameters->AddWithValue("@s", semId);
                cmd->Parameters->AddWithValue("@gn", groupNum);
                cmd->Parameters->AddWithValue("@sn", sectionNum);

                int rows = cmd->ExecuteNonQuery();
                c->Close();
                return rows > 0;
            }
            catch (Exception^ ex) { throw ex; }
        }

        inline static bool DeleteStudent(int id)
        {
            try {
                auto c = OpenConn();
                // Delete from both tables since they share the same ID
                auto cmdDelStudent = gcnew MySqlCommand("DELETE FROM students WHERE student_id=@id", c);
                cmdDelStudent->Parameters->AddWithValue("@id", id);
                cmdDelStudent->ExecuteNonQuery();

                auto cmdDelUser = gcnew MySqlCommand("DELETE FROM system_user WHERE user_id=@id", c);
                cmdDelUser->Parameters->AddWithValue("@id", id);
                cmdDelUser->ExecuteNonQuery();

                c->Close();
                return true;
            }
            catch (Exception^) { return false; }
        }

        inline static List<String^>^ ReadAllStudents()
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT s.student_id, s.full_name, s.email, d.department_name, s.phone, s.national_id FROM students s "
                    "LEFT JOIN departments d ON s.department_id = d.department_id ORDER BY s.student_id", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(
                        r["student_id"]->ToString() + "," + r["full_name"]->ToString() + "," +
                        r["email"]->ToString() + "," + (r["department_name"] == DBNull::Value ? "N/A" : r["department_name"]->ToString()) + "," +
                        r["phone"]->ToString() + "," + r["national_id"]->ToString());
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        inline static String^ GetStudentById(int id)
        {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT s.*, d.department_name FROM students s "
                    "LEFT JOIN departments d ON s.department_id = d.department_id WHERE s.student_id=@id LIMIT 1", c);
                cmd->Parameters->AddWithValue("@id", id);
                auto r = cmd->ExecuteReader();
                String^ out = "";
                if (r->Read()) {
                    auto SafeString = [](Object^ obj) { return (obj == nullptr || obj == DBNull::Value) ? "" : obj->ToString(); };
                    out = SafeString(r["student_id"]) + "|" + SafeString(r["full_name"]) + "|" +
                        SafeString(r["email"]) + "|" + SafeString(r["phone"]) + "|" + 
                        SafeString(r["national_id"]) + "|" + SafeString(r["department_id"]) + "|" +
                        SafeString(r["faculty_id"]) + "|" + SafeString(r["academic_level_id"]) + "|" +
                        SafeString(r["academic_year_id"]) + "|" + SafeString(r["semester_id"]) + "|" +
                        SafeString(r["group_number"]) + "|" + SafeString(r["section_number"]);
                }
                r->Close(); c->Close();
                return out;
            }
            catch (Exception^) { return String::Empty; }
        }

        // Professors (using instructors table)
        inline static bool AddProfessor(int profId, String^ username, String^ password, String^ fullName, String^ email, String^ phone, String^ specialization, int deptId, int facultyId) {
            try {
                auto c = OpenConn();
                auto trans = c->BeginTransaction();
                try {
                    // 1. Insert into system_user - force user_id to match profId
                    String^ hashedPassword = HashPassword(password);
                    auto cmdUser = gcnew MySqlCommand(
                        "INSERT INTO system_user(user_id, username, password_hash, user_type) VALUES(@pid, @u, @p, 'Instructor')", c, trans);
                    cmdUser->Parameters->AddWithValue("@pid", profId);
                    cmdUser->Parameters->AddWithValue("@u", username);
                    cmdUser->Parameters->AddWithValue("@p", hashedPassword);
                    cmdUser->ExecuteNonQuery();

                    // 2. Insert into instructors
                    auto cmdProf = gcnew MySqlCommand(
                        "INSERT INTO instructors(instructor_id, full_name, email, phone, specialization, faculty_id, department_id, hire_date) "
                        "VALUES(@pid, @fn, @e, @ph, @s, @f, @d, CURRENT_DATE)", c, trans);
                    cmdProf->Parameters->AddWithValue("@pid", profId);
                    cmdProf->Parameters->AddWithValue("@fn", fullName);
                    cmdProf->Parameters->AddWithValue("@e", email);
                    cmdProf->Parameters->AddWithValue("@ph", phone);
                    cmdProf->Parameters->AddWithValue("@s", specialization);
                    cmdProf->Parameters->AddWithValue("@f", facultyId);
                    cmdProf->Parameters->AddWithValue("@d", deptId);
                    cmdProf->ExecuteNonQuery();

                    trans->Commit();
                    c->Close();
                    return true;
                }
                catch (Exception^) {
                    trans->Rollback();
                    throw;
                }
            }
            catch (Exception^) { throw; }
        }

        inline static bool UpdateProfessor(int profId, String^ fullName, String^ email, String^ phone, String^ specialization, int deptId, int facultyId) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "UPDATE instructors SET full_name=@fn, email=@e, phone=@ph, specialization=@s, faculty_id=@f, department_id=@d WHERE instructor_id=@pid", c);
                cmd->Parameters->AddWithValue("@pid", profId);
                cmd->Parameters->AddWithValue("@fn", fullName);
                cmd->Parameters->AddWithValue("@e", email);
                cmd->Parameters->AddWithValue("@ph", phone);
                cmd->Parameters->AddWithValue("@s", specialization);
                cmd->Parameters->AddWithValue("@f", facultyId);
                cmd->Parameters->AddWithValue("@d", deptId);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            }
            catch (Exception^) { throw; }
        }

        inline static bool DeleteProfessor(int profId) {
            try {
                auto c = OpenConn();
                // Delete from both tables since they share the same ID
                auto cmdDelProf = gcnew MySqlCommand("DELETE FROM instructors WHERE instructor_id=@pid", c);
                cmdDelProf->Parameters->AddWithValue("@pid", profId);
                cmdDelProf->ExecuteNonQuery();

                auto cmdDelUser = gcnew MySqlCommand("DELETE FROM system_user WHERE user_id=@pid", c);
                cmdDelUser->Parameters->AddWithValue("@pid", profId);
                cmdDelUser->ExecuteNonQuery();

                c->Close();
                return true;
            }
            catch (Exception^) { return false; }
        }

        inline static List<String^>^ ReadAllProfessors() {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT i.instructor_id, i.full_name, i.email, d.department_name FROM instructors i "
                    "LEFT JOIN departments d ON i.department_id = d.department_id ORDER BY i.instructor_id", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(
                        r["instructor_id"]->ToString() + "," + r["full_name"]->ToString() + "," +
                        r["email"]->ToString() + "," + (r["department_name"] == DBNull::Value ? "N/A" : r["department_name"]->ToString()));
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        inline static String^ GetProfessorById(int id) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT i.*, d.department_name FROM instructors i "
                    "LEFT JOIN departments d ON i.department_id = d.department_id WHERE i.instructor_id=@id LIMIT 1", c);
                cmd->Parameters->AddWithValue("@id", id);
                auto r = cmd->ExecuteReader();
                String^ out = "";
                if (r->Read()) {
                    out = r["instructor_id"]->ToString() + "|" + r["full_name"]->ToString() + "|" +
                        r["email"]->ToString() + "|" + r["phone"]->ToString() + "|" + 
                        r["specialization"]->ToString() + "|" + r["department_id"]->ToString() + "|" +
                        r["faculty_id"]->ToString();
                }
                r->Close(); c->Close();
                return out;
            }
            catch (Exception^) { return String::Empty; }
        }

        // Payments (Fees in uni.sql)
        inline static bool AddPayment(int sid, int semId, double paidAmount, double totalAmount, String^ status)
        {
            try {
                auto c = OpenConn();
                
                // Fetch academic_year_id from semesters table
                int yearId = 1; // Default
                auto cmdYear = gcnew MySqlCommand("SELECT academic_year_id FROM semesters WHERE semester_id=@sem", c);
                cmdYear->Parameters->AddWithValue("@sem", semId);
                auto val = cmdYear->ExecuteScalar();
                if (val != nullptr) yearId = Convert::ToInt32(val);

                auto cmd = gcnew MySqlCommand(
                    "INSERT INTO fees(student_id, academic_year_id, semester_id, total_amount, paid_amount, payment_date, payment_status) "
                     "VALUES(@s,@y,@sem,@t,@a,CURRENT_DATE,@st)", c);
                cmd->Parameters->AddWithValue("@s", sid);
                cmd->Parameters->AddWithValue("@y", yearId);
                cmd->Parameters->AddWithValue("@sem", semId);
                cmd->Parameters->AddWithValue("@t", totalAmount);
                cmd->Parameters->AddWithValue("@a", paidAmount);
                cmd->Parameters->AddWithValue("@st", status);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            }
            catch (Exception^) { throw; }
        }

        inline static List<String^>^ ReadAllPayments()
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT student_id, academic_year_id, semester_id, total_amount, paid_amount, payment_date, payment_status FROM fees ORDER BY fee_id", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(
                        r["student_id"]->ToString() + "," + 
                        r["academic_year_id"]->ToString() + "," + 
                        r["semester_id"]->ToString() + "," +
                        r["total_amount"]->ToString() + "," + 
                        r["paid_amount"]->ToString() + "," + 
                        r["payment_date"]->ToString() + "," +
                        r["payment_status"]->ToString());
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        inline static bool CanRegisterCourses(int sid, int semId)
        {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT COUNT(*) FROM fees WHERE student_id=@s", c);
                cmd->Parameters->AddWithValue("@s", sid);
                int count = Convert::ToInt32(cmd->ExecuteScalar());
                c->Close();
                return count > 0;
            }
            catch (Exception^) { return false; }
        }

        // Courses
        inline static bool AddCourse(String^ code, String^ name, String^ desc, String^ type, int maxDegree, double credits)
        {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "INSERT INTO courses(course_code, course_name, description, course_type, max_degree, credit_hours) "
                    "VALUES(@c, @n, @d, @t, @m, @cr)", c);
                cmd->Parameters->AddWithValue("@c", code);
                cmd->Parameters->AddWithValue("@n", name);
                cmd->Parameters->AddWithValue("@d", desc);
                cmd->Parameters->AddWithValue("@t", type);
                cmd->Parameters->AddWithValue("@m", maxDegree);
                cmd->Parameters->AddWithValue("@cr", credits);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            }
            catch (Exception^) { throw; }
        }

        inline static List<String^>^ ReadAllCourses()
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT course_id, course_code, course_name, credit_hours FROM courses ORDER BY course_id", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(
                        r["course_id"]->ToString() + "," + r["course_code"]->ToString() + "," +
                        r["course_name"]->ToString() + "," + r["credit_hours"]->ToString());
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        // Enrollment
        inline static bool RegisterStudentToCourse(int sid, int courseId, int yearId, int semId)
        {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "INSERT INTO student_course_enrollment(student_id, course_id, academic_year_id, semester_id, enrollment_date) "
                    "VALUES(@s, @c, @y, @sem, CURRENT_DATE)", c);
                cmd->Parameters->AddWithValue("@s", sid);
                cmd->Parameters->AddWithValue("@c", courseId);
                cmd->Parameters->AddWithValue("@y", yearId);
                cmd->Parameters->AddWithValue("@sem", semId);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            }
            catch (Exception^) { return false; }
        }

        inline static List<String^>^ ReadRegistrationsForStudent(int sid)
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT sce.course_id, c.course_code, c.course_name, sce.academic_year_id, sce.semester_id "
                    "FROM student_course_enrollment sce "
                    "JOIN courses c ON sce.course_id = c.course_id "
                    "WHERE sce.student_id=@s", c);
                cmd->Parameters->AddWithValue("@s", sid);
                auto r = cmd->ExecuteReader();
                while (r->Read()) 
                    list->Add(r["course_id"]->ToString() + "," + r["course_code"]->ToString() + "," + 
                              r["course_name"]->ToString() + "," + r["academic_year_id"]->ToString() + "," + 
                              r["semester_id"]->ToString());
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        // Grades
        inline static bool AddGrade(int sid, int courseId, int semId, double a1, double a2, double cw, double f)
        {
            try {
                auto c = OpenConn();
                double total = a1 + a2 + cw + f;
                String^ eval = "F";
                if (total >= 90) eval = "A";
                else if (total >= 80) eval = "B";
                else if (total >= 70) eval = "C";
                else if (total >= 60) eval = "D";

                auto cmd = gcnew MySqlCommand(
                    "INSERT INTO grades(student_id, course_id, semester_id, assignment1, assignment2, coursework, final_exam, total_score, grade_evaluation) "
                    "VALUES(@s, @c, @sem, @a1, @a2, @cw, @f, @t, @e)", c);
                cmd->Parameters->AddWithValue("@s", sid);
                cmd->Parameters->AddWithValue("@c", courseId);
                cmd->Parameters->AddWithValue("@sem", semId);
                cmd->Parameters->AddWithValue("@a1", a1);
                cmd->Parameters->AddWithValue("@a2", a2);
                cmd->Parameters->AddWithValue("@cw", cw);
                cmd->Parameters->AddWithValue("@f", f);
                cmd->Parameters->AddWithValue("@t", total);
                cmd->Parameters->AddWithValue("@e", eval);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            }
            catch (Exception^) { return false; }
        }

        inline static List<String^>^ ReadAllGrades()
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT student_id, course_id, assignment1, assignment2, coursework, final_exam, total_score, grade_evaluation FROM grades", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(
                        r["student_id"]->ToString() + "," + r["course_id"]->ToString() + "," +
                        r["assignment1"]->ToString() + "," + r["assignment2"]->ToString() + "," +
                        r["coursework"]->ToString() + "," + r["final_exam"]->ToString() + "," +
                        r["total_score"]->ToString() + "," + r["grade_evaluation"]->ToString());
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        inline static List<String^>^ ReadGradesForStudent(int sid)
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT c.course_name, g.assignment1, g.assignment2, g.coursework, g.final_exam, g.total_score, g.grade_evaluation "
                    "FROM grades g JOIN courses c ON g.course_id = c.course_id "
                    "WHERE g.student_id=@s", c);
                cmd->Parameters->AddWithValue("@s", sid);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(
                        r["course_name"]->ToString() + "," +
                        r["assignment1"]->ToString() + "," + r["assignment2"]->ToString() + "," +
                        r["coursework"]->ToString() + "," + r["final_exam"]->ToString() + "," +
                        r["total_score"]->ToString() + "," + r["grade_evaluation"]->ToString());
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        inline static List<String^>^ ReadGradesByProfessor(int instructorId)
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT st.full_name as student_name, c.course_name, g.assignment1, g.assignment2, g.coursework, g.final_exam, g.total_score, g.grade_evaluation FROM grades g "
                    "JOIN courses c ON g.course_id = c.course_id "
                    "JOIN students st ON g.student_id = st.student_id "
                    "JOIN instructor_course_assignment ica ON g.course_id = ica.course_id "
                    "WHERE ica.instructor_id=@iid", c);
                cmd->Parameters->AddWithValue("@iid", instructorId);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(
                        r["student_name"]->ToString() + "," + r["course_name"]->ToString() + "," +
                        r["assignment1"]->ToString() + "," + r["assignment2"]->ToString() + "," +
                        r["coursework"]->ToString() + "," + r["final_exam"]->ToString() + "," +
                        r["total_score"]->ToString() + "," + r["grade_evaluation"]->ToString());
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        inline static List<String^>^ ReadPaymentsForStudent(int sid)
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT academic_year_id, semester_id, total_amount, paid_amount, payment_date, payment_status FROM fees WHERE student_id=@s ORDER BY payment_date DESC", c);
                cmd->Parameters->AddWithValue("@s", sid);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(
                        r["academic_year_id"]->ToString() + "," + 
                        r["semester_id"]->ToString() + "," +
                        r["total_amount"]->ToString() + "," + 
                        r["paid_amount"]->ToString() + "," + 
                        r["payment_date"]->ToString() + "," +
                        r["payment_status"]->ToString());
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        inline static List<String^>^ ReadAllNews()
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT news_id, title, description, post_date FROM news ORDER BY post_date DESC", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(r["news_id"]->ToString() + "|" + r["title"]->ToString() + "|" + r["description"]->ToString() + "|" + 
                              Convert::ToDateTime(r["post_date"]).ToString("yyyy-MM-dd"));
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        inline static bool AddNews(String^ title, String^ description, int userId) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("INSERT INTO news (title, description, posted_by_user_id, post_date) VALUES (@t, @d, @u, CURRENT_DATE)", c);
                cmd->Parameters->AddWithValue("@t", title);
                cmd->Parameters->AddWithValue("@d", description);
                cmd->Parameters->AddWithValue("@u", userId);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (...) { return false; }
        }

        inline static bool DeleteNews(int id) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("DELETE FROM news WHERE news_id=@id", c);
                cmd->Parameters->AddWithValue("@id", id);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (...) { return false; }
        }

        // Faculties
        inline static List<String^>^ ReadAllFaculties() {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT faculty_id, faculty_code, faculty_name FROM faculties", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(r["faculty_id"]->ToString() + "," + r["faculty_code"]->ToString() + "," + r["faculty_name"]->ToString());
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        inline static bool AddFaculty(String^ code, String^ name) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("INSERT INTO faculties (faculty_code, faculty_name) VALUES (@c, @n)", c);
                cmd->Parameters->AddWithValue("@c", code);
                cmd->Parameters->AddWithValue("@n", name);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (...) { return false; }
        }

        inline static bool DeleteFaculty(int id) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("DELETE FROM faculties WHERE faculty_id=@id", c);
                cmd->Parameters->AddWithValue("@id", id);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (...) { return false; }
        }

        // Departments
        inline static List<String^>^ ReadAllDepartments() {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT d.department_id, d.department_code, d.department_name, f.faculty_name FROM departments d JOIN faculties f ON d.faculty_id = f.faculty_id", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(r["department_id"]->ToString() + "," + r["department_code"]->ToString() + "," + r["department_name"]->ToString() + "," + r["faculty_name"]->ToString());
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        inline static bool AddDepartment(String^ code, String^ name, int facultyId) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("INSERT INTO departments (department_code, department_name, faculty_id) VALUES (@c, @n, @f)", c);
                cmd->Parameters->AddWithValue("@c", code);
                cmd->Parameters->AddWithValue("@n", name);
                cmd->Parameters->AddWithValue("@f", facultyId);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (...) { return false; }
        }

        inline static bool DeleteDepartment(int id) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("DELETE FROM departments WHERE department_id=@id", c);
                cmd->Parameters->AddWithValue("@id", id);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (...) { return false; }
        }

        // Academic Calendar
        inline static List<String^>^ ReadAllCalendarEvents() {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT calendar_id, event_title, event_type, start_date, end_date FROM academic_calendar ORDER BY start_date", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(r["calendar_id"]->ToString() + "|" + r["event_title"]->ToString() + "|" + r["event_type"]->ToString() + "|" + 
                              Convert::ToDateTime(r["start_date"]).ToString("yyyy-MM-dd") + "|" + 
                              Convert::ToDateTime(r["end_date"]).ToString("yyyy-MM-dd"));
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        inline static bool AddCalendarEvent(String^ title, String^ type, DateTime start, DateTime end) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("INSERT INTO academic_calendar (event_title, event_type, start_date, end_date) VALUES (@t, @ty, @s, @e)", c);
                cmd->Parameters->AddWithValue("@t", title);
                cmd->Parameters->AddWithValue("@ty", type);
                cmd->Parameters->AddWithValue("@s", start);
                cmd->Parameters->AddWithValue("@e", end);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (...) { return false; }
        }

        inline static bool DeleteCalendarEvent(int id) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("DELETE FROM academic_calendar WHERE calendar_id=@id", c);
                cmd->Parameters->AddWithValue("@id", id);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (...) { return false; }
        }

        // Semesters, Years, Levels
        inline static List<String^>^ ReadAllSemesters() {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT semester_id, semester_name FROM semesters", c);
                auto r = cmd->ExecuteReader();
                while (r->Read()) list->Add(r["semester_id"]->ToString() + "," + r["semester_name"]->ToString());
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        inline static List<String^>^ ReadAllYears() {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT academic_year_id, year_name FROM academic_years", c);
                auto r = cmd->ExecuteReader();
                while (r->Read()) list->Add(r["academic_year_id"]->ToString() + "," + r["year_name"]->ToString());
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        inline static List<String^>^ ReadAllLevels() {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT level_id, level_name FROM academic_levels", c);
                auto r = cmd->ExecuteReader();
                while (r->Read()) list->Add(r["level_id"]->ToString() + "," + r["level_name"]->ToString());
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        inline static List<String^>^ ReadScheduleForStudent(int sid) {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "SELECT c.course_name, s.day_of_week, s.start_time, s.end_time, "
                    "COALESCE(h.hall_name, l.lab_name, 'TBA') as location_name "
                    "FROM academic_schedule s "
                    "JOIN courses c ON s.course_id = c.course_id "
                    "LEFT JOIN locations loc ON s.location_id = loc.location_id "
                    "LEFT JOIN lecture_halls h ON loc.hall_id = h.hall_id "
                    "LEFT JOIN laboratories l ON loc.lab_id = l.lab_id "
                    "JOIN student_course_enrollment e ON s.course_id = e.course_id "
                    "WHERE e.student_id = @sid", c);
                cmd->Parameters->AddWithValue("@sid", sid);
                auto r = cmd->ExecuteReader();
                while (r->Read()) {
                    list->Add(r["course_name"]->ToString() + "|" + 
                             r["day_of_week"]->ToString() + "|" + 
                             r["start_time"]->ToString() + "|" + 
                             r["end_time"]->ToString() + "|" + 
                             r["location_name"]->ToString());
                }
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        // Attendance
        inline static List<String^>^ ReadAttendanceForStudent(int sid) {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT c.course_name, a.lecture_date, a.status FROM attendance a JOIN courses c ON a.course_id = c.course_id WHERE a.student_id = @sid ORDER BY a.lecture_date DESC", c);
                cmd->Parameters->AddWithValue("@sid", sid);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(r["course_name"]->ToString() + "|" + Convert::ToDateTime(r["lecture_date"]).ToString("yyyy-MM-dd") + "|" + r["status"]->ToString());
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        inline static List<String^>^ ReadAllLaboratories()
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT lab_id, lab_name, capacity FROM laboratories", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(r["lab_id"]->ToString() + "," + r["lab_name"]->ToString() + "," + r["capacity"]->ToString());
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        inline static List<String^>^ ReadAllLectureHalls()
        {
            auto list = gcnew List<String^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT hall_id, hall_name, capacity FROM lecture_halls", c);
                auto r = cmd->ExecuteReader();
                while (r->Read())
                    list->Add(r["hall_id"]->ToString() + "," + r["hall_name"]->ToString() + "," + r["capacity"]->ToString());
                r->Close(); c->Close();
            } catch (...) {}
            return list;
        }

        // Dashboard Stats
        inline static int GetStudentCount() {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT COUNT(*) FROM students", c);
                int count = Convert::ToInt32(cmd->ExecuteScalar());
                c->Close();
                return count;
            } catch(...) { return 0; }
        }

        inline static int GetCourseCount() {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT COUNT(*) FROM courses", c);
                int count = Convert::ToInt32(cmd->ExecuteScalar());
                c->Close();
                return count;
            } catch(...) { return 0; }
        }

        inline static int GetInstructorCount() {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT COUNT(*) FROM instructors", c);
                int count = Convert::ToInt32(cmd->ExecuteScalar());
                c->Close();
                return count;
            } catch(...) { return 0; }
        }

        // Helper to hash passwords
        inline static String^ HashPassword(String^ password) {
            array<unsigned char>^ bytes = System::Text::Encoding::UTF8->GetBytes(password);
            System::Security::Cryptography::SHA256^ sha256 = System::Security::Cryptography::SHA256::Create();
            array<unsigned char>^ hash = sha256->ComputeHash(bytes);
            return System::Convert::ToBase64String(hash);
        }

        // Add a new user to the system_user table
        inline static bool AddSystemUser(String^ username, String^ password, String^ userType) {
            String^ hashedPassword = HashPassword(password);
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "INSERT INTO system_user(username, password_hash, user_type) VALUES(@u, @p, @ut)", c);
                cmd->Parameters->AddWithValue("@u", username);
                cmd->Parameters->AddWithValue("@p", hashedPassword);
                cmd->Parameters->AddWithValue("@ut", userType);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            }
            catch (Exception^) { throw; }
        }

        // User Management Methods
        inline static List<User^>^ GetAllUsers() {
            auto list = gcnew List<User^>();
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("SELECT user_id, username, user_type FROM system_user ORDER BY user_id", c);
                auto r = cmd->ExecuteReader();
                while (r->Read()) {
                    int userId = Convert::ToInt32(r["user_id"]);
                    String^ userName = r["username"]->ToString();
                    String^ userType = r["user_type"]->ToString();
                    list->Add(gcnew User(userId, userName, userType));
                }
                r->Close(); c->Close();
            }
            catch (Exception^) {}
            return list;
        }

        inline static bool AddUser(String^ username, String^ password, String^ userType) {
            String^ hashedPassword = HashPassword(password);
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "INSERT INTO system_user (username, password_hash, user_type) VALUES (@u, @p, @t)", c);
                cmd->Parameters->AddWithValue("@u", username);
                cmd->Parameters->AddWithValue("@p", hashedPassword);
                cmd->Parameters->AddWithValue("@t", userType);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (Exception^) { return false; }
        }

        inline static bool UpdateUser(int userId, String^ username, String^ userType) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "UPDATE system_user SET username=@u, user_type=@t WHERE user_id=@id", c);
                cmd->Parameters->AddWithValue("@u", username);
                cmd->Parameters->AddWithValue("@t", userType);
                cmd->Parameters->AddWithValue("@id", userId);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (Exception^) { return false; }
        }

        inline static bool UpdateUser(int userId, String^ username, String^ password, String^ userType) {
            String^ hashedPassword = HashPassword(password);
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand(
                    "UPDATE system_user SET username=@u, password_hash=@p, user_type=@t WHERE user_id=@id", c);
                cmd->Parameters->AddWithValue("@u", username);
                cmd->Parameters->AddWithValue("@p", hashedPassword);
                cmd->Parameters->AddWithValue("@t", userType);
                cmd->Parameters->AddWithValue("@id", userId);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (Exception^) { return false; }
        }

        inline static bool DeleteUser(int userId) {
            try {
                auto c = OpenConn();
                auto cmd = gcnew MySqlCommand("DELETE FROM system_user WHERE user_id=@id", c);
                cmd->Parameters->AddWithValue("@id", userId);
                cmd->ExecuteNonQuery();
                c->Close();
                return true;
            } catch (Exception^) { return false; }
        }

    };
}
