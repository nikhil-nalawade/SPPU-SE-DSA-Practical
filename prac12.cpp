// Department  maintains  a  student  information.  The  file  contains  roll  number,  name, 
// division and address. Allow user to add, delete information of student. Display 
// information  of  particular  employee.  If  record  of  student  does  not  exist  an  appropriate 
// message is displayed. If it is, then the system displays the student details. Use sequential 
// file to main the data.

#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

// Student structure
typedef struct student {
    int rollNo;
    char name[50];
    char div;
    char address[100];
} student;

// Class to handle Student Database
class studentDatabase {
    string fileName = "student_data.dat";

public:
    studentDatabase() {
        fstream fileObj(fileName, ios::in | ios::binary);
        if (!fileObj) {
            cout << "Creating new file: " << fileName << endl;
            ofstream newFile(fileName, ios::out | ios::binary);
            newFile.close();
        } else {
            cout << "File loaded successfully.\n";
        }
        fileObj.close();
    }

    void addStudent();
    void searchStudent();
    void deleteStudent();
    void displayAll();
};

// Add a new student record
void studentDatabase::addStudent() {
    student s;
    cout << "Enter Roll Number: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(s.name, 50);
    cout << "Enter Division: ";
    cin >> s.div;
    cout << "Enter Address: ";
    cin.ignore();
    cin.getline(s.address, 100);

    ofstream file(fileName, ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&s), sizeof(student));
    file.close();

    cout << "Student added successfully.\n";
}

// Search for a student record
void studentDatabase::searchStudent() {
    int roll;
    student s;
    bool found = false;

    cout << "Enter Roll Number to search: ";
    cin >> roll;

    ifstream file(fileName, ios::binary);
    while (file.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        if (s.rollNo == roll) {
            found = true;
            cout << "\n--- Student Record Found ---\n";
            cout << "Roll Number: " << s.rollNo << "\nName: " << s.name
                 << "\nDivision: " << s.div << "\nAddress: " << s.address << endl;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Student with Roll Number " << roll << " not found.\n";
    }
}

// Delete a student record
void studentDatabase::deleteStudent() {
    int roll;
    student s;
    bool found = false;

    cout << "Enter Roll Number to delete: ";
    cin >> roll;

    ifstream file(fileName, ios::binary);
    ofstream tempFile("temp.dat", ios::binary);

    while (file.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        if (s.rollNo == roll) {
            found = true;
            cout << "Student with Roll Number " << roll << " deleted.\n";
        } else {
            tempFile.write(reinterpret_cast<char*>(&s), sizeof(student));
        }
    }

    file.close();
    tempFile.close();

    // Replace original file with updated file
    remove(fileName.c_str());
    rename("temp.dat", fileName.c_str());

    if (!found) {
        cout << "Student with Roll Number " << roll << " not found.\n";
    }
}

// Display all student records
void studentDatabase::displayAll() {
    ifstream file(fileName, ios::binary);
    student s;
    int count = 0;

    cout << "\n--- All Student Records ---\n";
    while (file.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        count++;
        cout << count << ") Roll Number: " << s.rollNo << "\n   Name: " << s.name
             << "\n   Division: " << s.div << "\n   Address: " << s.address << endl;
    }
    file.close();

    if (count == 0) {
        cout << "No records found.\n";
    }
}

// Main Function
int main() {
    studentDatabase db;
    int choice;

    do {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1 -> Add Student Record\n";
        cout << "2 -> Search Student Record\n";
        cout << "3 -> Delete Student Record\n";
        cout << "4 -> Display All Student Records\n";
        cout << "0 -> Exit\n";
        cout << "Choose an option (0-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                db.addStudent();
                break;
            case 2:
                db.searchStudent();
                break;
            case 3:
                db.deleteStudent();
                break;
            case 4:
                db.displayAll();
                break;
            case 0:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}