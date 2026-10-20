Student Record & CGPA System

About the Project

The Student Record & CGPA System is a terminal-based application developed using C++. It allows students to create accounts, sign in using their credentials, manage their academic records, and calculate their CGPA based on subject marks and credits.

The project uses C++ file handling to store student account information and academic records in files. Each student has a separate data file identified by their name and student ID, allowing them to access and manage their own academic information.

Features

Student Sign Up

Register using a student ID, student name, and password.

Check whether the student ID or name already exists.

Prevent duplicate account registration.

Ask existing students to sign in instead of creating another account.

Student Sign In

Verify the student ID, name, and password.

Allow access only when the entered credentials match the registered account.

Display an error message when the credentials are incorrect.

Load the student's academic records after successful authentication.

Student Record Management

Store each student's academic records in a separate .dat file.

Save the student's name and ID along with their academic information.

Load previously saved records when the student signs in.

Maintain records after the application is closed.

Subject Management

Students can:

Add a subject with marks and credit hours.

Update a subject name, marks, or credits.

Remove a subject from their academic record.

View all subjects, marks, credits, and grade points.

The program also checks for duplicate subject names.

Automatic CGPA Calculation

The system calculates CGPA using subject marks and credit hours.

Marks

Grade Point

90–100

10

80–89.99

9

70–79.99

8

60–69.99

7

50–59.99

6

40–49.99

5

Below 40

0

The formula used is:

CGPA = Sum of (Grade Point × Credits) / Sum of Credits

The CGPA is recalculated after a subject is added, updated, or removed.

Note: This is the grading scale implemented in the current code. Update it according to your college's official grading rules if required.

Technologies Used

Programming Language: C++

Interface: Command-Line Interface (CLI)

File Handling: fstream, ifstream, ofstream

Data Storage: .txt and .dat files

Data Structures: Structures and vectors

Input Validation: Conditional statements and loops

Calculations: Functions and arithmetic operations

Project Structure

Student-Record-CGPA-System/
├── Student_Record_CGPA_System.cpp
├── student_accounts.txt
├── StudentName_StudentID.dat
└── README.md

Student_Record_CGPA_System.cpp — Contains the C++ source code.

student_accounts.txt — Stores registered students' IDs, names, passwords, and data file names.

StudentName_StudentID.dat — Stores an individual student's academic records.

README.md — Contains project documentation.

The account file and individual student data files are created by the program when required.

How to Run

1. Install a C++ Compiler

Install a C++ compiler such as MinGW-w64 and configure it in Visual Studio Code.

2. Open the Project

Open the project folder in VS Code and open the terminal.

3. Compile the Program

g++ -std=c++11 -Wall -Wextra -pedantic Student_Record_CGPA_System.cpp -o Student_Record_CGPA_System.exe

4. Run the Program

On Windows PowerShell:

.\Student_Record_CGPA_System.exe

5. Use the Application

The main menu provides these options:

Student Sign Up

Student Sign In

Exit

After signing in, students can use the dashboard to manage subjects, update marks, remove subjects, view academic records, and calculate their CGPA.

How File Handling Works

Account File

The student_accounts.txt file contains registered account information used to identify a student and locate their individual data file.

Individual Student File

Each student's filename is generated using their name and ID. For example:

Harmanpreet_CSE101.dat

The file stores the student's ID, name, subject count, subject names, marks, and credit hours.

When a student signs in, the application verifies the credentials and loads the corresponding academic record. Subject changes are saved to that student's file.

Project Objectives

Develop a menu-driven C++ application.

Implement student registration and sign-in.

Understand file handling and persistent data storage.

Manage academic records using structures and vectors.

Implement functions to add, update, and remove subjects.

Calculate CGPA using grade points and credit hours.

Apply input validation and basic error handling.

Limitations

Passwords are stored as plain text in the account file.

The grading scale is predefined in the source code.

Student records are stored locally in files.

The application does not use a database.

Future Enhancements

Password hashing for improved account security.

Semester-wise academic record management.

Subject-wise grade calculation and academic reports.

Export academic reports to a file.

A graphical user interface.

Author

Harmanpreet Kaur
B.Tech Computer Science and Engineering

License

This project is intended for educational and learning purposes.
