#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
#include <cstdio>

using namespace std;

const string INDEX_FILE = "student_accounts.txt";

struct Subject {
    string name;
    double marks;
    int credits;
};

struct Student {
    string id;
    string name;
    string password;
    vector<Subject> subjects;
};

string trim(const string& value) {
    size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

string toUpperCase(string value) {
    for (size_t i = 0; i < value.size(); ++i) {
        value[i] = static_cast<char>(toupper(static_cast<unsigned char>(value[i])));
    }
    return value;
}

void clearInputLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string readNonEmptyLine(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        value = trim(value);
        if (!value.empty() && value.find('|') == string::npos) {
            return value;
        }
        cout << "Input cannot be empty or contain the '|' character. Try again.\n";
    }
}

int readInt(const string& prompt, int minimum, int maximum) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minimum && value <= maximum) {
            clearInputLine();
            return value;
        }
        cout << "Enter a whole number between " << minimum << " and " << maximum << ".\n";
        clearInputLine();
    }
}

double readDouble(const string& prompt, double minimum, double maximum) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minimum && value <= maximum) {
            clearInputLine();
            return value;
        }
        cout << "Enter a number between " << minimum << " and " << maximum << ".\n";
        clearInputLine();
    }
}

bool isSafeFilePart(const string& value) {
    if (value.empty()) {
        return false;
    }

    for (size_t i = 0; i < value.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(value[i]);
        if (!(isalnum(ch) || ch == '_' || ch == '-')) {
            return false;
        }
    }
    return true;
}

string makeStudentFileName(const string& studentName, const string& studentId) {
    string safeName;
    for (size_t i = 0; i < studentName.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(studentName[i]);
        if (isalnum(ch) || ch == '_' || ch == '-') {
            safeName += static_cast<char>(ch);
        } else if (ch == ' ' && !safeName.empty() && safeName[safeName.size() - 1] != '_') {
            safeName += '_';
        }
    }

    while (!safeName.empty() && safeName[safeName.size() - 1] == '_') {
        safeName.erase(safeName.size() - 1);
    }

    if (safeName.empty()) {
        safeName = "Student";
    }

    return safeName + "_" + studentId + ".dat";
}

bool accountExists(const string& studentId, const string& studentName) {
    ifstream file(INDEX_FILE.c_str());
    string line;

    while (getline(file, line)) {
        string storedId, storedName, storedPassword, storedFile;
        stringstream parser(line);

        if (getline(parser, storedId, '|') &&
            getline(parser, storedName, '|') &&
            getline(parser, storedPassword, '|') &&
            getline(parser, storedFile)) {
            if (storedId == studentId || toUpperCase(storedName) == toUpperCase(studentName)) {
                return true;
            }
        }
    }

    return false;
}

bool findAccountById(const string& studentId, Student& student, string& dataFileName) {
    ifstream file(INDEX_FILE.c_str());
    string line;

    while (getline(file, line)) {
        string storedId, storedName, storedPassword, storedFile;
        stringstream parser(line);

        if (getline(parser, storedId, '|') &&
            getline(parser, storedName, '|') &&
            getline(parser, storedPassword, '|') &&
            getline(parser, storedFile)) {
            if (storedId == studentId) {
                student.id = storedId;
                student.name = storedName;
                student.password = storedPassword;
                dataFileName = storedFile;
                return true;
            }
        }
    }

    return false;
}

bool saveStudentData(const Student& student, const string& dataFileName) {
    ofstream file(dataFileName.c_str(), ios::out | ios::trunc);

    if (!file.is_open()) {
        cout << "Error: Unable to open the student data file for saving.\n";
        return false;
    }

    file << student.id << '\n';
    file << student.name << '\n';
    file << student.subjects.size() << '\n';
    file << fixed << setprecision(2);

    for (size_t i = 0; i < student.subjects.size(); ++i) {
        file << student.subjects[i].name << '|'
             << student.subjects[i].marks << '|'
             << student.subjects[i].credits << '\n';
    }

    file.close();

    if (file.fail()) {
        cout << "Error: Could not save the complete student record.\n";
        return false;
    }

    return true;
}

