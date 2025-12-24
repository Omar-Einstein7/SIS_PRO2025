-- SIS Database Schema - Complete Overhaul

CREATE DATABASE IF NOT EXISTS sis_db;
USE sis_db;

-- 1. Faculties Table
CREATE TABLE IF NOT EXISTS faculties (
    faculty_id INT AUTO_INCREMENT PRIMARY KEY,
    faculty_code VARCHAR(10) NOT NULL,
    faculty_name VARCHAR(100) NOT NULL
);

-- 2. Departments Table
CREATE TABLE IF NOT EXISTS departments (
    department_id INT AUTO_INCREMENT PRIMARY KEY,
    department_code VARCHAR(10) NOT NULL,
    department_name VARCHAR(100) NOT NULL,
    faculty_id INT,
    FOREIGN KEY (faculty_id) REFERENCES faculties(faculty_id) ON DELETE CASCADE
);

-- 3. Academic Levels Table
CREATE TABLE IF NOT EXISTS academic_levels (
    level_id INT AUTO_INCREMENT PRIMARY KEY,
    level_name VARCHAR(50) NOT NULL
);

-- 4. Academic Years Table
CREATE TABLE IF NOT EXISTS academic_years (
    academic_year_id INT AUTO_INCREMENT PRIMARY KEY,
    year_name VARCHAR(20) NOT NULL,
    start_date DATE,
    end_date DATE
);

-- 5. Semesters Table
CREATE TABLE IF NOT EXISTS semesters (
    semester_id INT AUTO_INCREMENT PRIMARY KEY,
    semester_name VARCHAR(20) NOT NULL,
    start_date DATE,
    end_date DATE,
    academic_year_id INT,
    FOREIGN KEY (academic_year_id) REFERENCES academic_years(academic_year_id) ON DELETE CASCADE
);

-- 6. Courses Table
CREATE TABLE IF NOT EXISTS courses (
    course_id INT AUTO_INCREMENT PRIMARY KEY,
    course_code VARCHAR(10) NOT NULL,
    course_name VARCHAR(100) NOT NULL,
    description TEXT,
    course_type VARCHAR(50),
    max_degree INT,
    credit_hours DECIMAL(3,1),
    department_id INT,
    FOREIGN KEY (department_id) REFERENCES departments(department_id) ON DELETE SET NULL
);

-- 7. Lecture Halls Table
CREATE TABLE IF NOT EXISTS lecture_halls (
    hall_id INT AUTO_INCREMENT PRIMARY KEY,
    product_id VARCHAR(20),
    hall_name VARCHAR(100) NOT NULL,
    description TEXT,
    capacity INT,
    seats INT,
    air_conditioning_units INT,
    fans INT,
    lighting_units INT
);

-- 8. Laboratories Table
CREATE TABLE IF NOT EXISTS laboratories (
    lab_id INT AUTO_INCREMENT PRIMARY KEY,
    product_id VARCHAR(20),
    lab_name VARCHAR(100) NOT NULL,
    description TEXT,
    capacity INT,
    computers_count INT,
    seats INT,
    air_conditioning_units INT,
    fans INT,
    lighting_units INT
);

-- 9. Locations Table
CREATE TABLE IF NOT EXISTS locations (
    location_id INT AUTO_INCREMENT PRIMARY KEY,
    location_type VARCHAR(10) NOT NULL,
    hall_id INT,
    lab_id INT,
    FOREIGN KEY (hall_id) REFERENCES lecture_halls(hall_id) ON DELETE SET NULL,
    FOREIGN KEY (lab_id) REFERENCES laboratories(lab_id) ON DELETE SET NULL
);

-- 10. Professors Table
CREATE TABLE IF NOT EXISTS instructors (
    instructor_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL UNIQUE,
    full_name VARCHAR(100) NOT NULL,
    instructor_type VARCHAR(20),
    specialization VARCHAR(50),
    email VARCHAR(100),
    phone VARCHAR(15),
    faculty_id INT,
    department_id INT,
    hire_date DATE,
    FOREIGN KEY (faculty_id) REFERENCES faculties(faculty_id) ON DELETE SET NULL,
    FOREIGN KEY (department_id) REFERENCES departments(department_id) ON DELETE SET NULL,
    FOREIGN KEY (user_id) REFERENCES system_user(user_id) ON DELETE CASCADE
);

-- 11. Students Table
CREATE TABLE IF NOT EXISTS students (
    student_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL UNIQUE,
    full_name VARCHAR(100) NOT NULL,
    national_id VARCHAR(20),
    email VARCHAR(100),
    phone VARCHAR(15),
    academic_year_id INT,
    semester_id INT,
    academic_level_id INT,
    faculty_id INT,
    department_id INT,
    group_number VARCHAR(10),
    section_number VARCHAR(10),
    enrollment_date DATE,
    GPA DECIMAL(3,2),
    final_grade VARCHAR(2),
    FOREIGN KEY (academic_year_id) REFERENCES academic_years(academic_year_id) ON DELETE SET NULL,
    FOREIGN KEY (semester_id) REFERENCES semesters(semester_id) ON DELETE SET NULL,
    FOREIGN KEY (academic_level_id) REFERENCES academic_levels(level_id) ON DELETE SET NULL,
    FOREIGN KEY (faculty_id) REFERENCES faculties(faculty_id) ON DELETE SET NULL,
    FOREIGN KEY (department_id) REFERENCES departments(department_id) ON DELETE SET NULL,
    FOREIGN KEY (user_id) REFERENCES system_user(user_id) ON DELETE CASCADE
);

