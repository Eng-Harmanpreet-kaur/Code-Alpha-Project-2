🎓 CGPA Calculator

A C++ Console Application for Semester GPA and Cumulative GPA Calculation

Add Semesters · Record Grades · Calculate SGPA · Track Overall CGPA

📌 Overview

The CGPA Calculator is a terminal-based application developed in C++. It helps students record course names, credit hours, and grades for each semester, calculate semester GPA (SGPA), and view their overall CGPA.

The application uses standard C++ file handling to save academic records in a text file. Previously saved records are loaded when the program starts, allowing students to continue using the calculator without entering their records again.

✨ Key Features

Feature

Description

➕ Add Semester

Enter courses for a new semester.

📚 Course Records

Store course names, credit hours, and grades.

🧮 SGPA Calculation

Calculate the GPA for a selected semester using credits and grade points.

🎓 Overall CGPA

Calculate cumulative GPA from all saved courses.

📋 Academic Summary

View all course records and semester-wise GPA.

💾 Persistent Storage

Save and reload records using a text file.

🛡️ Input Validation

Check menu choices, credits, and supported grades.

🗑️ Reset Records

Clear saved academic records after confirmation.

📈 Grading Scale

Display the grade-point scale used by the program.

🧮 GPA and CGPA Calculation

The application uses the following grade-point mapping:

CGPA Formula
CGPA = ∑(Grade Point×Credits)​ / ∑Credits

🧰 Technology Stack

Programming Language: C++

C++ Standard: C++11

Interface: Command-Line Interface (CLI)

File Handling: fstream, ifstream, ofstream

Data Structures: Structures and vectors

Storage Format: .txt file

Input Validation: Conditions, loops, and input checks

🗂️ Project Structure

CGPA-Calculator/
│
├── CGPA_Calculator.cpp
├── README.md
└── cgpa_records.txt    # Created by the application when needed

File

Purpose

CGPA_Calculator.cpp

Contains the C++ source code.

README.md

Project documentation.

cgpa_records.txt

Stores semester-wise course and grade records. The application creates this file when needed.

🚀 Getting Started

1. Prerequisites

Windows computer

Visual Studio Code

A C++ compiler such as g++ (MinGW-w64)

2. Compile the Program

Open the project folder in VS Code, open the terminal, and run:

g++ -std=c++11 -Wall -Wextra -pedantic CGPA_Calculator.cpp -o CGPA_Calculator.exe

3. Run the Program

In Windows PowerShell, execute:

.\CGPA_Calculator.exe

4. Use the Application

The main menu provides these options:

Add a new semester

View overall CGPA and all records

View results of a particular semester

View the grading scale

Reset all saved records

Save and exit

Enter the menu number and follow the prompts to record courses, select grades, and view the calculated results.

💾 How File Handling Works

The application uses cgpa_records.txt to store course records. Each record includes the semester number, course name, credits, grade, and grade point.

When the program starts, it reads the saved records from the file. When a semester is added or records are reset, the application updates the file so the information is available the next time the program runs.

🎯 Project Objectives

Develop a menu-driven C++ console application.

Practise structures, vectors, and functions.

Use file handling to preserve academic records.

Calculate SGPA and CGPA using credit-weighted grade points.

Apply input validation and basic error handling.

Organize course information in a readable report.

⚠️ Current Limitations

The grading scale is predefined in the source code.

Records are stored locally in a text file.

The application does not use a database or graphical interface.

The application records grades and credits entered by the user; results depend on the accuracy of that input.

🔮 Possible Future Improvements

Add editing and deleting options for individual course records.

Add student profiles and sign-in functionality.

Add semester-wise printable reports.

Allow configurable college grading scales.

Add a graphical user interface.

👩‍💻 Developed by Harmanpreet Kaur

B.Tech — Computer Science & Engineering

Built with C++ and file handling.
