class Manager
{
    string name;
    string password;
    public:
    Manager(string &_name, string &_pass) : name(_name), password(_pass) {}
    void addToMenu(Outlet &outlet, int code, string &name, double price, int currQuantity)
    {
        outlet.addItem(code, name, price, currQuantity);
        cout << name << " has been added to the menu of outlet.\n";
        return;
    }
    void removeFromMenu(Outlet &outlet, int code)
    {
        outlet.removeItem(code);
        cout << "The item " << code << " has been removed from the outlet's menu.\n";
        return;
    }
    void changePriceOfItem(Outlet &outlet, int code, double newPrice)
    {
        outlet.changePrice(code, newPrice);
        cout << "The price of item " << code << " has been changed.\n";
        return;
    }
    void changeQuantityOfItem(Outlet &outlet, int code, int newQuantity)
    {
        outlet.changeQuantity(code, newQuantity);
        cout << "The quantity of item " << code << " has been changed.\n";
        return;
    }
    double getSales(Outlet &outlet)
    {
        return outlet.getSales();
    }
    int getOrders(Outlet &outlet)
    {
        return outlet.getOrders();
    }
    void displaySales(Outlet &outlet)
    {
        outlet.displaySales();
        return;
    }
    void displayOptions(void)
    {
        cout << "1. Add an item to selected outlet's menu.\n";
        cout << "2. Remove an item from selected outlet's menu.\n";
        cout << "3. Change price of an item from selected outlet's menu.\n";
        cout << "4. Change Quantity of an item from selected outlet's menu.\n";
        cout << "5. Get the total sales of the day from the selected outlet.\n";
        cout << "6. Get the total orders of the day to the selected outlet.\n";
        cout << "7. Display the details of all the sales from the selected outlet.\n";
        cout << "8. Exit from Menu.\n";
        return;
    }
    ~Manager() {}
};

bool managerFind(string _name, string _pass)
{
    ifstream fin("Manager_Database.txt");
    string str;
    int i, j;
    bool exists = false;
    while(getline(fin, str))
    {
        i = 0, j = 0;
        for (; str[i] != ',' && j < _name.length(); i++, j++) if (str[i] != _name[j]) break;
        if (str[i] != ',' || j != _name.length()) continue;
        i += 2;
        j = 0;
        for (; str[i] != ',' && j < _pass.length(); i++, j++) if (str[i] != _pass[j]) break;
        if (str[i] != ',' || j != _pass.length()) continue;
        exists = true;
        break;
    }
    fin.close();
    return exists;
}