#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_ITEMS = 1000;
const int MAX_CUSTOMERS = 1000;

class item
{
    public:
        int id;
        char name[100];
        char manufacturer[100];
        int dealer_id;
        int quantity;
        float costprice;
        float sellingprice;

void getInput(int new_id)
{
    id = new_id;
    cin.ignore();
    cout << "   Name - ";
    cin.getline(name, 100);
    cout << "   Manufacturer - ";
    cin.getline(manufacturer, 100);
    cout << "    Supplying Dealer - ";
    cin >> dealer_id;
    cout << "    Quantity of the Item - ";
    cin >> quantity;
    cout << "    Costing Price - ";
    cin >> costprice;
    cout << "    Selling Price - ";
    cin >> sellingprice;
    cin.ignore();
}

    void putoutput()
    {
        cout << left << setw(10) << id
            << setw(30) << name
            << setw(20) << manufacturer
            << setw(12) << dealer_id
            << setw(10) << quantity
            << "$ " << setw(10) << fixed << setprecision(2) << costprice
            << "$ " << setw(10) << fixed << setprecision(2) << sellingprice
            << endl;
    }

};

class customer 
{
    public:
        char name[50];
        char mobile[15];
        int type;
        float totalspent;
        int loyalpoints;
        bool reward;

        customer()
        {
            totalspent = 0;
            loyalpoints = 0;
            reward = false ;
        }

        void update (float amount)
        {
            totalspent +=  amount;
            if (type == 1)
            {
                int points = amount * 0.25;
                loyalpoints += points;
                if (loyalpoints > 2000 && !reward)
                {
                    reward = true;
                    cout << "   You can get Reward upto Rs. " << (loyalpoints/5);
                }
                
            }
        }

        void display()
        {
            string custype;
            if (type == 1) 
            {
                custype = "Mechanic";
            } else 
            {
                custype = "Common Customer";
            }
            cout << left << setw(25) << name
                << setw(15) << mobile
                << setw(20) << custype
                << "Rs. " << setw(12) << fixed << setprecision(2) << totalspent
                << setw(10) << loyalpoints
                << endl;
        }

};

class Autospareparts
{
    item items[MAX_ITEMS];
    customer customers[MAX_CUSTOMERS];
    int itemcount = 0;
    int customercount = 0;
    float total_selled_cp = 0;
    float total_selled_sp =0;
    public:
        void initItemdata()
        {
            int ids[MAX_ITEMS] ;
            string names[MAX_ITEMS];
            string brands[MAX_ITEMS];
            int dealers_id[MAX_ITEMS];
            int qty[MAX_ITEMS];
            float costPrices[MAX_ITEMS] ;
            float sellPrices[MAX_ITEMS] ;


            ifstream fin("Items_data.csv");
            if (!fin.is_open()) 
            {
                cout << "   Error: Could not open file Items_data.csv\n";
                return;
            }
            string item_line;
            int i = 0;
            if (!getline(fin, item_line)) 
            {
                cout << "   Error: CSV file is empty or invalid format.\n";
                return;
            }

            while (getline(fin, item_line) && i < MAX_ITEMS) 
            {
                stringstream iL(item_line);
                string temp;

                try {
                    getline(iL, temp, ',');
                    ids[i] = stoi(temp);

                    getline(iL, names[i], ',');

                    getline(iL, brands[i], ',');

                    getline(iL, temp, ',');
                    dealers_id[i] = stoi(temp);

                    getline(iL, temp, ',');
                    qty[i] = stoi(temp);

                    getline(iL, temp, ',');
                    costPrices[i] = stof(temp);

                    getline(iL, temp, ',');
                    sellPrices[i] = stof(temp);
                } catch (...) {
                    cerr << "   Warning: Skipping invalid item_line in CSV (item_line " << i+2 << ")\n";
                    cerr << "   item_line content: " << item_line << endl;
                    continue;
                }
                i++;
            }
            itemcount = i;
        
            for (int i = 0 ; i<itemcount; i++)
            {
                items[i].id = ids[i];
                strcpy(items[i].name, names[i].c_str());
                strcpy(items[i].manufacturer, brands[i].c_str());
                items[i].dealer_id = dealers_id[i];
                items[i].quantity = qty[i];
                items[i].costprice = costPrices[i];
                items[i].sellingprice = sellPrices[i];
            }
        }
    
