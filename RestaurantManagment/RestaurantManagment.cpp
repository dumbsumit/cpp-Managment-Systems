#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

class Order
{
private:
    int tableNo;
    vector<string> items;
    double totalBill;
    bool isComplete;

public:
    Order() : tableNo(0), totalBill(0.0), isComplete(false) {}

    void setTableNo(int t) { tableNo = t; }
    void addItem(string item) { items.push_back(item); }
    void setTotalBill(double bill) { totalBill = bill; }
    void setStatus(bool status) { isComplete = status; }

    int getTableNo() { return tableNo; }
    vector<string> getItems() { return items; }
    double getTotalBill() { return totalBill; }
    bool getStatus() { return isComplete; }
};

void takeOrder(Order o)
{
    bool close = false;
    while (!close)
    {
        system("clear");
        int choice;
        cout << "\t1. Take New Order" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int tableNo;
            double itemPrice;
            string item;
            double totalBill = 0;

            cout << "\tEnter Table Number: ";
            cin >> tableNo;
            o.setTableNo(tableNo);
            cin.ignore();

            char more = 'y';
            while (more == 'y' || more == 'Y')
            {
                cout << "\tEnter Item Name: ";
                getline(cin, item);
                o.addItem(item);

                cout << "\tEnter Item Price: $";
                cin >> itemPrice;
                totalBill += itemPrice;
                cin.ignore();

                cout << "\tAdd more items? (y/n): ";
                cin >> more;
                cin.ignore();
            }

            o.setTotalBill(totalBill);
            o.setStatus(false);

            ofstream out("Restaurant.txt", ios::app);
            if (!out)
            {
                cout << "\tError: File Can't Open!" << endl;
            }
            else
            {
                out << "\tTable-" << o.getTableNo() << " : Items-";
                for (const string &item : o.getItems())
                {
                    out << item << ",";
                }
                out << " : Total-$" << o.getTotalBill() << " : Active" << endl;
                cout << "\tOrder Placed Successfully!" << endl;
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

void completeOrder()
{
    system("clear");
    int tableNo;
    cout << "\tEnter Table Number to complete order: ";
    cin >> tableNo;

    ifstream in("Restaurant.txt");
    ofstream out("Temp.txt");

    string line;
    bool found = false;

    while (getline(in, line))
    {
        if (line.find("Table-" + to_string(tableNo)) != string::npos && line.find("Active") != string::npos)
        {
            found = true;
            string modifiedLine = line;
            modifiedLine.replace(modifiedLine.find("Active"), 6, "Completed");
            out << modifiedLine << endl;
            cout << "\tOrder completed for Table " << tableNo << endl;
        }
        else
        {
            out << line << endl;
        }
    }

    if (!found)
    {
        cout << "\tNo active order found for Table " << tableNo << "!" << endl;
    }

    in.close();
    out.close();
    remove("Restaurant.txt");
    rename("Temp.txt", "Restaurant.txt");

    this_thread::sleep_for(chrono::seconds(2));
}

void viewOrders()
{
    system("clear");
    ifstream in("Restaurant.txt");

    if (!in)
    {
        cout << "\tNo orders in the system." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    cout << "\tCurrent Orders:" << endl;
    cout << "\t--------------" << endl;
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
    Order o;
    bool exit = false;

    while (!exit)
    {
        system("clear");
        int choice;

        cout << "\tRestaurant Management System" << endl;
        cout << "\t**************************" << endl;
        cout << "\t1. Take Order" << endl;
        cout << "\t2. Complete Order" << endl;
        cout << "\t3. View Orders" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            takeOrder(o);
            break;
        case 2:
            completeOrder();
            break;
        case 3:
            viewOrders();
            break;
        case 4:
            exit = true;
            cout << "\tThank you for using Restaurant Management System!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        default:
            cout << "\tInvalid Choice!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
    return 0;
}