bool loadStudentData(Student& student, const string& dataFileName) {
    ifstream file(dataFileName.c_str());

    if (!file.is_open()) {
        cout << "Error: Student data file could not be opened.\n";
        return false;
    }

    string countLine;
    if (!getline(file, student.id) || !getline(file, student.name) || !getline(file, countLine)) {
        cout << "Error: Student data file is incomplete or damaged.\n";
        return false;
    }

    int count = 0;
    try {
        count = stoi(countLine);
    } catch (...) {
        cout << "Error: Invalid subject count in student data file.\n";
        return false;
    }

    if (count < 0 || count > 200) {
        cout << "Error: Invalid subject count in student data file.\n";
        return false;
    }

    student.subjects.clear();

    for (int i = 0; i < count; ++i) {
        string line, subjectName, marksText, creditsText;
        if (!getline(file, line)) {
            cout << "Error: Student data file ended unexpectedly.\n";
            return false;
        }

        stringstream parser(line);
        if (!getline(parser, subjectName, '|') ||
            !getline(parser, marksText, '|') ||
            !getline(parser, creditsText)) {
            cout << "Error: Invalid subject record in student data file.\n";
            return false;
        }

        Subject subject;
        subject.name = subjectName;

        try {
            subject.marks = stod(marksText);
            subject.credits = stoi(creditsText);
        } catch (...) {
            cout << "Error: Invalid marks or credits in student data file.\n";
            return false;
        }

        if (subject.marks < 0 || subject.marks > 100 || subject.credits < 1 || subject.credits > 30) {
            cout << "Error: Subject data is outside the allowed range.\n";
            return false;
        }

        student.subjects.push_back(subject);
    }

    return true;
}

bool saveAccountIndex(const string& studentId, const string& studentName,
                      const string& password, const string& dataFileName) {
    ofstream file(INDEX_FILE.c_str(), ios::out | ios::app);

    if (!file.is_open()) {
        cout << "Error: Unable to open the account index file.\n";
        return false;
    }

    file << studentId << '|'
         << studentName << '|'
         << password << '|'
         << dataFileName << '\n';

    file.close();
    return !file.fail();
}

bool signUp(Student& student, string& dataFileName) {
    cout << "\n========== Student Sign Up ==========\n";

    student.id = readNonEmptyLine("Create student ID (letters, digits, _ or -): ");
    if (!isSafeFilePart(student.id)) {
        cout << "Invalid student ID. Use only letters, digits, '_' or '-'.\n";
        return false;
    }

    student.name = readNonEmptyLine("Enter student name: ");
    if (student.name.find('|') != string::npos) {
        cout << "Student name contains an invalid character.\n";
        return false;
    }

    if (accountExists(student.id, student.name)) {
        cout << "An account with this student ID or student name already exists.\n";
        cout << "Please sign in instead of creating another account.\n";
        return false;
    }

    student.password = readNonEmptyLine("Create password: ");
    if (student.password.find('|') != string::npos) {
        cout << "Password cannot contain the '|' character.\n";
        return false;
    }

    dataFileName = makeStudentFileName(student.name, student.id);
    student.subjects.clear();

    ofstream dataFile(dataFileName.c_str(), ios::out | ios::trunc);
    if (!dataFile.is_open()) {
        cout << "Error: Could not create the student data file.\n";
        return false;
    }
    dataFile.close();

    if (!saveStudentData(student, dataFileName)) {
        remove(dataFileName.c_str());
        return false;
    }

    if (!saveAccountIndex(student.id, student.name, student.password, dataFileName)) {
        remove(dataFileName.c_str());
        cout << "Error: Account could not be registered.\n";
        return false;
    }

    cout << "Sign up successful. Your personal record file is " << dataFileName << ".\n";
    cout << "Please sign in to access your student dashboard.\n";
    return true;
}