        void initCustomerdata()
        {
            string name[MAX_CUSTOMERS];
            string mobile[MAX_CUSTOMERS];
            int type[MAX_CUSTOMERS];
            float totalspent[MAX_CUSTOMERS];
            int loyalpoints[MAX_CUSTOMERS];
            bool reward[MAX_CUSTOMERS];

            ifstream fin("customer_data.csv");
            if (!fin.is_open()) 
            {
                cout << "   Error: Could not open file Customer_data.csv\n";
                return;
            }
            string customer_line;
            int i = 0;

            if (!getline(fin, customer_line)) 
            {
                cout << "   Error: CSV file is empty or invalid format.\n";
                return;
            }
            while (getline(fin, customer_line) && i < MAX_ITEMS) 
            {
                stringstream cL(customer_line);
                string temp;

                try
                {
                    getline(cL, name[i], ',');
                    getline(cL, mobile[i], ',');
                    getline(cL, temp, ',');
                    type[i]= stoi(temp);
                    getline(cL, temp, ',');
                    totalspent[i]= stof(temp);
                    getline(cL, temp, ',');
                    loyalpoints[i]= stoi(temp);
                    getline(cL, temp, ',');
                    if (temp == "1" || temp == "true" || temp == "TRUE")
                        reward[i] = true;
                    else if (temp == "0" || temp == "false" || temp == "FALSE")
                        reward[i] = false;
                }
                catch (...) 
                {
                    cerr << "   Warning: Skipping invalid customer_line in CSV (customer_line " << i+2 << ")\n";
                    cerr << "   customer_line content: " << customer_line << endl;
                    continue;
                }
                i++;
            }
            customercount = i;
        
            for (int i = 0 ; i < customercount; i++)
            {
                strcpy(customers[i].name, name[i].c_str());
                strcpy(customers[i].mobile, mobile[i].c_str());
                customers[i].type = type[i];
                customers[i].totalspent = totalspent[i];
                customers[i].loyalpoints = loyalpoints[i];
                customers[i].reward = reward[i];
            }
        }

        Autospareparts()
        {
            initItemdata();
            initCustomerdata();
        }

        void deleteitem()
        {
            int delId;
            bool found = false;
            cout<<"Enter the Product ID- ";
            cin>>delId;
            for (int i =0 ; i<itemcount; i++)
            {
                if (items[i].id == delId)
                {
                    found = true;
                    for (int j = i; j < itemcount - 1; j++)
                    {
                        items[j] = items[j + 1];
                    }
                    itemcount--;                
                }
            }
            if (found==0)
            {
                cout<<"Item is not Available! ";
                return;
            }
        }

        void addItem()
        {
            int new_qty;
            int new_id;
            cout << "Enter ID - ";
            cin >> new_id;
            for (int i = 0; i < itemcount; ++i) 
            {
                if (items[i].id == new_id) {
                    cout<<"Enter the Quantity- ";
                    cin>>new_qty;
                    items[i].quantity += new_qty;
                    return;
                }
            }
            items[itemcount].getInput(new_id);
            itemcount++;
            cout<<"     Product added Successfully !";
        }

        void displayItems()
        {
            if (itemcount == 0)
            {
                cout << "NO Products are available !";
                return;
            }
            cout << "   \n-----------AUTOMOBILE SPARE PARTS-----------\n";
            cout << left <<"    "<< setw(10) << "Prod ID"
                << setw(25) << "Name"
                << setw(20) << "Brand"
                << setw(12) << "Dealer ID"
                << setw(10) << "Qty"
                << setw(12) << "Cost Price"
                << setw(12) << "Sell Price" << endl;
            cout << string(106, '-') << endl;

            for (int i = 0; i < itemcount; i++)
            {
               items[i].putoutput();
            }    
        }

        void addCustomer(const char* mobileno, const char* name, int type, float totamount)
        {
            for (int i = 0 ; i < customercount ; i++)
            {
                if(strcmp(customers[i].mobile, mobileno) ==0 )
                {
                    customers[i].update(totamount);
                    return;
                }
            }
            strcpy(customers[customercount].mobile, mobileno);
            strcpy(customers[customercount].name, name);
            customers[customercount].type = type;
            customers[customercount].update(totamount);
            customercount++;
        }

        void errormsg()
        {
            cout << "   The Product ID you've entered is not available in stock!\n";
            cout << "   Please enter a valid Product ID.\n";
        }


