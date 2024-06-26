#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#include "Outlet.hpp"
#include "Manager.hpp"

int main()
{
    cout << "\t\t\t\t\t\t\t*** Welcome to Foodies ***\n";
    string name, password;
    bool check;
    do
    {
        cout << "Please enter your username : ";
        getline(cin, name);
        cout << "Please enter your password : ";
        cin >> password;
        check = managerFind(name, password);
        if (!check) 
        {
            cout << "Invalid username/password.\n";
            cin.ignore();
        }
    } while (!check);
    Manager manager(name, password);
    cout << "Welcome " << name << ".\n\n";
    Outlet *outletptr = nullptr;
    chooseOutlet(outletptr);
    int managerChoice;
    do
    {
        outletptr -> displayMenu();
        cout << "\n";
        cout << "Please select one of the following options :\n";
        manager.displayOptions();
        cin >> managerChoice;
        if (managerChoice < 1 || managerChoice > 8) cout << "Please enter a valid choice (1 - 8).\n";
        else if (managerChoice == 1)
        {
            // add item to menu
            int code, currQuantity;
            double price;
            string itemName;
            cout << "Enter the code of the item : ";
            cin >> code;
            cout << "Enter the name of the item : ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter the price of the item : ";
            cin >> price;
            cout << "Enter the quantity of the item : ";
            cin >> currQuantity;
            manager.addToMenu(*outletptr, code, itemName, price, currQuantity);
            cout << '\n';
        }
        else if (managerChoice == 2)
        {
            // remove an item from menu
            int code;
            cout << "Enter the code of the item : ";
            cin >> code;
            manager.removeFromMenu(*outletptr, code);
            cout << '\n';
        }
        else if (managerChoice == 3)
        {
            // change price of item
            int code;
            double newPrice;
            cout << "Enter the code of the item : ";
            cin >> code;
            cout << "Enter the new price of the item : ";
            cin >> newPrice;
            manager.changePriceOfItem(*outletptr, code, newPrice);
            cout << '\n';
        }
        else if (managerChoice == 4)
        {
            // change quantity of item
            int code;
            int newQuantity;
            cout << "Enter the code of the item : ";
            cin >> code;
            cout << "Enter the new quantity of the item : ";
            cin >> newQuantity;
            manager.changeQuantityOfItem(*outletptr, code, newQuantity);
            cout << '\n';
        }
        else if (managerChoice == 5)
        {
            // show total sales
            cout << "The total sales for the day are : Rs. " << manager.getSales(*outletptr) << '\n';
            cout << '\n';
        }
        else if (managerChoice == 6)
        {
            // get total orders
            cout << "The total orders for the day are : " << manager.getOrders(*outletptr) << '\n';
            cout << '\n';
        }
        else if (managerChoice == 7)
        {
            // display details of sales
            manager.displaySales(*outletptr);
            cout << '\n';
        }
        else if (managerChoice == 8)
        {
            // exit from menu
            cout << "GoodBye " << name << ".\nHave a nice day ahead.\n";
            break;
        }
    } while (managerChoice != 8);
    // load the changes into the menu
    outletptr->loadToDatabase();
    // free up the space taken by outlet object 
    delete outletptr;
    outletptr = nullptr;
    return 0;
}