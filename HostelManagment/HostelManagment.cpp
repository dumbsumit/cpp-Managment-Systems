#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
using namespace std;

class Student
{
private:
    string name;
    string rollNo;
    int roomNo;
    string branch;
    bool isAllocated;

public:
    Student() : name(""), rollNo(""), roomNo(0), branch(""), isAllocated(false) {}

    void setName(string n) { name = n; }
    void setRollNo(string r) { rollNo = r; }
    void setRoomNo(int r) { roomNo = r; }
    void setBranch(string b) { branch = b; }
    void setAllocationStatus(bool status) { isAllocated = status; }

    string getName() { return name; }
    string getRollNo() { return rollNo; }
    int getRoomNo() { return roomNo; }
    string getBranch() { return branch; }
    bool getAllocationStatus() { return isAllocated; }
};

void allocateRoom(Student s)
{
    bool close = false;
    while (!close)
    {
        system("clear");
        int choice;
        cout << "\t1. Allocate New Room" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name, rollNo, branch;
            int roomNo;
            cin.ignore();

            cout << "\tEnter Student Name: ";
            getline(cin, name);
            s.setName(name);

            cout << "\tEnter Roll Number: ";
            getline(cin, rollNo);
            s.setRollNo(rollNo);

            cout << "\tEnter Room Number: ";
            cin >> roomNo;
            s.setRoomNo(roomNo);
            cin.ignore();

            cout << "\tEnter Branch: ";
            getline(cin, branch);
            s.setBranch(branch);

            s.setAllocationStatus(true);

            ofstream out("Hostel.txt", ios::app);
            if (!out)
            {
                cout << "\tError: File Can't Open!" << endl;
            }
            else
            {
                out << "\t" << s.getName() << " : " << s.getRollNo() << " : Room-" << s.getRoomNo()
                    << " : " << s.getBranch() << " : Allocated" << endl;
                cout << "\tRoom Allocated Successfully!" << endl;
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

void vacateRoom()
{
    system("clear");
    string rollNo;
    cout << "\tEnter Roll Number to vacate room: ";
    cin >> rollNo;

    ifstream in("Hostel.txt");
    ofstream out("Temp.txt");

    string line;
    bool found = false;

    while (getline(in, line))
    {
        stringstream ss(line);
        string name, roll, room, branch, status;
        char delimiter;

        getline(ss, name, ':');
        getline(ss, roll, ':');
        getline(ss, room, ':');
        getline(ss, branch, ':');
        getline(ss, status);

        if (roll.find(rollNo) != string::npos && status.find("Allocated") != string::npos)
        {
            found = true;
            cout << "\tRoom vacated for student with Roll No: " << roll << endl;
        }
        else
        {
            out << line << endl;
        }
    }

    if (!found)
    {
        cout << "\tStudent not found or room already vacated!" << endl;
    }

    in.close();
    out.close();
    remove("Hostel.txt");
    rename("Temp.txt", "Hostel.txt");

    this_thread::sleep_for(chrono::seconds(2));
}

void viewAllocations()
{
    system("clear");
    ifstream in("Hostel.txt");

    if (!in)
    {
        cout << "\tNo rooms currently allocated." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    cout << "\tCurrent Room Allocations:" << endl;
    cout << "\t-----------------------" << endl;
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

        cout << "\tHostel Management System" << endl;
        cout << "\t**********************" << endl;
        cout << "\t1. Allocate Room" << endl;
        cout << "\t2. Vacate Room" << endl;
        cout << "\t3. View Allocations" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            allocateRoom(s);
            break;
        case 2:
            vacateRoom();
            break;
        case 3:
            viewAllocations();
            break;
        case 4:
            exit = true;
            cout << "\tThank you for using Hostel Management System!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        default:
            cout << "\tInvalid Choice!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
    return 0;
}