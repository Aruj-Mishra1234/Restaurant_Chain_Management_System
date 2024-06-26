#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#include "Outlet.hpp"
#include "Customer.hpp"


int main()
{
    cout << "\t\t\t\t\t\t\t*** Welcome to Foodies ***\n";
    int choice;
    do
    {
        cout << "Choose one of the following options to continue :\n";
        cout << "1. Login.\n2. Create account.\n";
        cin >> choice;
        if (choice < 1 || choice > 2) cout << "Please Enter a valid choice (1 - 2).\n\n";
    } while(choice < 1 || choice > 2);
    cout << '\n';
    cin.ignore();
    if (choice == 1)
    {
        string name, password;
        bool check;
        do
        {
            cout << "Enter your username : ";
            getline(cin, name);
            cout << "Enter your password : ";
            cin >> password;
            check = customerFind(name, password);
            if (!check)
            {
                cout << "Invalid username/password.\n\n";
                cin.ignore();
            }
        } while (!check);
        cout << '\n';
        Customer customer(name, password);
        cout << "Welcome " << name << ".\n\n";
        Outlet *outletptr = nullptr;
        chooseOutlet(outletptr);
        cout << '\n';
        int customerChoice;
        do
        {
            cout << "Please select one of the following options :\n";
            cout << "1. Place an Order.\n2. Exit.\n";
            cin >> customerChoice;
            if (customerChoice > 2 || customerChoice < 1) cout << "Invalid choice. Please enter a valid choice(1 - 2).\n\n";
        } while (customerChoice > 2 || customerChoice < 1);
        if (customerChoice == 1)
        {
            outletptr -> displayMenu();
            cout << '\n';
            customer.placeOrder(*outletptr);
        }
        outletptr -> loadToDatabase();
        delete outletptr;
        outletptr = nullptr;
    }
    else
    {
        string name, password;
        bool check;
        do
        {
            cout << "Enter your username : ";
            getline(cin, name);
            cout << "Enter your password : ";
            cin >> password;
            check = customerFind(name, password);
            if (check)
            {
                cout << "The given account already exists. Please choose another name or password.\n\n";
                cin.ignore();
            }
        } while (check);
        addNewCustomer(name, password);
        cout << "Your account has been created.\n";
    }
    return 0;
}