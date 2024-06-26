void menuParser(string &str, pair<int, pair<string, pair<double, int>>> &info)
{
    int i = 0;
    string tmp = "";
    while(str[i] != ',')
    {
        tmp.push_back(str[i]);
        ++i;
    }
    info.first = stoi(tmp);
    tmp = "";
    i += 2;
    while(str[i] != ',')
    {
        tmp.push_back(str[i]);
        ++i;
    }
    info.second.first = tmp;
    tmp = "";
    i += 2;
    while(str[i] != ',')
    {
        tmp.push_back(str[i]);
        ++i;
    }
    info.second.second.first = stold(tmp);
    tmp = "";
    i += 2;
    while(str[i] != ',')
    {
        tmp.push_back(str[i]);
        ++i;
    }
    info.second.second.second = stoi(tmp);
}
void salesParser(string &str, int &totalOrders, double &totalSales)
{
    int i = 0;
    string tmp = "";
    while(str[i] != ',')
    {
        tmp.push_back(str[i]);
        i++;
    }
    totalOrders = stoi(tmp);
    i += 2;
    tmp = "";
    while(str[i] != ',')
    {
        tmp.push_back(str[i]);
        i++;
    }
    totalSales = stold(tmp);
    return;
}

class Outlet
{
    string menuDatabase;
    map<int, pair<string, pair<double, int>>> menu;
    string salesDatabase;
    string cntSalesDatabase;
    static double totalSales;
    static int totalOrders;
    public:
    Outlet(string _menuDatabase, string _salesDatabase, string _cntSalesDatabase) : menuDatabase(_menuDatabase), salesDatabase(_salesDatabase), cntSalesDatabase(_cntSalesDatabase)
    {
        string currLine;
        ifstream fin(_menuDatabase);
        pair<int, pair<string, pair<double, int>>> info;
        while(getline(fin, currLine))
        {
            menuParser(currLine, info);
            menu[info.first] = info.second;
        }
        fin.close();
        currLine = "";
        fin.open(_cntSalesDatabase);
        if (getline(fin, currLine)) salesParser(currLine, totalOrders, totalSales);
        fin.close();
        return;
    }
    void displayMenu(void)
    {
        cout << "\t\t\t\t\t\t\t*** MENU ***\n";
        cout << "Item Code, Item Name, Price, Available Quantity\n";
        for (auto item : menu) cout << item.first << ", " << item.second.first << ", " << item.second.second.first << ", " << item.second.second.second << '\n';
        return;
    }
    void addItem(int code, string &name, double price, int currQuantity)
    {
        menu[code] = {name, {price, currQuantity}};
        return;
    }
    void removeItem(int code)
    {
        menu.erase(code);
        return;
    }
    void changePrice(int code, double newPrice)
    {
        menu[code].second.first = newPrice;
        return;
    }
    void changeQuantity(int code, int newQuantity)
    {
        menu[code].second.second = newQuantity;
        return;
    }
    bool canAcceptOrder(map<int, int> &order)
    {
        for (auto currOrder : order)
        {
            if (menu.find(currOrder.first) == menu.end()) return false;
            else if (menu[currOrder.first].second.second < currOrder.second) return false;
        }        
        return true;
    }
    void generateInvoice(map<int, int> &order)
    {
        ++totalOrders;
        double orderCost = 0.0, currCost;
        ofstream fout(salesDatabase, ios_base :: app);
        cout << "\t\t\t\t\t\t\t*** INVOICE ***\n";
        for (auto currOrder : order)
        {
            currCost = menu[currOrder.first].second.first * currOrder.second;
            menu[currOrder.first].second.second -= currOrder.second;
            totalSales += currCost;
            orderCost += currCost;
            cout << currOrder.first << ", " << menu[currOrder.first].first << ", " << menu[currOrder.first].second.first << ", " << currOrder.second << ", " << currCost << "\n";
            fout << currOrder.first << ", " << menu[currOrder.first].first << ", " << menu[currOrder.first].second.first << ", " << currOrder.second << ", " << currCost << ",\n";
        }
        cout << "Your Total Cost is : " << orderCost << " Rs.\n"; 
        fout.close();
        return;
    }
    void displaySales(void)
    {
        ifstream fin(salesDatabase);
        string currLine;
        cout << "\t\t\t\t\t\t\t*** Sales ***\n";
        cout << "Item Code, Item Name, Item Price, Quantity Ordered, Total Cost\n";
        while(getline(fin, currLine))
        {
            currLine.pop_back();
            cout << currLine << '\n';
        }
        return;
    }
    void loadToDatabase(void)
    {
        ofstream fout(menuDatabase);
        for (auto item : menu) fout << item.first << ", " << item.second.first << ", " << item.second.second.first << ", " << item.second.second.second << ",\n";
        fout.close();
        fout.open(cntSalesDatabase);
        fout << totalOrders << ", " << totalSales << ",\n";
        fout.close();
    }
    static int getOrders(void)
    {
        return totalOrders;
    }
    static double getSales(void)
    {
        return totalSales;
    }
    ~Outlet() {}     
};

int Outlet :: totalOrders = 0;
double Outlet :: totalSales = 0.0;

void chooseOutlet(Outlet *&outletptr)
{
    int outletChoice;
    do
    {
        cout << "Please choose an outlet to continue :\n";
        cout << "1. Vidhyadhar Nagar\n2. Civil Lines\n";
        cin >> outletChoice;
        if (outletChoice < 1 || outletChoice > 2) cout << "Please enter a valid choice (1 - 2).\n\n";
    } while (outletChoice < 1 || outletChoice > 2);
    if (outletChoice == 1) outletptr = new Outlet("VDN_Menu.txt", "VDN_sales.txt", "VDN_cntSales.txt");
    else if (outletChoice == 2) outletptr = new Outlet("CVL_Menu.txt", "CVL_sales.txt", "CVL_cntSales.txt");
    return;
}