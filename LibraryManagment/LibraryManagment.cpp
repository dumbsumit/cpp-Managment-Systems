#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
using namespace std;

class Book {
private:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

public:
    Book() : title(""), author(""), ISBN(""), isAvailable(true) {}

    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setISBN(string isbn) { ISBN = isbn; }
    void setAvailability(bool avail) { isAvailable = avail; }

    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getISBN() { return ISBN; }
    bool getAvailability() { return isAvailable; }
};

void addBook(Book b) {
    bool close = false;
    while (!close) {
        system("clear");
        int choice;
        cout << "\t1. Add New Book" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string title, author, isbn;
            cin.ignore();
            
            cout << "\tEnter Book Title: ";
            getline(cin, title);
            b.setTitle(title);

            cout << "\tEnter Author Name: ";
            getline(cin, author);
            b.setAuthor(author);

            cout << "\tEnter ISBN: ";
            getline(cin, isbn);
            b.setISBN(isbn);

            b.setAvailability(true);

            ofstream out("Library.txt", ios::app);
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            }
            else {
                out << "\t" << b.getTitle() << " : " << b.getAuthor() << " : " << b.getISBN() << " : " << "Available" << endl;
                cout << "\tBook Added Successfully!" << endl;
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

void borrowBook() {
    system("clear");
    string isbn;
    cout << "\tEnter ISBN of the book to borrow: ";
    cin >> isbn;

    ifstream in("Library.txt");
    ofstream out("Temp.txt");
    
    string line;
    bool found = false;

    while (getline(in, line)) {
        stringstream ss(line);
        string title, author, bookISBN, status;
        char delimiter;
        
        getline(ss, title, ':');
        getline(ss, author, ':');
        getline(ss, bookISBN, ':');
        getline(ss, status);

        if (isbn == bookISBN && status.find("Available") != string::npos) {
            found = true;
            out << title << ":" << author << ":" << bookISBN << ": Borrowed" << endl;
            cout << "\tBook has been borrowed successfully!" << endl;
        }
        else {
            out << line << endl;
        }
    }

    if (!found) {
        cout << "\tBook not found or not available!" << endl;
    }

    in.close();
    out.close();
    remove("Library.txt");
    rename("Temp.txt", "Library.txt");
    
    this_thread::sleep_for(chrono::seconds(2));
}

void returnBook() {
    system("clear");
    string isbn;
    cout << "\tEnter ISBN of the book to return: ";
    cin >> isbn;

    ifstream in("Library.txt");
    ofstream out("Temp.txt");
    
    string line;
    bool found = false;

    while (getline(in, line)) {
        stringstream ss(line);
        string title, author, bookISBN, status;
        char delimiter;
        
        getline(ss, title, ':');
        getline(ss, author, ':');
        getline(ss, bookISBN, ':');
        getline(ss, status);

        if (isbn == bookISBN && status.find("Borrowed") != string::npos) {
            found = true;
            out << title << ":" << author << ":" << bookISBN << ": Available" << endl;
            cout << "\tBook has been returned successfully!" << endl;
        }
        else {
            out << line << endl;
        }
    }

    if (!found) {
        cout << "\tBook not found or already returned!" << endl;
    }

    in.close();
    out.close();
    remove("Library.txt");
    rename("Temp.txt", "Library.txt");
    
    this_thread::sleep_for(chrono::seconds(2));
}

int main() {
    Book b;
    bool exit = false;

    while (!exit) {
        system("clear");
        int choice;
        
        cout << "\tLibrary Management System" << endl;
        cout << "\t***********************" << endl;
        cout << "\t1. Add New Book" << endl;
        cout << "\t2. Borrow Book" << endl;
        cout << "\t3. Return Book" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addBook(b);
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                exit = true;
                cout << "\tThank you for using Library Management System!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                break;
            default:
                cout << "\tInvalid Choice!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
        }
    }
    return 0;
}