-- phpMyAdmin SQL Dump
-- version 4.9.0.1
-- https://www.phpmyadmin.net/
--
-- Host: sql206.infinityfree.com
-- Generation Time: Dec 23, 2025 at 06:37 PM
-- Server version: 11.4.7-MariaDB
-- PHP Version: 7.2.22

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `if0_40667078_cPPproject`
--

-- --------------------------------------------------------

--
-- Table structure for table `academic_calendar`
--

CREATE TABLE `academic_calendar` (
  `calendar_id` int(11) NOT NULL,
  `academic_year_id` int(11) DEFAULT NULL,
  `semester_id` int(11) DEFAULT NULL,
  `event_title` varchar(100) DEFAULT NULL,
  `event_type` varchar(50) DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  `end_date` date DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `academic_calendar`
--

INSERT INTO `academic_calendar` (`calendar_id`, `academic_year_id`, `semester_id`, `event_title`, `event_type`, `start_date`, `end_date`) VALUES
(1, 1, 1, 'Start of First Semester', 'Semester Start', '2021-09-15', '2021-09-15'),
(2, 1, 1, 'Start of First Semester', 'Semester Start', '2021-09-15', '2021-09-15'),
(3, 1, 1, 'Midterm Exams', 'Exams', '2021-11-20', '2021-11-30'),
(4, 1, 1, 'Final Exams', 'Exams', '2022-01-10', '2022-01-31'),
(5, 1, 2, 'Start of Second Semester', 'Semester Start', '2022-02-15', '2022-02-15'),
(6, 1, 2, 'Midterm Exams', 'Exams', '2022-04-10', '2022-04-20'),
(7, 1, 2, 'Final Exams', 'Exams', '2022-06-10', '2022-06-30'),
(8, 2, 3, 'Start of First Semester', 'Semester Start', '2022-09-15', '2022-09-15'),
(9, 2, 3, 'Midterm Exams', 'Exams', '2022-11-20', '2022-11-30'),
(10, 2, 3, 'Final Exams', 'Exams', '2023-01-10', '2023-01-31'),
(11, 2, 4, 'Start of Second Semester', 'Semester Start', '2023-02-15', '2023-02-15'),
(12, 2, 4, 'Midterm Exams', 'Exams', '2023-04-10', '2023-04-20'),
(13, 2, 4, 'Final Exams', 'Exams', '2023-06-10', '2023-06-30'),
(14, 3, 5, 'Start of First Semester', 'Semester Start', '2023-09-15', '2023-09-15'),
(15, 3, 5, 'Midterm Exams', 'Exams', '2023-11-20', '2023-11-30'),
(16, 3, 5, 'Final Exams', 'Exams', '2024-01-10', '2024-01-31'),
(17, 3, 6, 'Start of Second Semester', 'Semester Start', '2024-02-15', '2024-02-15'),
(18, 3, 6, 'Midterm Exams', 'Exams', '2024-04-10', '2024-04-20'),
(19, 3, 6, 'Final Exams', 'Exams', '2024-06-10', '2024-06-30'),
(20, 3, 5, 'University Orientation Day', 'Event', '2023-09-20', '2023-09-20'),
(21, 4, 7, 'Graduation Ceremony', 'Event', '2025-07-15', '2025-07-15'),
(22, 5, 9, 'Registration Period', 'Registration', '2025-08-20', '2025-09-10');

-- --------------------------------------------------------

--
-- Table structure for table `academic_levels`
--

CREATE TABLE `academic_levels` (
  `level_id` int(11) NOT NULL,
  `level_name` varchar(50) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `academic_levels`
--

INSERT INTO `academic_levels` (`level_id`, `level_name`) VALUES
(1, 'Level 1'),
(2, 'Level 2'),
(3, 'Level 3'),
(4, 'Level 4'),
(5, 'Graduate'),
(6, 'Postgraduate');

-- --------------------------------------------------------

--
-- Table structure for table `academic_schedule`
--

CREATE TABLE `academic_schedule` (
  `schedule_id` int(11) NOT NULL,
  `course_id` int(11) DEFAULT NULL,
  `instructor_id` int(11) DEFAULT NULL,
  `academic_year_id` int(11) DEFAULT NULL,
  `semester_id` int(11) DEFAULT NULL,
  `location_id` int(11) DEFAULT NULL,
  `day_of_week` varchar(10) NOT NULL,
  `start_time` time NOT NULL,
  `end_time` time NOT NULL,
  `group_number` varchar(10) DEFAULT NULL,
  `section_number` varchar(10) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `academic_schedule`
--

INSERT INTO `academic_schedule` (`schedule_id`, `course_id`, `instructor_id`, `academic_year_id`, `semester_id`, `location_id`, `day_of_week`, `start_time`, `end_time`, `group_number`, `section_number`) VALUES
(1, 1, 1, 3, 5, 1, 'Sunday', '09:00:00', '11:00:00', '1', '1'),
(2, 2, 2, 3, 5, 3, 'Tuesday', '11:00:00', '13:00:00', '1', '1'),
(3, 3, 3, 3, 5, 1, 'Thursday', '09:00:00', '11:00:00', '2', '1'),
(4, 4, 4, 3, 5, 2, 'Sunday', '11:00:00', '13:00:00', '1', '1'),
(5, 5, 5, 3, 5, 3, 'Tuesday', '09:00:00', '11:00:00', '1', '2'),
(6, 6, 6, 3, 5, 2, 'Thursday', '11:00:00', '13:00:00', '2', '1'),
(7, 7, 7, 3, 5, 1, 'Monday', '09:00:00', '11:00:00', '1', '1'),
(8, 8, 8, 3, 5, 4, 'Wednesday', '11:00:00', '13:00:00', '1', '1'),
(9, 9, 9, 3, 5, 1, 'Saturday', '09:00:00', '11:00:00', '2', '1'),
(10, 10, 10, 3, 5, 3, 'Monday', '11:00:00', '13:00:00', '1', '1'),
(11, 11, 11, 3, 5, 4, 'Wednesday', '09:00:00', '11:00:00', '1', '2'),
(12, 12, 12, 3, 5, 3, 'Saturday', '11:00:00', '13:00:00', '2', '1'),
(13, 13, 13, 3, 5, 2, 'Sunday', '09:00:00', '11:00:00', '1', '1'),
(14, 14, 14, 3, 5, 1, 'Tuesday', '11:00:00', '13:00:00', '1', '1'),
(15, 15, 15, 3, 5, 2, 'Thursday', '09:00:00', '11:00:00', '2', '1');

-- --------------------------------------------------------

--
-- Table structure for table `academic_years`
--

CREATE TABLE `academic_years` (
  `academic_year_id` int(11) NOT NULL,
  `year_name` varchar(20) DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  `end_date` date DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `academic_years`
--

INSERT INTO `academic_years` (`academic_year_id`, `year_name`, `start_date`, `end_date`) VALUES
(1, '2021/2022', '2021-09-01', '2022-06-30'),
(2, '2022/2023', '2022-09-01', '2023-06-30'),
(3, '2023/2024', '2023-09-01', '2024-06-30'),
(4, '2024/2025', '2024-09-01', '2025-06-30'),
(5, '2025/2026', '2025-09-01', '2026-06-30');

-- --------------------------------------------------------

--
-- Table structure for table `administration_users`
--

CREATE TABLE `administration_users` (
  `admin_id` int(11) NOT NULL,
  `full_name` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `role` varchar(50) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `administration_users`
--

INSERT INTO `administration_users` (`admin_id`, `full_name`, `email`, `role`) VALUES
(1, 'Omar Yasser', 'omar1@gmail.com', NULL),
(2, 'admin', 'admin@gmail.com', 'admin');

-- --------------------------------------------------------

--
-- Table structure for table `attendance`
--

CREATE TABLE `attendance` (
  `attendance_id` int(11) NOT NULL,
  `student_id` int(11) DEFAULT NULL,
  `course_id` int(11) DEFAULT NULL,
  `semester_id` int(11) DEFAULT NULL,
  `lecture_date` date DEFAULT NULL,
  `status` varchar(10) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Table structure for table `courses`
--

CREATE TABLE `courses` (
  `course_id` int(11) NOT NULL,
  `course_code` varchar(10) DEFAULT NULL,
  `course_name` varchar(100) DEFAULT NULL,
  `description` text DEFAULT NULL,
  `course_type` varchar(50) DEFAULT NULL,
  `max_degree` int(11) DEFAULT NULL,
  `credit_hours` decimal(3,1) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `courses`
--

INSERT INTO `courses` (`course_id`, `course_code`, `course_name`, `description`, `course_type`, `max_degree`, `credit_hours`) VALUES
(1, 'CS101', 'Introduction to Programming', 'Basics of programming using C++', 'Core', 100, '3.0'),
(2, 'CS101', 'Introduction to Programming', 'Basics of programming using C++', 'Core', 100, '3.0'),
(3, 'CS102', 'Object Oriented Programming', 'OOP concepts using C++ and Java', 'Core', 100, '3.0'),
(4, 'CS201', 'Data Structures', 'Stacks, Queues, Trees, Graphs', 'Core', 100, '3.0'),
(5, 'CS202', 'Algorithms', 'Algorithm design and analysis', 'Core', 100, '3.0'),
(6, 'CS301', 'Operating Systems', 'Process, memory and file systems', 'Core', 100, '3.0'),
(7, 'CS302', 'Database Systems', 'Relational databases and SQL', 'Core', 100, '3.0'),
(8, 'CS401', 'Software Engineering', 'Software development life cycle', 'Core', 100, '3.0'),
(9, 'CS402', 'Compiler Design', 'Lexical and syntax analysis', 'Elective', 100, '3.0'),
(10, 'IT101', 'Introduction to IT', 'Fundamentals of Information Technology', 'Core', 100, '3.0'),
(11, 'IT102', 'Computer Networks', 'Networking fundamentals and protocols', 'Core', 100, '3.0'),
(12, 'IT201', 'Network Administration', 'Managing enterprise networks', 'Core', 100, '3.0'),
(13, 'IT202', 'Cyber Security Basics', 'Security principles and threats', 'Core', 100, '3.0'),
(14, 'IT301', 'Linux Administration', 'Linux system administration', 'Core', 100, '3.0'),
(15, 'IT302', 'Cloud Computing', 'Cloud services and virtualization', 'Elective', 100, '3.0'),
(16, 'IT401', 'IT Project Management', 'Managing IT projects', 'Elective', 100, '3.0'),
(17, 'ENG101', 'Engineering Mathematics', 'Mathematics for engineers', 'Core', 100, '3.0'),
(18, 'ENG102', 'Electrical Circuits', 'Basic electrical circuits', 'Core', 100, '3.0'),
(19, 'ENG201', 'Electronics I', 'Analog electronics fundamentals', 'Core', 100, '3.0'),
(20, 'ENG202', 'Digital Logic Design', 'Logic gates and digital circuits', 'Core', 100, '3.0'),
(21, 'ENG301', 'Microprocessors', 'Microprocessor architecture', 'Core', 100, '3.0'),
(22, 'ENG302', 'Control Systems', 'Control theory and applications', 'Elective', 100, '3.0'),
(23, 'ENG401', 'Embedded Systems', 'Embedded hardware and software', 'Elective', 100, '3.0'),
(24, 'AI101', 'Introduction to AI', 'Basics of Artificial Intelligence', 'Core', 100, '3.0'),
(25, 'AI102', 'Python for AI', 'Python programming for AI', 'Core', 100, '3.0'),
(26, 'AI201', 'Machine Learning', 'Supervised and unsupervised learning', 'Core', 100, '3.0'),
(27, 'AI202', 'Deep Learning', 'Neural networks and deep learning', 'Core', 100, '3.0'),
(28, 'AI301', 'Computer Vision', 'Image processing and vision systems', 'Elective', 100, '3.0'),
(29, 'AI302', 'Natural Language Processing', 'Text and language processing', 'Elective', 100, '3.0'),
(30, 'AI401', 'Robotics', 'Robotics and intelligent systems', 'Elective', 100, '3.0'),
(31, 'BIS101', 'Introduction to BIS', 'Overview of Business Information Systems', 'Core', 100, '3.0'),
(32, 'BIS102', 'Business Management', 'Principles of management', 'Core', 100, '3.0'),
(33, 'BIS201', 'Accounting Information Systems', 'Accounting systems and software', 'Core', 100, '3.0'),
(34, 'BIS202', 'ERP Systems', 'Enterprise resource planning systems', 'Core', 100, '3.0'),
(35, 'BIS301', 'Business Intelligence', 'Data analysis for business decisions', 'Elective', 100, '3.0'),
(36, 'BIS302', 'E-Commerce', 'Electronic commerce systems', 'Elective', 100, '3.0'),
(37, 'BIS401', 'Digital Transformation', 'Digital business strategies', 'Elective', 100, '3.0');

-- --------------------------------------------------------

--
-- Table structure for table `departments`
--

CREATE TABLE `departments` (
  `department_id` int(11) NOT NULL,
  `department_code` varchar(10) DEFAULT NULL,
  `department_name` varchar(100) NOT NULL,
  `faculty_id` int(11) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `departments`
--

INSERT INTO `departments` (`department_id`, `department_code`, `department_name`, `faculty_id`) VALUES
(1, 'CS-SE', 'Software Engineering', 1),
(2, 'CS-DS', 'Data Science', 1),
(3, 'CS-IS', 'Information Systems', 1),
(4, 'IT-NET', 'Computer Networks', 2),
(5, 'IT-SEC', 'Cyber Security', 2),
(6, 'IT-SYS', 'System Administration', 2),
(7, 'ENG-COM', 'Computer Engineering', 3),
(8, 'ENG-ELC', 'Electronics Engineering', 3),
(9, 'ENG-POW', 'Electrical Power Engineering', 3),
(10, 'AI-ML', 'Machine Learning', 4),
(11, 'AI-DL', 'Deep Learning', 4),
(12, 'AI-ROB', 'Robotics', 4),
(13, 'BIS-MIS', 'Management Information Systems', 5),
(14, 'BIS-ERP', 'Enterprise Resource Planning', 5);

-- --------------------------------------------------------

--
-- Table structure for table `faculties`
--

CREATE TABLE `faculties` (
  `faculty_id` int(11) NOT NULL,
  `faculty_code` varchar(10) DEFAULT NULL,
  `faculty_name` varchar(100) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `faculties`
--

INSERT INTO `faculties` (`faculty_id`, `faculty_code`, `faculty_name`) VALUES
(1, 'CS', 'Faculty of Computer Science'),
(2, 'IT', 'Faculty of Information Technology'),
(3, 'ENG', 'Faculty of Engineering'),
(4, 'AI', 'Faculty of Artificial Intelligence'),
(5, 'BIS', 'Faculty of Business Information Systems');

-- --------------------------------------------------------

--
-- Table structure for table `fees`
--

CREATE TABLE `fees` (
  `fee_id` int(11) NOT NULL,
  `student_id` int(11) DEFAULT NULL,
  `academic_year_id` int(11) DEFAULT NULL,
  `semester_id` int(11) DEFAULT NULL,
  `total_amount` decimal(10,2) DEFAULT NULL,
  `paid_amount` decimal(10,2) DEFAULT NULL,
  `payment_date` date DEFAULT NULL,
  `payment_status` varchar(20) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `fees`
--

INSERT INTO `fees` (`fee_id`, `student_id`, `academic_year_id`, `semester_id`, `total_amount`, `paid_amount`, `payment_date`, `payment_status`) VALUES
(1, 1, 1, 1, '10000.00', '10000.00', '2021-10-01', 'Paid'),
(2, 2, 1, 2, '10000.00', '10000.00', '2022-03-01', 'Paid'),
(3, 3, 1, 1, '10000.00', '10000.00', '2021-10-05', 'Paid'),
(4, 4, 1, 2, '10000.00', '10000.00', '2022-03-05', 'Paid'),
(5, 5, 1, 1, '10000.00', '10000.00', '2021-10-10', 'Paid'),
(6, 6, 2, 3, '12000.00', '6000.00', '2022-10-10', 'Partial'),
(7, 7, 2, 4, '12000.00', '8000.00', '2023-03-01', 'Partial'),
(8, 8, 2, 3, '12000.00', '5000.00', '2022-10-15', 'Partial'),
(9, 9, 2, 4, '12000.00', '7000.00', '2023-03-10', 'Partial'),
(10, 10, 2, 3, '12000.00', '9000.00', '2022-10-20', 'Partial'),
(11, 11, 3, 5, '14000.00', '0.00', NULL, 'Unpaid'),
(12, 12, 3, 6, '14000.00', '0.00', NULL, 'Unpaid'),
(13, 13, 3, 5, '14000.00', '0.00', NULL, 'Unpaid'),
(14, 14, 3, 6, '14000.00', '0.00', NULL, 'Unpaid'),
(15, 15, 3, 5, '14000.00', '0.00', NULL, 'Unpaid'),
(16, 16, 4, 7, '16000.00', '16000.00', '2024-10-01', 'Paid'),
(17, 17, 4, 8, '16000.00', '8000.00', '2025-02-01', 'Partial'),
(18, 18, 5, 9, '18000.00', '18000.00', '2025-10-01', 'Paid'),
(19, 19, 5, 10, '18000.00', '0.00', NULL, 'Unpaid'),
(20, 20, 5, 9, '18000.00', '9000.00', '2025-10-10', 'Partial');

-- --------------------------------------------------------

--
-- Table structure for table `grades`
--

CREATE TABLE `grades` (
  `grade_id` int(11) NOT NULL,
  `student_id` int(11) DEFAULT NULL,
  `course_id` int(11) DEFAULT NULL,
  `semester_id` int(11) DEFAULT NULL,
  `assignment1` decimal(5,2) DEFAULT NULL,
  `assignment2` decimal(5,2) DEFAULT NULL,
  `coursework` decimal(5,2) DEFAULT NULL,
  `final_exam` decimal(5,2) DEFAULT NULL,
  `total_score` decimal(5,2) DEFAULT NULL,
  `grade_evaluation` varchar(2) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Table structure for table `instructors`
--

CREATE TABLE `instructors` (
  `instructor_id` int(11) NOT NULL,
  `full_name` varchar(100) DEFAULT NULL,
  `instructor_type` varchar(20) DEFAULT NULL,
  `specialization` varchar(50) DEFAULT NULL,
  `email` varchar(100) DEFAULT NULL,
  `phone` varchar(15) DEFAULT NULL,
  `faculty_id` int(11) DEFAULT NULL,
  `department_id` int(11) DEFAULT NULL,
  `hire_date` date DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `instructors`
--

INSERT INTO `instructors` (`instructor_id`, `full_name`, `instructor_type`, `specialization`, `email`, `phone`, `faculty_id`, `department_id`, `hire_date`) VALUES
(1, 'Mohamed Ramadan', 'Doctor', 'Software Engineering', 'mohamed.ramadan@uni.edu', '01090000001', 1, 1, '2018-09-01'),
(2, 'Ahmed Hassan', 'Doctor', 'Data Science', 'ahmed.hassan@uni.edu', '01090000002', 1, 2, '2017-09-01'),
(3, 'Mahmoud Ali', 'Doctor', 'Computer Networks', 'mahmoud.ali@uni.edu', '01090000003', 2, 4, '2016-09-01'),
(4, 'Youssef Adel', 'Doctor', 'Artificial Intelligence', 'youssef.adel@uni.edu', '01090000004', 4, 10, '2019-09-01'),
(5, 'Omar Salah', 'Assistant', 'Software Engineering', 'omar.salah@uni.edu', '01090000005', 1, 1, '2021-10-01'),
(6, 'Karim Mostafa', 'Assistant', 'Cyber Security', 'karim.mostafa@uni.edu', '01090000006', 2, 5, '2022-10-01'),
(7, 'Hassan Ibrahim', 'Assistant', 'Electronics Engineering', 'hassan.ibrahim@uni.edu', '01090000007', 3, 8, '2020-10-01'),
(8, 'Islam Reda', 'Assistant', 'Machine Learning', 'islam.reda@uni.edu', '01090000008', 4, 11, '2023-10-01'),
(9, 'Ayman Fathy', 'Doctor', 'Information Systems', 'ayman.fathy@uni.edu', '01090000009', 1, 3, '2015-09-01'),
(10, 'Tarek Mahmoud', 'Doctor', 'Cyber Security', 'tarek.mahmoud@uni.edu', '01090000010', 2, 5, '2014-09-01'),
(11, 'Hesham Abdelrahman', 'Doctor', 'Computer Networks', 'hesham.abdelrahman@uni.edu', '01090000011', 2, 4, '2016-09-01'),
(12, 'Sameh Nabil', 'Doctor', 'Computer Engineering', 'sameh.nabil@uni.edu', '01090000012', 3, 7, '2013-09-01'),
(13, 'Wael Samir', 'Doctor', 'Electronics Engineering', 'wael.samir@uni.edu', '01090000013', 3, 8, '2012-09-01'),
(14, 'Ramy Adel', 'Doctor', 'Machine Learning', 'ramy.adel@uni.edu', '01090000014', 4, 10, '2018-09-01'),
(15, 'Sherif Khaled', 'Doctor', 'Robotics', 'sherif.khaled@uni.edu', '01090000015', 4, 12, '2019-09-01'),
(16, 'Nader Hassan', 'Doctor', 'ERP Systems', 'nader.hassan@uni.edu', '01090000016', 5, 15, '2016-09-01'),
(17, 'Hany Lotfy', 'Doctor', 'Business Intelligence', 'hany.lotfy@uni.edu', '01090000017', 5, 14, '2017-09-01'),
(18, 'Bassem Youssef', 'Doctor', 'Data Science', 'bassem.youssef@uni.edu', '01090000018', 1, 2, '2015-09-01'),
(19, 'Mahmoud Reda', 'Assistant', 'Information Systems', 'mahmoud.reda@uni.edu', '01090000019', 1, 3, '2021-10-01'),
(20, 'Mostafa Saeed', 'Assistant', 'Software Engineering', 'mostafa.saeed@uni.edu', '01090000020', 1, 1, '2022-10-01'),
(21, 'Khaled Samy', 'Assistant', 'Computer Networks', 'khaled.samy@uni.edu', '01090000021', 2, 4, '2023-10-01'),
(22, 'Ahmed Lotfy', 'Assistant', 'Cyber Security', 'ahmed.lotfy@uni.edu', '01090000022', 2, 5, '2021-10-01'),
(23, 'Ibrahim Nasser', 'Assistant', 'Electronics Engineering', 'ibrahim.nasser@uni.edu', '01090000023', 3, 8, '2020-10-01'),
(24, 'Seif Magdy', 'Assistant', 'Computer Engineering', 'seif.magdy@uni.edu', '01090000024', 3, 7, '2022-10-01'),
(25, 'Ola Samir', 'Assistant', 'Artificial Intelligence', 'ola.samir@uni.edu', '01090000025', 4, 10, '2023-10-01'),
(26, 'Nour Adel', 'Assistant', 'Deep Learning', 'nour.adel@uni.edu', '01090000026', 4, 11, '2024-10-01'),
(27, 'Heba Mahmoud', 'Assistant', 'Management Information Systems', 'heba.mahmoud@uni.edu', '01090000027', 5, 14, '2022-10-01'),
(28, 'Salma Taha', 'Assistant', 'ERP Systems', 'salma.taha@uni.edu', '01090000028', 5, 15, '2023-10-01');

-- --------------------------------------------------------

--
-- Table structure for table `instructor_course_assignment`
--

CREATE TABLE `instructor_course_assignment` (
  `id` int(11) NOT NULL,
  `instructor_id` int(11) DEFAULT NULL,
  `course_id` int(11) DEFAULT NULL,
  `academic_year_id` int(11) DEFAULT NULL,
  `semester_id` int(11) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `instructor_course_assignment`
--

INSERT INTO `instructor_course_assignment` (`id`, `instructor_id`, `course_id`, `academic_year_id`, `semester_id`) VALUES
(1, 1, 1, 3, 5),
(2, 1, 2, 3, 5),
(3, 2, 3, 3, 6),
(4, 3, 4, 4, 7),
(5, 4, 5, 4, 7);

-- --------------------------------------------------------

--
-- Table structure for table `laboratories`
--

CREATE TABLE `laboratories` (
  `lab_id` int(11) NOT NULL,
  `product_id` varchar(20) DEFAULT NULL,
  `lab_name` varchar(100) NOT NULL,
  `description` text DEFAULT NULL,
  `capacity` int(11) DEFAULT NULL,
  `computers_count` int(11) DEFAULT NULL,
  `seats` int(11) DEFAULT NULL,
  `air_conditioning_units` int(11) DEFAULT NULL,
  `fans` int(11) DEFAULT NULL,
  `lighting_units` int(11) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `laboratories`
--

INSERT INTO `laboratories` (`lab_id`, `product_id`, `lab_name`, `description`, `capacity`, `computers_count`, `seats`, `air_conditioning_units`, `fans`, `lighting_units`) VALUES
(1, '1', 'Computer Lab 1', 'General purpose computer laboratory', 30, 30, 30, 2, 4, 10),
(2, '2', 'Computer Lab 2', 'Programming and software development lab', 25, 25, 25, 2, 3, 8),
(3, '3', 'Network Lab', 'Networking and routing practical lab', 20, 20, 20, 1, 2, 6),
(4, '4', 'AI Lab', 'Artificial Intelligence and Machine Learning lab', 35, 35, 35, 3, 4, 12),
(5, '5', 'Database Lab', 'Database management systems lab', 28, 28, 28, 2, 3, 9),
(6, '6', 'Cyber Security Lab', 'Security and penetration testing lab', 22, 22, 22, 2, 3, 7),
(7, '7', 'Electronics Lab', 'Electronics and circuits laboratory', 40, 0, 40, 3, 6, 14),
(8, '8', 'Robotics Lab', 'Robotics and automation laboratory', 18, 18, 18, 1, 2, 5),
(9, '9', 'Software Testing Lab', 'Software testing and QA lab', 24, 24, 24, 2, 3, 8),
(10, '10', 'Project Lab', 'Final year projects laboratory', 30, 30, 30, 2, 4, 10),
(11, '1', 'Computer Lab 1', 'General purpose computer laboratory', 30, 30, 30, 2, 4, 10),
(12, '2', 'Computer Lab 2', 'Programming and software development lab', 25, 25, 25, 2, 3, 8),
(13, '3', 'Network Lab', 'Networking and routing practical lab', 20, 20, 20, 1, 2, 6),
(14, '4', 'AI Lab', 'Artificial Intelligence and Machine Learning lab', 35, 35, 35, 3, 4, 12),
(15, '5', 'Database Lab', 'Database management systems lab', 28, 28, 28, 2, 3, 9),
(16, '6', 'Cyber Security Lab', 'Security and penetration testing lab', 22, 22, 22, 2, 3, 7),
(17, '7', 'Electronics Lab', 'Electronics and circuits laboratory', 40, 0, 40, 3, 6, 14),
(18, '8', 'Robotics Lab', 'Robotics and automation laboratory', 18, 18, 18, 1, 2, 5),
(19, '9', 'Software Testing Lab', 'Software testing and QA lab', 24, 24, 24, 2, 3, 8),
(20, '10', 'Project Lab', 'Final year projects laboratory', 30, 30, 30, 2, 4, 10),
(21, '1', 'Computer Lab 1', 'General purpose computer laboratory', 30, 30, 30, 2, 4, 10),
(22, '2', 'Computer Lab 2', 'Programming and software development lab', 25, 25, 25, 2, 3, 8),
(23, '3', 'Network Lab', 'Networking and routing practical lab', 20, 20, 20, 1, 2, 6),
(24, '4', 'AI Lab', 'Artificial Intelligence and Machine Learning lab', 35, 35, 35, 3, 4, 12),
(25, '5', 'Database Lab', 'Database management systems lab', 28, 28, 28, 2, 3, 9),
(26, '6', 'Cyber Security Lab', 'Security and penetration testing lab', 22, 22, 22, 2, 3, 7),
(27, '7', 'Electronics Lab', 'Electronics and circuits laboratory', 40, 0, 40, 3, 6, 14),
(28, '8', 'Robotics Lab', 'Robotics and automation laboratory', 18, 18, 18, 1, 2, 5),
(29, '9', 'Software Testing Lab', 'Software testing and QA lab', 24, 24, 24, 2, 3, 8),
(30, '10', 'Project Lab', 'Final year projects laboratory', 30, 30, 30, 2, 4, 10);

-- --------------------------------------------------------

--
-- Table structure for table `lecture_halls`
--

CREATE TABLE `lecture_halls` (
  `hall_id` int(11) NOT NULL,
  `product_id` varchar(20) DEFAULT NULL,
  `hall_name` varchar(100) NOT NULL,
  `description` text DEFAULT NULL,
  `capacity` int(11) DEFAULT NULL,
  `seats` int(11) DEFAULT NULL,
  `air_conditioning_units` int(11) DEFAULT NULL,
  `fans` int(11) DEFAULT NULL,
  `lighting_units` int(11) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `lecture_halls`
--

INSERT INTO `lecture_halls` (`hall_id`, `product_id`, `hall_name`, `description`, `capacity`, `seats`, `air_conditioning_units`, `fans`, `lighting_units`) VALUES
(1, '1', 'Hall A', 'Main lecture hall for large classes', 200, 200, 6, 10, 30),
(2, '2', 'Hall B', 'Medium size lecture hall', 150, 150, 4, 8, 24),
(3, '3', 'Hall C', 'Lecture hall for CS faculty', 120, 120, 4, 6, 20),
(4, '4', 'Hall D', 'Lecture hall for IT faculty', 100, 100, 3, 6, 18),
(5, '5', 'Hall E', 'Lecture hall for Engineering faculty', 180, 180, 5, 9, 28),
(6, '6', 'Hall F', 'Lecture hall for AI faculty', 90, 90, 3, 5, 16),
(7, '7', 'Seminar Hall 1', 'Seminars and presentations', 60, 60, 2, 4, 12),
(8, '8', 'Seminar Hall 2', 'Postgraduate lectures', 50, 50, 2, 4, 10),
(9, '1', 'Hall A', 'Main lecture hall', 200, 200, 4, 6, 12),
(10, '1', 'Hall B', 'Secondary lecture hall', 150, 150, 3, 5, 10),
(11, '2', 'Hall C', 'IT department hall', 120, 120, 3, 4, 8),
(12, '3', 'Hall D', 'Engineering lectures', 180, 180, 4, 6, 12),
(13, '4', 'Hall E', 'AI faculty hall', 100, 100, 2, 4, 8);

-- --------------------------------------------------------

--
-- Table structure for table `locations`
--

CREATE TABLE `locations` (
  `location_id` int(11) NOT NULL,
  `location_type` varchar(10) DEFAULT NULL,
  `hall_id` int(11) DEFAULT NULL,
  `lab_id` int(11) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `locations`
--

INSERT INTO `locations` (`location_id`, `location_type`, `hall_id`, `lab_id`) VALUES
(1, 'Hall', 1, NULL),
(2, 'Hall', 2, NULL),
(3, 'Hall', 3, NULL),
(4, 'Lab', NULL, 1),
(5, 'Lab', NULL, 2),
(6, 'Lab', NULL, 3),
(7, 'Lab', NULL, 4),
(8, 'Lab', NULL, 5);

-- --------------------------------------------------------

--
-- Table structure for table `news`
--

CREATE TABLE `news` (
  `news_id` int(11) NOT NULL,
  `title` varchar(200) DEFAULT NULL,
  `description` text DEFAULT NULL,
  `posted_by_user_id` int(11) DEFAULT NULL,
  `post_date` date DEFAULT NULL,
  `visible_to` varchar(50) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Table structure for table `semesters`
--

CREATE TABLE `semesters` (
  `semester_id` int(11) NOT NULL,
  `semester_name` varchar(20) DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  `end_date` date DEFAULT NULL,
  `academic_year_id` int(11) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `semesters`
--

INSERT INTO `semesters` (`semester_id`, `semester_name`, `start_date`, `end_date`, `academic_year_id`) VALUES
(0, 'First Semester', '2021-09-15', '2022-01-31', 1),
(1, 'First Semester', '2021-09-15', '2022-01-31', 1),
(2, 'Second Semester', '2022-02-15', '2022-06-30', 1),
(3, 'First Semester', '2022-09-15', '2023-01-31', 2),
(4, 'Second Semester', '2023-02-15', '2023-06-30', 2),
(5, 'First Semester', '2023-09-15', '2024-01-31', 3),
(6, 'Second Semester', '2024-02-15', '2024-06-30', 3),
(7, 'First Semester', '2024-09-15', '2025-01-31', 4),
(8, 'Second Semester', '2025-02-15', '2025-06-30', 4),
(9, 'First Semester', '2025-09-15', '2026-01-31', 5),
(10, 'Second Semester', '2026-02-15', '2026-06-30', 5);

-- --------------------------------------------------------

--
-- Table structure for table `students`
--

CREATE TABLE `students` (
  `student_id` int(11) NOT NULL,
  `full_name` varchar(100) DEFAULT NULL,
  `national_id` varchar(20) DEFAULT NULL,
  `email` varchar(100) DEFAULT NULL,
  `phone` varchar(15) DEFAULT NULL,
  `academic_year_id` int(11) DEFAULT NULL,
  `semester_id` int(11) DEFAULT NULL,
  `academic_level_id` int(11) DEFAULT NULL,
  `faculty_id` int(11) DEFAULT NULL,
  `department_id` int(11) DEFAULT NULL,
  `group_number` varchar(10) DEFAULT NULL,
  `section_number` varchar(10) DEFAULT NULL,
  `enrollment_date` date DEFAULT NULL,
  `GPA` decimal(3,2) DEFAULT NULL,
  `final_grade` varchar(2) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `students`
--

INSERT INTO `students` (`student_id`, `full_name`, `national_id`, `email`, `phone`, `academic_year_id`, `semester_id`, `academic_level_id`, `faculty_id`, `department_id`, `group_number`, `section_number`, `enrollment_date`, `GPA`, `final_grade`) VALUES
(1, 'Ahmed Hassan Ali', '30101010000001', 'ahmed1@gmail.com', '01010000001', 1, 1, 1, 1, 1, '1', '1', '2021-09-15', '3.10', 'B'),
(2, 'Ahmed Hassan Ali', '30101010000001', 'ahmed1@gmail.com', '01010000001', 1, 1, 1, 1, 1, '1', '1', '2021-09-15', '3.10', 'B'),
(3, 'Mohamed Salah Eid', '30101010000002', 'mohamed1@gmail.com', '01010000002', 1, 1, 1, 1, 2, '1', '2', '2021-09-15', '3.50', 'A-'),
(4, 'Omar Yasser Khidr', '30101010000003', 'omar1@gmail.com', '01010000003', 1, 2, 1, 2, 4, '2', '1', '2021-09-15', '3.80', 'A'),
(5, 'Karim Adel Nasser', '30102020000004', 'karim2@gmail.com', '01020000004', 2, 3, 2, 1, 1, '1', '1', '2022-09-15', '3.00', 'B'),
(6, 'Youssef Ahmed Salem', '30102020000005', 'youssef2@gmail.com', '01020000005', 2, 4, 2, 1, 3, '1', '2', '2022-09-15', '2.70', 'C+'),
(7, 'Hassan Mostafa Eid', '30102020000006', 'hassan2@gmail.com', '01020000006', 2, 3, 2, 2, 5, '2', '1', '2022-09-15', '3.40', 'B+'),
(8, 'Ali Mahmoud Ibrahim', '30103030000007', 'ali3@gmail.com', '01030000007', 3, 5, 3, 3, 7, '1', '1', '2023-09-15', '3.60', 'A-'),
(9, 'Mahmoud Tarek Fathy', '30103030000008', 'mahmoud3@gmail.com', '01030000008', 3, 6, 3, 3, 8, '1', '2', '2023-09-15', '2.90', 'C+'),
(10, 'Islam Reda Abdelrahman', '30103030000009', 'islam3@gmail.com', '01030000009', 3, 5, 3, 4, 10, '2', '1', '2023-09-15', '3.85', 'A'),
(11, 'Amr Khaled Shawky', '30104040000010', 'amr4@gmail.com', '01040000010', 4, 7, 4, 4, 11, '1', '1', '2024-09-15', '3.20', 'B'),
(12, 'Mostafa Ibrahim Adel', '30104040000011', 'mostafa4@gmail.com', '01040000011', 4, 8, 4, 4, 12, '1', '2', '2024-09-15', '3.55', 'A-'),
(13, 'Ziad Mahmoud Saber', '30104040000012', 'ziad4@gmail.com', '01040000012', 4, 7, 4, 5, 14, '2', '1', '2024-09-15', '3.00', 'B'),
(14, 'Fady Nabil George', '30105050000013', 'fady@gmail.com', '01050000013', 5, 9, 1, 5, 15, '1', '1', '2025-09-15', '2.80', 'C'),
(15, 'Mina Sameh Rizk', '30105050000014', 'mina@gmail.com', '01050000014', 5, 10, 2, 2, 6, '2', '2', '2025-09-15', '3.10', 'B'),
(16, 'Seif Ahmed Lotfy', '30105050000015', 'seif@gmail.com', '01050000015', 5, 9, 3, 1, 2, '1', '1', '2025-09-15', '3.90', 'A'),
(17, 'Nourhan Adel Mahmoud', '30106060000016', 'nourhan@gmail.com', '01060000016', 3, 6, 3, 1, 3, '2', '2', '2023-09-15', '3.70', 'A-'),
(18, 'Salma Ahmed Fawzy', '30106060000017', 'salma@gmail.com', '01060000017', 2, 4, 2, 2, 5, '1', '1', '2022-09-15', '3.30', 'B+'),
(19, 'Menna Tarek Samy', '30106060000018', 'menna@gmail.com', '01060000018', 1, 2, 1, 5, 14, '2', '1', '2021-09-15', '3.95', 'A'),
(20, 'Student 01', '301000000001', 's1@mail.com', '01000000001', 1, 1, 1, 1, 1, '1', '1', '2021-09-15', '3.10', 'B'),
(21, 'Student 02', '301000000002', 's2@mail.com', '01000000002', 1, 2, 1, 1, 2, '1', '2', '2021-09-15', '3.50', 'A-'),
(22, 'Student 03', '301000000003', 's3@mail.com', '01000000003', 1, 1, 1, 2, 4, '2', '1', '2021-09-15', '2.90', 'C+'),
(23, 'Student 04', '301000000004', 's4@mail.com', '01000000004', 1, 2, 1, 3, 7, '2', '2', '2021-09-15', '3.80', 'A'),
(24, 'Student 05', '301000000005', 's5@mail.com', '01000000005', 1, 1, 1, 4, 10, '1', '1', '2021-09-15', '3.00', 'B'),
(25, 'Student 06', '301000000006', 's6@mail.com', '01000000006', 2, 3, 2, 1, 1, '1', '1', '2022-09-15', '2.80', 'C'),
(26, 'Student 07', '301000000007', 's7@mail.com', '01000000007', 2, 4, 2, 1, 3, '1', '2', '2022-09-15', '3.40', 'B+'),
(27, 'Student 08', '301000000008', 's8@mail.com', '01000000008', 2, 3, 2, 2, 5, '2', '1', '2022-09-15', '3.70', 'A-'),
(28, 'Student 09', '301000000009', 's9@mail.com', '01000000009', 2, 4, 2, 3, 8, '2', '2', '2022-09-15', '2.60', 'C'),
(29, 'Student 10', '301000000010', 's10@mail.com', '01000000010', 2, 3, 2, 4, 11, '1', '1', '2022-09-15', '3.90', 'A'),
(30, 'Student 11', '301000000011', 's11@mail.com', '01000000011', 3, 5, 3, 1, 2, '1', '1', '2023-09-15', '3.20', 'B'),
(31, 'Student 12', '301000000012', 's12@mail.com', '01000000012', 3, 6, 3, 2, 6, '2', '1', '2023-09-15', '3.60', 'A-'),
(32, 'Student 13', '301000000013', 's13@mail.com', '01000000013', 3, 5, 3, 3, 7, '1', '2', '2023-09-15', '2.95', 'C+'),
(33, 'Student 14', '301000000014', 's14@mail.com', '01000000014', 3, 6, 3, 4, 10, '2', '2', '2023-09-15', '3.85', 'A'),
(34, 'Student 15', '301000000015', 's15@mail.com', '01000000015', 3, 5, 3, 5, 14, '1', '1', '2023-09-15', '3.00', 'B'),
(35, 'Student 16', '301000000016', 's16@mail.com', '01000000016', 4, 7, 4, 1, 1, '1', '1', '2024-09-15', '3.40', 'B+'),
(36, 'Student 17', '301000000017', 's17@mail.com', '01000000017', 4, 8, 4, 2, 5, '2', '1', '2024-09-15', '3.75', 'A-'),
(37, 'Student 18', '301000000018', 's18@mail.com', '01000000018', 5, 9, 1, 3, 8, '1', '2', '2025-09-15', '3.10', 'B'),
(38, 'Student 19', '301000000019', 's19@mail.com', '01000000019', 5, 10, 2, 4, 11, '2', '2', '2025-09-15', '3.55', 'A-'),
(39, 'Student 20', '301000000020', 's20@mail.com', '01000000020', 5, 9, 3, 5, 15, '1', '1', '2025-09-15', '2.90', 'C+'),
(100, 'Omar Yasser Mohamed', '30301011234567', 'omar@gmail.com', '01012345678', 1, 1, 2, 1, 3, '1', '2', '2024-09-20', '3.45', 'B+');

-- --------------------------------------------------------

--
-- Table structure for table `student_course_enrollment`
--

CREATE TABLE `student_course_enrollment` (
  `student_course_id` int(11) NOT NULL,
  `student_id` int(11) DEFAULT NULL,
  `course_id` int(11) DEFAULT NULL,
  `academic_year_id` int(11) DEFAULT NULL,
  `semester_id` int(11) DEFAULT NULL,
  `enrollment_date` date DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `student_course_enrollment`
--

INSERT INTO `student_course_enrollment` (`student_course_id`, `student_id`, `course_id`, `academic_year_id`, `semester_id`, `enrollment_date`) VALUES
(1, 1, 1, 3, 5, '2023-09-20'),
(2, 1, 1, 3, 5, '2023-09-20'),
(3, 1, 2, 3, 5, '2023-09-20'),
(4, 2, 1, 3, 5, '2023-09-20'),
(5, 2, 3, 3, 5, '2023-09-20'),
(6, 3, 2, 3, 6, '2024-02-20'),
(7, 3, 4, 3, 6, '2024-02-20'),
(8, 4, 1, 4, 7, '2024-09-20'),
(9, 4, 5, 4, 7, '2024-09-20'),
(10, 5, 3, 4, 8, '2025-02-20'),
(11, 5, 6, 4, 8, '2025-02-20');

-- --------------------------------------------------------

--
-- Table structure for table `system_user`
--

CREATE TABLE `system_user` (
  `user_id` int(11) NOT NULL,
  `username` varchar(100) DEFAULT NULL,
  `password_hash` varchar(255) DEFAULT NULL,
  `user_type` varchar(20) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `system_user`
--

INSERT INTO `system_user` (`user_id`, `username`, `password_hash`, `user_type`) VALUES
(1, 'admin', 'hashed_admin_123', 'Admin'),
(2, 'omar', 'hashed_omar_123', 'Student'),
(3, 'ahmed', 'hashed_ahmed_123', 'Student'),
(4, 'mohamed', 'hashed_mohamed_123', 'Instructor'),
(5, 'sara', 'hashed_sara_123', 'Student'),
(6, 'karim', 'hashed_karim_123', 'Instructor'),
(7, 'it_admin', 'hashed_it_123', 'Staff');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `academic_calendar`
--
ALTER TABLE `academic_calendar`
  ADD PRIMARY KEY (`calendar_id`),
  ADD KEY `academic_year_id` (`academic_year_id`),
  ADD KEY `semester_id` (`semester_id`);

--
-- Indexes for table `academic_levels`
--
ALTER TABLE `academic_levels`
  ADD PRIMARY KEY (`level_id`);

--
-- Indexes for table `academic_schedule`
--
ALTER TABLE `academic_schedule`
  ADD PRIMARY KEY (`schedule_id`),
  ADD KEY `course_id` (`course_id`),
  ADD KEY `instructor_id` (`instructor_id`),
  ADD KEY `academic_year_id` (`academic_year_id`),
  ADD KEY `semester_id` (`semester_id`),
  ADD KEY `location_id` (`location_id`);

--
-- Indexes for table `academic_years`
--
ALTER TABLE `academic_years`
  ADD PRIMARY KEY (`academic_year_id`);

--
-- Indexes for table `administration_users`
--
ALTER TABLE `administration_users`
  ADD PRIMARY KEY (`admin_id`);

--
-- Indexes for table `attendance`
--
ALTER TABLE `attendance`
  ADD PRIMARY KEY (`attendance_id`),
  ADD KEY `fk_attendance_student` (`student_id`),
  ADD KEY `fk_attendance_course` (`course_id`),
  ADD KEY `fk_attendance_semester` (`semester_id`);

--
-- Indexes for table `courses`
--
ALTER TABLE `courses`
  ADD PRIMARY KEY (`course_id`);

--
-- Indexes for table `departments`
--
ALTER TABLE `departments`
  ADD PRIMARY KEY (`department_id`),
  ADD KEY `fk_departments_faculty` (`faculty_id`);

--
-- Indexes for table `faculties`
--
ALTER TABLE `faculties`
  ADD PRIMARY KEY (`faculty_id`);

--
-- Indexes for table `fees`
--
ALTER TABLE `fees`
  ADD PRIMARY KEY (`fee_id`),
  ADD KEY `student_id` (`student_id`),
  ADD KEY `academic_year_id` (`academic_year_id`),
  ADD KEY `semester_id` (`semester_id`);

--
-- Indexes for table `grades`
--
ALTER TABLE `grades`
  ADD PRIMARY KEY (`grade_id`),
  ADD KEY `student_id` (`student_id`),
  ADD KEY `course_id` (`course_id`),
  ADD KEY `semester_id` (`semester_id`);

--
-- Indexes for table `instructors`
--
ALTER TABLE `instructors`
  ADD PRIMARY KEY (`instructor_id`),
  ADD KEY `fk_instructors_faculty` (`faculty_id`),
  ADD KEY `fk_instructors_department` (`department_id`);

--
-- Indexes for table `instructor_course_assignment`
--
ALTER TABLE `instructor_course_assignment`
  ADD PRIMARY KEY (`id`),
  ADD KEY `fk_ica_instructor` (`instructor_id`),
  ADD KEY `fk_ica_course` (`course_id`),
  ADD KEY `fk_ica_academic_year` (`academic_year_id`),
  ADD KEY `fk_ica_semester` (`semester_id`);

--
-- Indexes for table `laboratories`
--
ALTER TABLE `laboratories`
  ADD PRIMARY KEY (`lab_id`);

--
-- Indexes for table `lecture_halls`
--
ALTER TABLE `lecture_halls`
  ADD PRIMARY KEY (`hall_id`);

--
-- Indexes for table `locations`
--
ALTER TABLE `locations`
  ADD PRIMARY KEY (`location_id`),
  ADD KEY `fk_locations_hall` (`hall_id`),
  ADD KEY `fk_locations_lab` (`lab_id`);

--
-- Indexes for table `news`
--
ALTER TABLE `news`
  ADD PRIMARY KEY (`news_id`),
  ADD KEY `fk_news_admin_user` (`posted_by_user_id`);

--
-- Indexes for table `semesters`
--
ALTER TABLE `semesters`
  ADD PRIMARY KEY (`semester_id`),
  ADD KEY `academic_year_id` (`academic_year_id`);

--
-- Indexes for table `students`
--
ALTER TABLE `students`
  ADD PRIMARY KEY (`student_id`),
  ADD KEY `academic_year_id` (`academic_year_id`),
  ADD KEY `semester_id` (`semester_id`),
  ADD KEY `academic_level_id` (`academic_level_id`),
  ADD KEY `faculty_id` (`faculty_id`),
  ADD KEY `department_id` (`department_id`);

--
-- Indexes for table `student_course_enrollment`
--
ALTER TABLE `student_course_enrollment`
  ADD PRIMARY KEY (`student_course_id`),
  ADD KEY `student_id` (`student_id`),
  ADD KEY `course_id` (`course_id`),
  ADD KEY `academic_year_id` (`academic_year_id`),
  ADD KEY `semester_id` (`semester_id`);

--
-- Indexes for table `system_user`
--
ALTER TABLE `system_user`
  ADD PRIMARY KEY (`user_id`),
  ADD UNIQUE KEY `username` (`username`) USING BTREE;

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `academic_calendar`
--
ALTER TABLE `academic_calendar`
  MODIFY `calendar_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- AUTO_INCREMENT for table `academic_levels`
--
ALTER TABLE `academic_levels`
  MODIFY `level_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `academic_schedule`
--
ALTER TABLE `academic_schedule`
  MODIFY `schedule_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT for table `academic_years`
--
ALTER TABLE `academic_years`
  MODIFY `academic_year_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `administration_users`
--
ALTER TABLE `administration_users`
  MODIFY `admin_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `attendance`
--
ALTER TABLE `attendance`
  MODIFY `attendance_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `courses`
--
ALTER TABLE `courses`
  MODIFY `course_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=38;

--
-- AUTO_INCREMENT for table `departments`
--
ALTER TABLE `departments`
  MODIFY `department_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT for table `faculties`
--
ALTER TABLE `faculties`
  MODIFY `faculty_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `fees`
--
ALTER TABLE `fees`
  MODIFY `fee_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;

--
-- AUTO_INCREMENT for table `grades`
--
ALTER TABLE `grades`
  MODIFY `grade_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `instructors`
--
ALTER TABLE `instructors`
  MODIFY `instructor_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=29;

--
-- AUTO_INCREMENT for table `instructor_course_assignment`
--
ALTER TABLE `instructor_course_assignment`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `laboratories`
--
ALTER TABLE `laboratories`
  MODIFY `lab_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=31;

--
-- AUTO_INCREMENT for table `lecture_halls`
--
ALTER TABLE `lecture_halls`
  MODIFY `hall_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `locations`
--
ALTER TABLE `locations`
  MODIFY `location_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `news`
--
ALTER TABLE `news`
  MODIFY `news_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `students`
--
ALTER TABLE `students`
  MODIFY `student_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=101;

--
-- AUTO_INCREMENT for table `student_course_enrollment`
--
ALTER TABLE `student_course_enrollment`
  MODIFY `student_course_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT for table `system_user`
--
ALTER TABLE `system_user`
  MODIFY `user_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
