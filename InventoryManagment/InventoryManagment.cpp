#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;

class Product
{
private:
    string name;
    string category;
    int quantity;
    double price;
    string sku;

public:
    Product() : name(""), category(""), quantity(0), price(0.0), sku("") {}

    void setName(string n) { name = n; }
    void setCategory(string c) { category = c; }
    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }
    void setSKU(string s) { sku = s; }

    string getName() { return name; }
    string getCategory() { return category; }
    int getQuantity() { return quantity; }
    double getPrice() { return price; }
    string getSKU() { return sku; }
};

void addProduct(Product p)
{
    bool close = false;
    while (!close)
    {
        system("clear");
        int choice;
        cout << "\t1. Add New Product" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name, category, sku;
            int quantity;
            double price;

            cin.ignore();
            cout << "\tEnter Product Name: ";
            getline(cin, name);
            p.setName(name);

            cout << "\tEnter Category: ";
            getline(cin, category);
            p.setCategory(category);

            cout << "\tEnter SKU: ";
            getline(cin, sku);
            p.setSKU(sku);

            cout << "\tEnter Quantity: ";
            cin >> quantity;
            p.setQuantity(quantity);

            cout << "\tEnter Price: $";
            cin >> price;
            p.setPrice(price);

            ofstream out("Inventory.txt", ios::app);
            if (!out)
            {
                cout << "\tError: File Can't Open!" << endl;
            }
            else
            {
                out << "\t" << p.getSKU() << " : " << p.getName() << " : " << p.getCategory()
                    << " : " << p.getQuantity() << " : $" << fixed << setprecision(2) << p.getPrice() << endl;
                cout << "\tProduct Added Successfully!" << endl;
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

void updateStock()
{
    system("clear");
    string sku;
    cout << "\tEnter Product SKU to update stock: ";
    cin >> sku;

    ifstream in("Inventory.txt");
    ofstream out("Temp.txt");

    string line;
    bool found = false;

    while (getline(in, line))
    {
        stringstream ss(line);
        string currSku, name, category, quantity, price;
        getline(ss, currSku, ':');
        getline(ss, name, ':');
        getline(ss, category, ':');
        getline(ss, quantity, ':');
        getline(ss, price);

        if (currSku.find(sku) != string::npos)
        {
            found = true;
            int newQuantity;
            cout << "\tCurrent Quantity: " << quantity << endl;
            cout << "\tEnter New Quantity: ";
            cin >> newQuantity;
            out << currSku << ":" << name << ":" << category << ":" << " " << newQuantity << ":" << price << endl;
            cout << "\tStock Updated Successfully!" << endl;
        }
        else
        {
            out << line << endl;
        }
    }

    if (!found)
    {
        cout << "\tProduct not found!" << endl;
    }

    in.close();
    out.close();
    remove("Inventory.txt");
    rename("Temp.txt", "Inventory.txt");

    this_thread::sleep_for(chrono::seconds(2));
}

void viewInventory()
{
    system("clear");
    ifstream in("Inventory.txt");

    if (!in)
    {
        cout << "\tNo products in inventory." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    cout << "\tCurrent Inventory:" << endl;
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
    Product p;
    bool exit = false;

    while (!exit)
    {
        system("clear");
        int choice;

        cout << "\tInventory Management System" << endl;
        cout << "\t*************************" << endl;
        cout << "\t1. Add Product" << endl;
        cout << "\t2. Update Stock" << endl;
        cout << "\t3. View Inventory" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addProduct(p);
            break;
        case 2:
            updateStock();
            break;
        case 3:
            viewInventory();
            break;
        case 4:
            exit = true;
            cout << "\tThank you for using Inventory Management System!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        default:
            cout << "\tInvalid Choice!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
    return 0;
}