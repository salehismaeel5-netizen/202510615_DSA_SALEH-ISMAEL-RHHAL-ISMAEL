#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// 1. Requirement: Create a Student Object to store student information.
class Student {
public:
    string rollNumber;
    string name;
    string age;

    // Helper function to convert student data to CSV format for writing to file
    string toCSV() const {
        return rollNumber + "," + name + "," + age;
    }
};

// Helper function to parse a CSV line from the file into a Student object
Student parseCSV(const string& line) {
    Student s;
    stringstream ss(line);
    getline(ss, s.rollNumber, ',');
    getline(ss, s.name, ',');
    getline(ss, s.age, ',');
    return s;
}

// 2. Requirement: Implement a function to display all students stored in the file.
void displayAllStudents() {
    ifstream file("student.txt");
    if (!file) {
        cout << "\n[!] Error: Could not open file or file does not exist yet.\n";
        return;
    }

    string line;
    cout << "\n--- Displaying All Students ---\n";
    cout << "Roll No.\tName\t\tAge\n";
    cout << "--------------------------------------------\n";
    
    bool hasData = false;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Student s = parseCSV(line);
        cout << s.rollNumber << "\t\t" << s.name << "\t\t" << s.age << "\n";
        hasData = true;
    }
    
    if (!hasData) {
        cout << "The file is empty. No student records found.\n";
    }
    file.close();
}

// 3. Requirement: Ask user for Roll Number, search for it, and display details or "Student not found".
void searchStudent() {
    ifstream file("student.txt");
    if (!file) {
        cout << "\n[!] Error: File not found.\n";
        return;
    }

    string searchRoll;
    cout << "\nEnter Roll Number to search: ";
    cin >> searchRoll;

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Student s = parseCSV(line);
        if (s.rollNumber == searchRoll) {
            cout << "\n[+] Student Found:\n";
            cout << "Roll Number: " << s.rollNumber << "\n";
            cout << "Name:        " << s.name << "\n";
            cout << "Age:         " << s.age << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n[-] Student not found\n";
    }
    file.close();
}

// 4. Requirement: Ask user for Roll Number and update the student's information permanently.
void updateStudent() {
    ifstream file("student.txt");
    if (!file) {
        cout << "\n[!] Error: File not found.\n";
        return;
    }

    string targetRoll;
    cout << "\nEnter Roll Number to update: ";
    cin >> targetRoll;

    vector<Student> students;
    string line;
    bool found = false;

    // Read all records and modify the targeted one in memory
    while (getline(file, line)) {
        if (line.empty()) continue;
        Student s = parseCSV(line);
        if (s.rollNumber == targetRoll) {
            found = true;
            cout << "[+] Record found for: " << s.name << "\n";
            cout << "Enter New Name: ";
            cin >> s.name;
            cout << "Enter New Age: ";
            cin >> s.age;
        }
        students.push_back(s);
    }
    file.close();

    if (!found) {
        cout << "\n[-] Student not found\n";
        return;
    }

    // Write back all records to the file permanently (overwriting old data)
    ofstream outFile("student.txt", ios::trunc);
    for (const auto& s : students) {
        outFile << s.toCSV() << "\n";
    }
    outFile.close();
    cout << "\n[+] Student record updated successfully.\n";
}

// 5. Requirement: Ask user for Roll Number and delete the student's record permanently.
void deleteStudent() {
    ifstream file("student.txt");
    if (!file) {
        cout << "\n[!] Error: File not found.\n";
        return;
    }

    string targetRoll;
    cout << "\nEnter Roll Number to delete: ";
    cin >> targetRoll;

    vector<Student> students;
    string line;
    bool found = false;

    // Read all records and skip (delete) the targeted one
    while (getline(file, line)) {
        if (line.empty()) continue;
        Student s = parseCSV(line);
        if (s.rollNumber == targetRoll) {
            found = true;
            continue; // Skip appending this student to delete it
        }
        students.push_back(s);
    }
    file.close();

    if (!found) {
        cout << "\n[-] Student not found\n";
        return;
    }

    // Rewrite the file without the deleted record
    ofstream outFile("student.txt", ios::trunc);
    for (const auto& s : students) {
        outFile << s.toCSV() << "\n";
    }
    outFile.close();
    cout << "\n[+] Student record deleted successfully.\n";
}

// Helper function to auto-initialize file with the default assignment data if it's empty
void initializeFileIfEmpty() {
    ifstream checkFile("student.txt");
    if (!checkFile || checkFile.peek() == ifstream::traits_type::eof()) {
        ofstream outFile("student.txt");
        outFile << "202312051,lithacynthia,18\n";
        outFile << "202312052,dessama,18\n";
        outFile << "202312053,david,20\n";
        outFile.close();
    }
    if (checkFile) checkFile.close();
}

// 7. Requirement: Create a menu-driven system using a loop and switch statement.
int main() {
    // Populate the file with default sample data from the assignment instruction sheet
    initializeFileIfEmpty();

    int choice;
    do {
        cout << "\n====================================\n";
        cout << "1. Display All Students\n";
        cout << "2. Search Student\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllStudents();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                cout << "\n[+] Exiting program... Goodbye!\n";
                break;
            default:
                cout << "\n[!] Invalid choice! Please select between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}