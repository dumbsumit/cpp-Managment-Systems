#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include <iomanip>
using namespace std;

class Student
{
private:
    string name;
    string rollNo;
    string className;
    vector<pair<string, int>> grades; // subject and grade
    string address;
    string parentName;

public:
    Student() : name(""), rollNo(""), className(""), address(""), parentName("") {}

    void setName(string n) { name = n; }
    void setRollNo(string r) { rollNo = r; }
    void setClass(string c) { className = c; }
    void addGrade(string subject, int grade) { grades.push_back({subject, grade}); }
    void setAddress(string a) { address = a; }
    void setParentName(string p) { parentName = p; }

    string getName() { return name; }
    string getRollNo() { return rollNo; }
    string getClass() { return className; }
    vector<pair<string, int>> &getGrades() { return grades; }
    string getAddress() { return address; }
    string getParentName() { return parentName; }
};

void addStudent(Student s)
{
    bool close = false;
    while (!close)
    {
        system("clear");
        int choice;
        cout << "\t1. Add New Student" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name, rollNo, className, address, parentName;

            cin.ignore();
            cout << "\tEnter Student Name: ";
            getline(cin, name);
            s.setName(name);

            cout << "\tEnter Roll Number: ";
            getline(cin, rollNo);
            s.setRollNo(rollNo);

            cout << "\tEnter Class: ";
            getline(cin, className);
            s.setClass(className);

            cout << "\tEnter Address: ";
            getline(cin, address);
            s.setAddress(address);

            cout << "\tEnter Parent's Name: ";
            getline(cin, parentName);
            s.setParentName(parentName);

            int numSubjects;
            cout << "\tEnter number of subjects: ";
            cin >> numSubjects;
            cin.ignore();

            for (int i = 0; i < numSubjects; i++)
            {
                string subject;
                int grade;
                cout << "\tEnter Subject " << (i + 1) << ": ";
                getline(cin, subject);
                cout << "\tEnter Grade for " << subject << ": ";
                cin >> grade;
                cin.ignore();
                s.addGrade(subject, grade);
            }

            ofstream out("School.txt", ios::app);
            if (!out)
            {
                cout << "\tError: File Can't Open!" << endl;
            }
            else
            {
                out << "\t" << s.getRollNo() << " : " << s.getName() << " : " << s.getClass()
                    << " : " << s.getParentName() << " : " << s.getAddress() << " : Grades[";
                for (const auto &grade : s.getGrades())
                {
                    out << grade.first << "=" << grade.second << ",";
                }
                out << "]" << endl;
                cout << "\tStudent Added Successfully!" << endl;
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

void updateGrades()
{
    system("clear");
    string rollNo;
    cout << "\tEnter Student Roll Number to update grades: ";
    cin >> rollNo;

    ifstream in("School.txt");
    ofstream out("Temp.txt");

    string line;
    bool found = false;

    while (getline(in, line))
    {
        if (line.find(rollNo) != string::npos)
        {
            found = true;
            stringstream ss(line);
            string roll, name, className, parentName, address;
            getline(ss, roll, ':');
            getline(ss, name, ':');
            getline(ss, className, ':');
            getline(ss, parentName, ':');
            getline(ss, address, ':');

            cout << "\tStudent: " << name << endl;
            int numSubjects;
            cout << "\tEnter number of subjects to update: ";
            cin >> numSubjects;
            cin.ignore();

            vector<pair<string, int>> newGrades;
            for (int i = 0; i < numSubjects; i++)
            {
                string subject;
                int grade;
                cout << "\tEnter Subject: ";
                getline(cin, subject);
                cout << "\tEnter New Grade: ";
                cin >> grade;
                cin.ignore();
                newGrades.push_back({subject, grade});
            }

            out << roll << ":" << name << ":" << className << ":" << parentName << ":"
                << address << ": Grades[";
            for (const auto &grade : newGrades)
            {
                out << grade.first << "=" << grade.second << ",";
            }
            out << "]" << endl;
            cout << "\tGrades Updated Successfully!" << endl;
        }
        else
        {
            out << line << endl;
        }
    }

    if (!found)
    {
        cout << "\tStudent not found!" << endl;
    }

    in.close();
    out.close();
    remove("School.txt");
    rename("Temp.txt", "School.txt");

    this_thread::sleep_for(chrono::seconds(2));
}

void generateReport()
{
    system("clear");
    string rollNo;
    cout << "\tEnter Student Roll Number to generate report: ";
    cin >> rollNo;

    ifstream in("School.txt");
    bool found = false;
    string line;

    while (getline(in, line))
    {
        if (line.find(rollNo) != string::npos)
        {
            found = true;
            stringstream ss(line);
            string roll, name, className, parentName, address, grades;
            getline(ss, roll, ':');
            getline(ss, name, ':');
            getline(ss, className, ':');
            getline(ss, parentName, ':');
            getline(ss, address, ':');
            getline(ss, grades);

            cout << "\n\t--------------------" << endl;
            cout << "\tSTUDENT REPORT CARD" << endl;
            cout << "\t--------------------" << endl;
            cout << "\tName: " << name << endl;
            cout << "\tRoll No: " << roll << endl;
            cout << "\tClass: " << className << endl;
            cout << "\tParent's Name: " << parentName << endl;
            cout << "\tAddress: " << address << endl;
            cout << "\t--------------------" << endl;
            cout << "\tGrades:" << endl;
            cout << grades << endl;
            cout << "\t--------------------" << endl;
        }
    }

    if (!found)
    {
        cout << "\tStudent not found!" << endl;
    }

    in.close();
    cout << "\n\tPress Enter to continue...";
    cin.ignore();
    getchar();
}

void viewAllStudents()
{
    system("clear");
    ifstream in("School.txt");

    if (!in)
    {
        cout << "\tNo students in the system." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    cout << "\tStudent Directory:" << endl;
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
    Student s;
    bool exit = false;

    while (!exit)
    {
        system("clear");
        int choice;

        cout << "\tSchool Management System" << endl;
        cout << "\t**********************" << endl;
        cout << "\t1. Add Student" << endl;
        cout << "\t2. Update Grades" << endl;
        cout << "\t3. Generate Report Card" << endl;
        cout << "\t4. View All Students" << endl;
        cout << "\t5. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(s);
            break;
        case 2:
            updateGrades();
            break;
        case 3:
            generateReport();
            break;
        case 4:
            viewAllStudents();
            break;
        case 5:
            exit = true;
            cout << "\tThank you for using School Management System!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        default:
            cout << "\tInvalid Choice!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
    return 0;
}