bool signIn(Student& student, string& dataFileName) {
    cout << "\n========== Student Sign In ==========\n";

    string studentId = readNonEmptyLine("Enter student ID: ");
    string studentName = readNonEmptyLine("Enter student name: ");
    string password = readNonEmptyLine("Enter password: ");

    Student storedStudent;
    string storedFileName;

    if (!findAccountById(studentId, storedStudent, storedFileName)) {
        cout << "No account found for this student ID. Please sign up first.\n";
        return false;
    }

    if (toUpperCase(storedStudent.name) != toUpperCase(studentName) ||
        storedStudent.password != password) {
        cout << "Student ID, name, or password is incorrect. Access denied.\n";
        return false;
    }

    student = storedStudent;
    dataFileName = storedFileName;

    if (!loadStudentData(student, dataFileName)) {
        cout << "Could not load your record. Access denied.\n";
        return false;
    }

    cout << "Sign in successful. Welcome, " << student.name << "!\n";
    return true;
}

double gradePointFromMarks(double marks) {
    if (marks >= 90) return 10.0;
    if (marks >= 80) return 9.0;
    if (marks >= 70) return 8.0;
    if (marks >= 60) return 7.0;
    if (marks >= 50) return 6.0;
    if (marks >= 40) return 5.0;
    return 0.0;
}

double calculateCGPA(const Student& student) {
    int totalCredits = 0;
    double weightedPoints = 0.0;

    for (size_t i = 0; i < student.subjects.size(); ++i) {
        double point = gradePointFromMarks(student.subjects[i].marks);
        totalCredits += student.subjects[i].credits;
        weightedPoints += point * student.subjects[i].credits;
    }

    if (totalCredits == 0) {
        return 0.0;
    }

    return weightedPoints / totalCredits;
}

void displaySubjects(const Student& student) {
    if (student.subjects.empty()) {
        cout << "\nNo subjects have been added yet.\n";
        return;
    }

    cout << "\n";
    cout << left << setw(5) << "No."
         << setw(30) << "Subject"
         << right << setw(12) << "Marks"
         << setw(12) << "Credits"
         << setw(14) << "Grade Point" << '\n';
    cout << string(73, '-') << '\n';

    for (size_t i = 0; i < student.subjects.size(); ++i) {
        cout << left << setw(5) << (i + 1)
             << setw(30) << student.subjects[i].name.substr(0, 28)
             << right << setw(12) << fixed << setprecision(2) << student.subjects[i].marks
             << setw(12) << student.subjects[i].credits
             << setw(14) << gradePointFromMarks(student.subjects[i].marks) << '\n';
    }

    cout << "\nCurrent CGPA: " << fixed << setprecision(2) << calculateCGPA(student) << '\n';
}

void addSubject(Student& student, const string& dataFileName) {
    cout << "\n========== Add Subject ==========\n";

    if (student.subjects.size() >= 200) {
        cout << "Subject limit reached.\n";
        return;
    }

    Subject subject;
    subject.name = readNonEmptyLine("Enter subject name: ");

    for (size_t i = 0; i < student.subjects.size(); ++i) {
        if (toUpperCase(student.subjects[i].name) == toUpperCase(subject.name)) {
            cout << "This subject already exists in your record.\n";
            return;
        }
    }

    subject.marks = readDouble("Enter marks (0-100): ", 0.0, 100.0);
    subject.credits = readInt("Enter credits (1-30): ", 1, 30);

    student.subjects.push_back(subject);

    if (!saveStudentData(student, dataFileName)) {
        student.subjects.pop_back();
        cout << "Subject was not added because saving failed.\n";
        return;
    }

    cout << "Subject added successfully. Updated CGPA: "
         << fixed << setprecision(2) << calculateCGPA(student) << '\n';
}

