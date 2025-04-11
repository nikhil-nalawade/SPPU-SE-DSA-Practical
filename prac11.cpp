// Company  maintains  employee  information  as  employee  ID,  name,  designation  and 
// salary.  Allow  user  to  add,  delete  information  of  employee.  Display  information  of 
// particular employee. If employee does not exist an appropriate message is displayed. If 
// it is, then the system displays the employee details. Use index sequential file to maintain 
// the data.  
#include <iostream>
#include <fstream>
#include <map>
#include <cstring>

using namespace std;

struct Employee {
    int id;
    char name[50];
    char designation[50];
    int salary;
};

class EmployeeDatabase {
    string dataFile = "employees.dat";
    map<int, streampos> index;

public:
    EmployeeDatabase();
    void loadIndex();
    void addEmployee(int id, string name, string designation, int salary);
    void searchEmployee(int id);
    void deleteEmployee(int id);
    void displayAll();
};

// Constructor - Load index from file
EmployeeDatabase::EmployeeDatabase() {
    ifstream file(dataFile, ios::binary);
    if (!file) {
        cout << "Creating new database file.\n";
        ofstream newFile(dataFile, ios::binary);
        newFile.close();
    } else {
        file.close();
        loadIndex();
    }
}

// Load index from the file to enable search and deletion
void EmployeeDatabase::loadIndex() {
    ifstream file(dataFile, ios::binary);
    Employee emp;
    streampos pos;

    while (file.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        pos = file.tellg();
        index[emp.id] = static_cast<streampos>(pos - static_cast<streamoff>(sizeof(emp)));
    }

    file.close();
}

// Add an employee record
void EmployeeDatabase::addEmployee(int id, string name, string designation, int salary) {
    if (index.find(id) != index.end()) {
        cout << "Employee already exists.\n";
        return;
    }

    Employee emp = {id, "", "", salary};
    strncpy(emp.name, name.c_str(), sizeof(emp.name) - 1);
    strncpy(emp.designation, designation.c_str(), sizeof(emp.designation) - 1);

    ofstream file(dataFile, ios::binary | ios::app);
    streampos pos = file.tellp();
    file.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    file.close();

    index[id] = pos;
    cout << "Employee added successfully.\n";
}

// Search for an employee
void EmployeeDatabase::searchEmployee(int id) {
    if (index.find(id) == index.end()) {
        cout << "Employee not found.\n";
        return;
    }

    ifstream file(dataFile, ios::binary);
    file.seekg(index[id]);
    Employee emp;
    file.read(reinterpret_cast<char*>(&emp), sizeof(emp));
    file.close();

    cout << "ID: " << emp.id << "\nName: " << emp.name << "\nDesignation: "
         << emp.designation << "\nSalary: Rs. " << emp.salary << endl;
}

// Delete an employee
void EmployeeDatabase::deleteEmployee(int id) {
    if (index.find(id) == index.end()) {
        cout << "Employee not found.\n";
        return;
    }

    ifstream file(dataFile, ios::binary);
    ofstream tempFile("temp.dat", ios::binary);
    Employee emp;

    while (file.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        if (emp.id != id) {
            tempFile.write(reinterpret_cast<char*>(&emp), sizeof(emp));
        }
    }

    file.close();
    tempFile.close();

    // Replace old file with new one
    remove(dataFile.c_str());
    rename("temp.dat", dataFile.c_str());

    index.erase(id);
    cout << "Employee deleted successfully.\n";
}

// Display all employees
void EmployeeDatabase::displayAll() {
    ifstream file(dataFile, ios::binary);
    Employee emp;

    if (!file) {
        cout << "No records found.\n";
        return;
    }

    while (file.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        cout << emp.id << " | " << emp.name << " | " << emp.designation
             << " | Rs. " << emp.salary << endl;
    }

    file.close();
}

// Main function
int main() {
    EmployeeDatabase db;
    int choice, id, salary;
    string name, designation;

    do {
        cout << "\n1 -> Add Employee\n2 -> Search Employee\n3 -> Delete Employee\n4 -> Display All\n5 -> Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "ID: "; cin >> id; cin.ignore();
                cout << "Name: "; getline(cin, name);
                cout << "Designation: "; getline(cin, designation);
                cout << "Salary: "; cin >> salary;
                db.addEmployee(id, name, designation, salary);
                break;
            case 2:
                cout << "ID: "; cin >> id;
                db.searchEmployee(id);
                break;
            case 3:
                cout << "ID: "; cin >> id;
                db.deleteEmployee(id);
                break;
            case 4:
                db.displayAll();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}