-- 12. System Users Table (for authentication)
CREATE TABLE IF NOT EXISTS system_user (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(100) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    user_type VARCHAR(20) NOT NULL
);

-- 13. Administration Users Table
CREATE TABLE IF NOT EXISTS administration_users (
    admin_id INT AUTO_INCREMENT PRIMARY KEY,
    full_name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL,
    role VARCHAR(50)
);

-- 14. Student Course Enrollment Table
CREATE TABLE IF NOT EXISTS student_course_enrollment (
    student_course_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT,
    course_id INT,
    academic_year_id INT,
    semester_id INT,
    enrollment_date DATE,
    FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE,
    FOREIGN KEY (course_id) REFERENCES courses(course_id) ON DELETE CASCADE,
    FOREIGN KEY (academic_year_id) REFERENCES academic_years(academic_year_id) ON DELETE CASCADE,
    FOREIGN KEY (semester_id) REFERENCES semesters(semester_id) ON DELETE CASCADE
);

-- 15. Professor Course Assignment Table
CREATE TABLE IF NOT EXISTS instructor_course_assignment (
    id INT AUTO_INCREMENT PRIMARY KEY,
    instructor_id INT,
    course_id INT,
    academic_year_id INT,
    semester_id INT,
    FOREIGN KEY (instructor_id) REFERENCES instructors(instructor_id) ON DELETE CASCADE,
    FOREIGN KEY (course_id) REFERENCES courses(course_id) ON DELETE CASCADE,
    FOREIGN KEY (academic_year_id) REFERENCES academic_years(academic_year_id) ON DELETE CASCADE,
    FOREIGN KEY (semester_id) REFERENCES semesters(semester_id) ON DELETE CASCADE
);

-- 16. Academic Schedule Table
CREATE TABLE IF NOT EXISTS academic_schedule (
    schedule_id INT AUTO_INCREMENT PRIMARY KEY,
    course_id INT,
    instructor_id INT,
    academic_year_id INT,
    semester_id INT,
    location_id INT,
    day_of_week VARCHAR(10) NOT NULL,
    start_time TIME NOT NULL,
    end_time TIME NOT NULL,
    group_number VARCHAR(10),
    section_number VARCHAR(10),
    FOREIGN KEY (course_id) REFERENCES courses(course_id) ON DELETE CASCADE,
    FOREIGN KEY (instructor_id) REFERENCES instructors(instructor_id) ON DELETE CASCADE,
    FOREIGN KEY (academic_year_id) REFERENCES academic_years(academic_year_id) ON DELETE CASCADE,
    FOREIGN KEY (semester_id) REFERENCES semesters(semester_id) ON DELETE CASCADE,
    FOREIGN KEY (location_id) REFERENCES locations(location_id) ON DELETE CASCADE
);

-- 17. Attendance Table
CREATE TABLE IF NOT EXISTS attendance (
    attendance_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT,
    course_id INT,
    semester_id INT,
    lecture_date DATE,
    status VARCHAR(10),
    FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE,
    FOREIGN KEY (course_id) REFERENCES courses(course_id) ON DELETE CASCADE,
    FOREIGN KEY (semester_id) REFERENCES semesters(semester_id) ON DELETE CASCADE
);

-- 18. Grades Table
CREATE TABLE IF NOT EXISTS grades (
    grade_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT,
    course_id INT,
    semester_id INT,
    assignment1 DECIMAL(5,2),
    assignment2 DECIMAL(5,2),
    coursework DECIMAL(5,2),
    final_exam DECIMAL(5,2),
    total_score DECIMAL(5,2),
    grade_evaluation VARCHAR(2),
    FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE,
    FOREIGN KEY (course_id) REFERENCES courses(course_id) ON DELETE CASCADE,
    FOREIGN KEY (semester_id) REFERENCES semesters(semester_id) ON DELETE CASCADE
);

-- 19. Fees Table
CREATE TABLE IF NOT EXISTS fees (
    fee_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT,
    academic_year_id INT,
    semester_id INT,
    total_amount DECIMAL(10,2),
    paid_amount DECIMAL(10,2),
    payment_date DATE,
    payment_status VARCHAR(20),
    FOREIGN KEY (student_id) REFERENCES students(student_id) ON DELETE CASCADE,
    FOREIGN KEY (academic_year_id) REFERENCES academic_years(academic_year_id) ON DELETE CASCADE,
    FOREIGN KEY (semester_id) REFERENCES semesters(semester_id) ON DELETE CASCADE
);

