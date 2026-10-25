# 🎓 Student Record & CGPA System

## 📌 About the Project

The **Student Record & CGPA System** is a menu-driven C++ application that helps students manage their academic records. Students can create an account, log in, manage subjects, update marks, and calculate their CGPA.

This project is developed using basic C++ concepts, data structures, file handling, and exception handling. Student records are stored in text and data files, so the information can be accessed again after restarting the program.

The main goal of this project is to apply Data Structures and C++ programming concepts to solve a real-world problem.

## ✨ Features

* 📝 **Student Sign Up:** Create a new student account.
* 🔐 **Student Sign In:** Log in using Student ID, name, and password.
* ➕ **Add Subject:** Add subjects with marks and credits.
* 📋 **View Subjects:** Display all subjects, marks, credits, and grade points.
* ✏️ **Update Subject:** Update subject names, marks, or credits.
* 🗑️ **Remove Subject:** Remove a subject with a confirmation option.
* 🧮 **CGPA Calculation:** Calculate CGPA using grade points and subject credits.
* 🔍 **Search Subject:** Search for subjects by name or part of the name.
* 📊 **Sort Subjects:** Arrange subjects by marks from highest to lowest.
* 📈 **Academic Summary:** View total subjects, average marks, highest marks, lowest marks, passed subjects, and subjects below passing marks.
* 🔑 **Change Password:** Change the account password after verifying the current password.
* 💾 **File Handling:** Save and retrieve student accounts and academic records using files.
* 🛡️ **Input Validation:** Check user input and restrict invalid marks, credits, and menu choices.
* ⚠️ **Exception Handling:** Handle certain invalid data and unexpected input errors.

## 🛠️ Technologies Used

* **Programming Language:** C++
* **Compiler Standard:** C++11
* **Data Storage:** Text files and `.dat` files
* **File Handling:** `ifstream`, `ofstream`, and `stringstream`
* **Data Structures:** Structures and vectors

## 🧠 C++ Concepts Used

### 1. Structures

The project uses two structures:

* `Student` — stores the student's ID, name, password, and subjects.
* `Subject` — stores the subject name, marks, and credits.

Structures help organize related information in a simple and understandable way.

### 2. Vector

The project uses `vector<Subject>` to store multiple subjects for each student.

A vector can grow or shrink when subjects are added or removed, so there is no need to use a fixed-size array for subject records.

### 3. Searching

Linear search is used to find subjects by name. The search can match the complete name or part of the name.

### 4. Sorting

Bubble sort is used to arrange subjects according to marks in descending order.

### 5. Functions

The program is divided into separate functions for tasks such as registration, login, adding subjects, updating records, searching, sorting, and calculating CGPA.

This makes the program easier to read, understand, test, and maintain.

### 6. Exception Handling

`try-catch` blocks handle certain conversion errors and unexpected input termination. Input validation is also used to prevent invalid values from being accepted.

### 7. File Handling

The program uses basic C++ file streams to save and read student information.

This allows academic records to remain available when the program is closed and opened again.

## 📂 Files Used

### `student_accounts.txt`

Stores account information, including Student ID, student name, password, and the name of the student's data file.

### Student Data Files

Each student has a separate `.dat` file containing their ID, name, and subject records.

### Temporary Account File

`student_accounts_temp.txt` is used when changing a password so the account records can be rewritten with the updated password.

These files are created and managed by the program when required.

## 🧮 CGPA Calculation

The program assigns grade points according to the marks entered for each subject.

| Marks    | Grade Point |
| -------- | ----------: |
| 90–100   |          10 |
| 80–89.99 |           9 |
| 70–79.99 |           8 |
| 60–69.99 |           7 |
| 50–59.99 |           6 |
| 40–49.99 |           5 |
| Below 40 |           0 |

The CGPA is calculated using the following formula:

**CGPA = Sum of (Grade Point × Subject Credits) / Total Credits**

The grading scale should be checked against your colle