        void sellItems()
        {
            displayItems();
            cout << endl;
            bool itemthere = false;
            int id, qty, custtype;
            char mobile[15], custname[50];
            cout << "   Enter the Product ID to sell- ";
            cin>>id;
            for (int i = 0; i < itemcount; i++) 
            {
                if (items[i].id == id) 
                {
                    itemthere = true;
                    cout << "   Enter quantity to sell: ";
                    cin >> qty;
                    if (items[i].quantity < qty) {
                        cout << "   Only "<< items[i].quantity <<  " is Available.\n";
                        return;
                    }
                    cin.ignore();
                    cout << "   Enter Customer phone number: ";
                    cin.getline(mobile, 15);
                    cout << "   Enter Customer name: ";
                    cin.getline(custname, 50);
                    cout << "   Enter customer type (1 - Mechanic, 2 - Common Customer): ";
                    cin >> custtype;
                    while (custtype !=1 && custtype!=2)
                    {
                        cout << "   Input is invalid - Try Again: ";
                        cin >> custtype;
                    }
                
                    float totsp = qty * items[i].sellingprice;
                    total_selled_sp += totsp;
                    float totcp = qty * items[i].costprice;
                    total_selled_cp += totcp;
                    items[i].quantity -= qty;
                    addCustomer(mobile, custname, custtype, totsp);
                    cout << "   Bill Generated! Total price: Rs. " << totsp << "\n";
                    cout << endl;
                    return;
                }
            }
            if (itemthere == false)
            {
                errormsg();
            }
        }
        void loyality()
        {
            cout << "   \n----- Loyalty Points Report for Mechanics -----\n";
            bool isthere = false;
            cout << left <<"    "<< setw(25) << "Customer Name"
                << setw(15) << "Mobile"
                << setw(20) << "Type"
                << setw(16) << "Total Spent"
                << setw(10) << "Points" << endl;
            cout << string(86, '-') << endl;
            for (int i = 0; i < customercount; i++)
            {
                if (customers[i].type == 1)
                {
                    customers[i].display();
                    cout << endl;
                    isthere = true;
                }
            }
            if (!isthere)
            {
                cout << "   No loyal Mechanics Found !" << endl;
            }
        }

        void displayCustomers()
        {
            cout << "\n-------- Customers Report --------\n";

            cout << left << "   " << setw(25) << "Customer Name"
                << setw(15) << "Mobile"
                << setw(20) << "Type"
                << setw(16) << "Total Spent"
                << setw(10) << "Points" << endl;

            cout << string(86, '-') << endl;

            // Display each customer in one row
            for (int i = 0; i < customercount; i++)
            {
                customers[i].display();
                cout << endl;
            }
        }

        void profitcalc()
        {
            float profit = total_selled_sp - total_selled_cp;
            if (profit == 0)
            {
                cout << "   Till now, NO Profit is Made!\n";
            }
            else
            {
                cout << "   Profit Earned Today: Rs. " << fixed << setprecision(2) << profit << "\n";
            }
        }


        void saveData() 
        {
            ofstream itemdata("Items_data.csv");
            if (!itemdata.is_open()) 
            {
                cout << "   Error: Could not open file Items_data.csv for writing.\n";
                return;
            }

            itemdata << "ID,Name,Brand,DealerID,Qty,CostPrice,SellPrice\n";
            for (int i = 0; i < itemcount; i++) {
                itemdata << items[i].id << ","
                        << items[i].name << ","
                        << items[i].manufacturer << ","
                        << items[i].dealer_id << ","
                        << items[i].quantity << ","
                        << fixed << setprecision(2) << items[i].costprice << ","
                        << fixed << setprecision(2) << items[i].sellingprice
                        << "\n";
            }
            itemdata.close();

            ofstream customerdata("Customer_data.csv");
            if (!customerdata.is_open()) 
            {
                cout << "   Error: Could not open file Customer_data.csv for writing.\n";
                return;
            }

            customerdata << "Name,Mobile,Type,TotalSpent,LoyalPoints,Reward\n";
            for (int i = 0; i < customercount; i++) 
            {
                string custype = (customers[i].type == 1) ? "Mechanic" : "Common Customer";

                customerdata << customers[i].name << ","
                            << customers[i].mobile << ","
                            << custype << ","
                            << fixed << setprecision(2) << customers[i].totalspent << ","
                            << customers[i].loyalpoints << ","
                            << (customers[i].reward ? "1" : "0")
                            << "\n";
            }
            customerdata.close();

            cout << "   Data saved successfully!\n";
        }


        void runMenu()
        {
            int choice;
        do 
        {
            cout << "\n=============Inventory Menu============\n";
            cout << "   1. Sell Item\n";
            cout << "   2. Display All Items\n";
            cout << "   3. Add Items\n";
            cout << "   4. Delete a Item\n";
            cout << "   5. Show Loyality Points\n";
            cout << "   6. Show All Customers\n";
            cout << "   7. Today's Profit\n";
            cout << "   8. Save Data to File\n";
            cout << "   0. Exit\n";
            cout << "   Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1: sellItems(); break;
            case 2: displayItems(); break;
            case 3: addItem(); break;
            case 4: deleteitem(); break;
            case 5: loyality(); break;
            case 6: displayCustomers(); break;
            case 7: profitcalc(); break;
            case 8: saveData(); break;
            case 0: cout << "Exiting!..... "; break;
            default: cout << "Invalid Input / Choice!..... "; break;
            }
            
        }while (choice!=0);    
    }

        ~Autospareparts() 
        {
            saveData();
        }

};

int main()
{
    Autospareparts july01th;
    july01th.runMenu();
    return 0;
}