-- 20. Academic Calendar Table
CREATE TABLE IF NOT EXISTS academic_calendar (
    calendar_id INT AUTO_INCREMENT PRIMARY KEY,
    academic_year_id INT,
    semester_id INT,
    event_title VARCHAR(100),
    event_type VARCHAR(50),
    start_date DATE,
    end_date DATE,
    FOREIGN KEY (academic_year_id) REFERENCES academic_years(academic_year_id) ON DELETE CASCADE,
    FOREIGN KEY (semester_id) REFERENCES semesters(semester_id) ON DELETE CASCADE
);

-- 21. News Table
CREATE TABLE IF NOT EXISTS news (
    news_id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(200),
    description TEXT,
    posted_by_user_id INT,
    post_date DATE,
    visible_to VARCHAR(50),
    FOREIGN KEY (posted_by_user_id) REFERENCES administration_users(admin_id) ON DELETE SET NULL
);

-- Insert default data
INSERT IGNORE INTO faculties (faculty_id, faculty_code, faculty_name) VALUES 
(1, 'FCS', 'Faculty of Computer Science'),
(2, 'FENG', 'Faculty of Engineering'),
(3, 'FBUS', 'Faculty of Business');

INSERT IGNORE INTO departments (department_id, department_code, department_name, faculty_id) VALUES 
(1, 'CS', 'Computer Science', 1),
(2, 'IT', 'Information Technology', 1),
(3, 'SE', 'Software Engineering', 1),
(4, 'CE', 'Civil Engineering', 2),
(5, 'ME', 'Mechanical Engineering', 2),
(6, 'ACC', 'Accounting', 3),
(7, 'MKT', 'Marketing', 3);

INSERT IGNORE INTO academic_levels (level_id, level_name) VALUES 
(1, 'Freshman'),
(2, 'Sophomore'),
(3, 'Junior'),
(4, 'Senior'),
(5, 'Graduate');

INSERT IGNORE INTO academic_years (academic_year_id, year_name, start_date, end_date) VALUES 
(1, '2023-2024', '2023-09-01', '2024-06-30'),
(2, '2024-2025', '2024-09-01', '2025-06-30');

INSERT IGNORE INTO semesters (semester_id, semester_name, start_date, end_date, academic_year_id) VALUES 
(1, 'Fall 2023', '2023-09-01', '2023-12-20', 1),
(2, 'Spring 2024', '2024-01-15', '2024-05-15', 1),
(3, 'Fall 2024', '2024-09-01', '2024-12-20', 2),
(4, 'Spring 2025', '2025-01-15', '2025-05-15', 2);

-- Insert default system users
INSERT IGNORE INTO system_user (username, password_hash, user_type) VALUES 
('admin', 'admin123', 'Admin'),
('professor1', 'prof123', 'Professor'),
('student1', 'student123', 'Student');

-- Insert default administration user
INSERT IGNORE INTO administration_users (admin_id, full_name, email, role) VALUES 
(1, 'System Administrator', 'admin@university.edu', 'Super Admin');

-- Insert sample courses
INSERT IGNORE INTO courses (course_id, course_code, course_name, course_type, max_degree, credit_hours) VALUES 
(1, 'CS101', 'Introduction to Programming', 'Core', 100, 3.0),
(2, 'CS201', 'Data Structures', 'Core', 100, 4.0),
(3, 'MATH101', 'Calculus I', 'Core', 100, 3.0),
(4, 'ENG101', 'English Composition', 'General', 100, 3.0);

-- Insert sample lecture halls and labs
INSERT IGNORE INTO lecture_halls (hall_id, hall_name, capacity, seats) VALUES 
(1, 'Main Hall A', 100, 100),
(2, 'Main Hall B', 80, 80),
(3, 'Engineering Hall', 120, 120);

INSERT IGNORE INTO laboratories (lab_id, lab_name, capacity, computers_count) VALUES 
(1, 'Computer Lab 1', 30, 30),
(2, 'Computer Lab 2', 25, 25),
(3, 'Engineering Lab', 20, 15);

INSERT IGNORE INTO locations (location_type, hall_id, lab_id) VALUES 
('Hall', 1, NULL),
('Hall', 2, NULL),
('Hall', 3, NULL),
('Lab', NULL, 1),
('Lab', NULL, 2),
('Lab', NULL, 3);

-- Sample Academic Calendar
INSERT IGNORE INTO academic_calendar (event_name, event_date, description) VALUES
('Fall Semester Start', '2023-09-01', 'Official start of the Fall semester classes.'),
('Midterm Exams Week', '2023-11-05', 'Midterm examinations for all courses.'),
('Winter Break', '2023-12-21', 'End of semester and start of winter holiday.'),
('Spring Semester Start', '2024-01-15', 'Official start of the Spring semester classes.');

-- Sample Academic Schedule (for Course 1, Year 1, Semester 1, Location 1)
INSERT IGNORE INTO academic_schedule (course_id, instructor_id, academic_year_id, semester_id, location_id, day_of_week, start_time, end_time) VALUES
(1, 1, 1, 1, 1, 'Monday', '09:00:00', '11:00:00'),
(2, 1, 1, 1, 4, 'Wednesday', '13:00:00', '15:00:00'),
(3, 1, 1, 1, 2, 'Thursday', '10:00:00', '12:00:00');
