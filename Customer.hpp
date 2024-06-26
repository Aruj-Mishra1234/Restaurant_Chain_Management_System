class Customer
{
    string name;
    string password;
    public:
    Customer(string _name, string _pass) : name(_name), password(_pass) {}
    void placeOrder(Outlet &outlet)
    {
        int itemCode, itemQuantity, countItems;
        cout << "Enter number of items to be ordered : ";
        cin >> countItems;
        map<int, int> order;
        for (int i = 0; i < countItems; i++)
        {
            cout << "Enter the item code and item quantity of item - " << i + 1 << " : ";
            cin >> itemCode >> itemQuantity;
            order[itemCode] = itemQuantity;
        }
        cout << '\n';
        if (outlet.canAcceptOrder(order))
        {
            outlet.generateInvoice(order);
            cout << "\nThanks for ordering from us.\nHope to see you again.\n";
        }
        else
        {
            cout << "\nUnfortunately, we don't have enough items for carrying out your order.\nSorry for the Inconvenience caused.\n";
        }
        return;
    }
    ~Customer() {}
};

bool customerFind(string _name, string _pass)
{
    ifstream fin("Customer_Database.txt");
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

void addNewCustomer(string _name, string _pass)
{
    ofstream fout("Customer_Database.txt", ios_base :: app);
    fout << _name << ", " << _pass << ",\n";
    fout.close();
    return;
}