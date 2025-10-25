#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;

class Employee
{
private:
    string name;
    string id;
    string department;
    string position;
    double salary;
    string joinDate;

public:
    Employee() : name(""), id(""), department(""), position(""), salary(0.0), joinDate("") {}

    void setName(string n) { name = n; }
    void setID(string i) { id = i; }
    void setDepartment(string d) { department = d; }
    void setPosition(string p) { position = p; }
    void setSalary(double s) { salary = s; }
    void setJoinDate(string d) { joinDate = d; }

    string getName() { return name; }
    string getID() { return id; }
    string getDepartment() { return department; }
    string getPosition() { return position; }
    double getSalary() { return salary; }
    string getJoinDate() { return joinDate; }
};

void addEmployee(Employee e)
{
    bool close = false;
    while (!close)
    {
        system("clear");
        int choice;
        cout << "\t1. Add New Employee" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name, id, department, position, joinDate;
            double salary;

            cin.ignore();
            cout << "\tEnter Employee Name: ";
            getline(cin, name);
            e.setName(name);

            cout << "\tEnter Employee ID: ";
            getline(cin, id);
            e.setID(id);

            cout << "\tEnter Department: ";
            getline(cin, department);
            e.setDepartment(department);

            cout << "\tEnter Position: ";
            getline(cin, position);
            e.setPosition(position);

            cout << "\tEnter Salary: $";
            cin >> salary;
            e.setSalary(salary);
            cin.ignore();

            cout << "\tEnter Join Date (DD/MM/YYYY): ";
            getline(cin, joinDate);
            e.setJoinDate(joinDate);

            ofstream out("Employees.txt", ios::app);
            if (!out)
            {
                cout << "\tError: File Can't Open!" << endl;
            }
            else
            {
                out << "\t" << e.getID() << " : " << e.getName() << " : " << e.getDepartment()
                    << " : " << e.getPosition() << " : $" << fixed << setprecision(2)
                    << e.getSalary() << " : " << e.getJoinDate() << endl;
                cout << "\tEmployee Added Successfully!" << endl;
            }
            out.close();
            this_thread::sleep_for(chrono::seconds(2));
        }
        else if (choice == 2)
        {
            close = true;
            cout << "\tReturning to Main Menu!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}

void updateEmployee()
{
    system("clear");
    string empID;
    cout << "\tEnter Employee ID to update details: ";
    cin >> empID;

    ifstream in("Employees.txt");
    ofstream out("Temp.txt");

    string line;
    bool found = false;

    while (getline(in, line))
    {
        if (line.find(empID) != string::npos)
        {
            found = true;
            string name, id, department, position, joinDate;
            double salary;

            cin.ignore();
            cout << "\tEnter New Department: ";
            getline(cin, department);

            cout << "\tEnter New Position: ";
            getline(cin, position);

            cout << "\tEnter New Salary: $";
            cin >> salary;

            stringstream ss(line);
            string oldId, oldName;
            getline(ss, oldId, ':');
            getline(ss, oldName, ':');

            out << oldId << ":" << oldName << ":" << " " << department << " : "
                << position << " : $" << fixed << setprecision(2) << salary << " : "
                << joinDate << endl;
            cout << "\tEmployee Details Updated Successfully!" << endl;
        }
        else
        {
            out << line << endl;
        }
    }

    if (!found)
    {
        cout << "\tEmployee not found!" << endl;
    }

    in.close();
    out.close();
    remove("Employees.txt");
    rename("Temp.txt", "Employees.txt");

    this_thread::sleep_for(chrono::seconds(2));
}

void removeEmployee()
{
    system("clear");
    string empID;
    cout << "\tEnter Employee ID to remove: ";
    cin >> empID;

    ifstream in("Employees.txt");
    ofstream out("Temp.txt");

    string line;
    bool found = false;

    while (getline(in, line))
    {
        if (line.find(empID) == string::npos)
        {
            out << line << endl;
        }
        else
        {
            found = true;
            cout << "\tEmployee Removed Successfully!" << endl;
        }
    }

    if (!found)
    {
        cout << "\tEmployee not found!" << endl;
    }

    in.close();
    out.close();
    remove("Employees.txt");
    rename("Temp.txt", "Employees.txt");

    this_thread::sleep_for(chrono::seconds(2));
}

void viewEmployees()
{
    system("clear");
    ifstream in("Employees.txt");

    if (!in)
    {
        cout << "\tNo employees in the system." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    cout << "\tEmployee Directory:" << endl;
    cout << "\t-----------------" << endl;
    string line;
    while (getline(in, line))
    {
        cout << line << endl;
    }

    in.close();
    cout << "\n\tPress Enter to continue...";
    cin.ignore();
    getchar();
}

int main()
{
    Employee e;
    bool exit = false;

    while (!exit)
    {
        system("clear");
        int choice;

        cout << "\tEmployee Management System" << endl;
        cout << "\t************************" << endl;
        cout << "\t1. Add Employee" << endl;
        cout << "\t2. Update Employee Details" << endl;
        cout << "\t3. Remove Employee" << endl;
        cout << "\t4. View All Employees" << endl;
        cout << "\t5. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addEmployee(e);
            break;
        case 2:
            updateEmployee();
            break;
        case 3:
            removeEmployee();
            break;
        case 4:
            viewEmployees();
            break;
        case 5:
            exit = true;
            cout << "\tThank you for using Employee Management System!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        default:
            cout << "\tInvalid Choice!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
    return 0;
}