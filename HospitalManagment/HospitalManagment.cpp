#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
using namespace std;

class Patient {
private:
    string name;
    int age;
    string disease;
    string bloodGroup;
    bool isAdmitted;

public:
    Patient() : name(""), age(0), disease(""), bloodGroup(""), isAdmitted(false) {}

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setDisease(string d) { disease = d; }
    void setBloodGroup(string bg) { bloodGroup = bg; }
    void setAdmissionStatus(bool status) { isAdmitted = status; }

    string getName() { return name; }
    int getAge() { return age; }
    string getDisease() { return disease; }
    string getBloodGroup() { return bloodGroup; }
    bool getAdmissionStatus() { return isAdmitted; }
};

void admitPatient(Patient p) {
    bool close = false;
    while (!close) {
        system("clear");
        int choice;
        cout << "\t1. Admit New Patient" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, disease, bloodGroup;
            int age;
            cin.ignore();
            
            cout << "\tEnter Patient Name: ";
            getline(cin, name);
            p.setName(name);

            cout << "\tEnter Age: ";
            cin >> age;
            p.setAge(age);
            cin.ignore();

            cout << "\tEnter Disease/Condition: ";
            getline(cin, disease);
            p.setDisease(disease);

            cout << "\tEnter Blood Group: ";
            getline(cin, bloodGroup);
            p.setBloodGroup(bloodGroup);

            p.setAdmissionStatus(true);

            ofstream out("Hospital.txt", ios::app);
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            }
            else {
                out << "\t" << p.getName() << " : " << p.getAge() << " : " << p.getDisease() 
                    << " : " << p.getBloodGroup() << " : Admitted" << endl;
                cout << "\tPatient Admitted Successfully!" << endl;
            }
            out.close();
            this_thread::sleep_for(chrono::seconds(2));
        }
        else if (choice == 2) {
            close = true;
            cout << "\tReturning to Main Menu!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}

void dischargePatient() {
    system("clear");
    string patientName;
    cout << "\tEnter Patient Name to discharge: ";
    cin.ignore();
    getline(cin, patientName);

    ifstream in("Hospital.txt");
    ofstream out("Temp.txt");
    
    string line;
    bool found = false;

    while (getline(in, line)) {
        stringstream ss(line);
        string name, age, disease, bloodGroup, status;
        char delimiter;
        
        getline(ss, name, ':');
        getline(ss, age, ':');
        getline(ss, disease, ':');
        getline(ss, bloodGroup, ':');
        getline(ss, status);

        if (name.find(patientName) != string::npos && status.find("Admitted") != string::npos) {
            found = true;
            cout << "\tPatient " << name << " has been discharged!" << endl;
        }
        else {
            out << line << endl;
        }
    }

    if (!found) {
        cout << "\tPatient not found or already discharged!" << endl;
    }

    in.close();
    out.close();
    remove("Hospital.txt");
    rename("Temp.txt", "Hospital.txt");
    
    this_thread::sleep_for(chrono::seconds(2));
}

void viewPatients() {
    system("clear");
    ifstream in("Hospital.txt");
    
    if (!in) {
        cout << "\tNo patients currently admitted." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    cout << "\tCurrent Admitted Patients:" << endl;
    cout << "\t------------------------" << endl;
    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
    
    in.close();
    cout << "\n\tPress Enter to continue...";
    cin.ignore();
    getchar();
}

int main() {
    Patient p;
    bool exit = false;

    while (!exit) {
        system("clear");
        int choice;
        
        cout << "\tHospital Management System" << endl;
        cout << "\t************************" << endl;
        cout << "\t1. Admit Patient" << endl;
        cout << "\t2. Discharge Patient" << endl;
        cout << "\t3. View Admitted Patients" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                admitPatient(p);
                break;
            case 2:
                dischargePatient();
                break;
            case 3:
                viewPatients();
                break;
            case 4:
                exit = true;
                cout << "\tThank you for using Hospital Management System!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                break;
            default:
                cout << "\tInvalid Choice!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
        }
    }
    return 0;
}