void updateSubject(Student& student, const string& dataFileName) {
    if (student.subjects.empty()) {
        cout << "\nNo subjects are available to update.\n";
        return;
    }

    displaySubjects(student);
    int index = readInt("Enter subject number to update: ", 1,
                        static_cast<int>(student.subjects.size())) - 1;

    Subject oldSubject = student.subjects[index];

    cout << "Selected subject: " << oldSubject.name << '\n';
    cout << "1. Update subject name\n";
    cout << "2. Update marks\n";
    cout << "3. Update credits\n";
    cout << "4. Update name, marks and credits\n";

    int choice = readInt("Choose update option: ", 1, 4);

    if (choice == 1 || choice == 4) {
        string newName = readNonEmptyLine("Enter new subject name: ");

        for (size_t i = 0; i < student.subjects.size(); ++i) {
            if (static_cast<int>(i) != index &&
                toUpperCase(student.subjects[i].name) == toUpperCase(newName)) {
                cout << "Another subject already uses that name.\n";
                return;
            }
        }

        student.subjects[index].name = newName;
    }

    if (choice == 2 || choice == 4) {
        student.subjects[index].marks = readDouble("Enter new marks (0-100): ", 0.0, 100.0);
    }

    if (choice == 3 || choice == 4) {
        student.subjects[index].credits = readInt("Enter new credits (1-30): ", 1, 30);
    }

    if (!saveStudentData(student, dataFileName)) {
        student.subjects[index] = oldSubject;
        cout << "Update failed. The previous subject record was restored in memory.\n";
        return;
    }

    cout << "Subject updated successfully. Updated CGPA: "
         << fixed << setprecision(2) << calculateCGPA(student) << '\n';
}

void removeSubject(Student& student, const string& dataFileName) {
    if (student.subjects.empty()) {
        cout << "\nNo subjects are available to remove.\n";
        return;
    }

    displaySubjects(student);
    int index = readInt("Enter subject number to remove: ", 1,
                        static_cast<int>(student.subjects.size())) - 1;

    Subject removedSubject = student.subjects[index];
    student.subjects.erase(student.subjects.begin() + index);

    if (!saveStudentData(student, dataFileName)) {
        student.subjects.insert(student.subjects.begin() + index, removedSubject);
        cout << "Removal failed. The previous record was restored in memory.\n";
        return;
    }

    cout << "Subject removed successfully. Updated CGPA: "
         << fixed << setprecision(2) << calculateCGPA(student) << '\n';
}

void studentDashboard(Student& student, const string& dataFileName) {
    while (true) {
        cout << "\n============================================\n";
        cout << "             STUDENT DASHBOARD\n";
        cout << "============================================\n";
        cout << "Student Name: " << student.name << '\n';
        cout << "Student ID  : " << student.id << '\n';
        cout << "1. View all subjects and CGPA\n";
        cout << "2. Add subject\n";
        cout << "3. Update subject or marks\n";
        cout << "4. Remove subject\n";
        cout << "5. View CGPA only\n";
        cout << "0. Sign out\n";

        int choice = readInt("Enter your choice: ", 0, 5);

        switch (choice) {
            case 1:
                displaySubjects(student);
                break;
            case 2:
                addSubject(student, dataFileName);
                break;
            case 3:
                updateSubject(student, dataFileName);
                break;
            case 4:
                removeSubject(student, dataFileName);
                break;
            case 5:
                cout << "Your current CGPA is "
                     << fixed << setprecision(2) << calculateCGPA(student) << '\n';
                break;
            case 0:
                cout << "Signed out successfully.\n";
                return;
        }
    }
}

int main() {
    while (true) {
        cout << "\n============================================\n";
        cout << "       STUDENT RECORD & CGPA SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Student Sign Up\n";
        cout << "2. Student Sign In\n";
        cout << "0. Exit\n";

        int choice = readInt("Enter your choice: ", 0, 2);

        if (choice == 0) {
            cout << "Thank you for using the system.\n";
            return 0;
        }

        Student student;
        string dataFileName;

        if (choice == 1) {
            signUp(student, dataFileName);
        } else if (choice == 2) {
            if (signIn(student, dataFileName)) {
                studentDashboard(student, dataFileName);
            }
        }
    }
}
