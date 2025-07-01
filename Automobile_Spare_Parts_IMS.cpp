#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_ITEMS = 500;
const int MAX_CUSTOMERS = 500;

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

    void getInput()
   {
        cout<< "Enter ID - ";
        cin>>id;
        cin.ignore();  // Clear newline before getline
        cout << "Name - ";
        cin.getline(name, 100);
        cout << "Manufacturer - ";
        cin.getline(manufacturer, 100);
        cout<< "Supplying Dealer - ";
        cin>>dealer_id;
        cout<< "Quantity of the Item - ";
        cin>> quantity;
        cout<< "Costing Price - ";
        cin>> costprice;
        cout<< "Selling Price - ";
        cin>> sellingprice;
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
        char custype[20];
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
                    cout << "You can get Reward upto Rs. " << (loyalpoints/5);
                }
                
            }
        }

        void display()
        {
            if (type == 1)
                strcpy(custype, "Mechanic");
            else
                strcpy(custype, "Common Customer");

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
        Autospareparts()
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
                cout << "Error: Could not open file Items_data.csv\n";
                return;
            }
            string line;
            int i = 0;
            if (!getline(fin, line)) 
            {
                cout << "Error: CSV file is empty or invalid format.\n";
                return;
            }

            while (getline(fin, line) && i < MAX_ITEMS) 
            {
                stringstream ss(line);
                string temp;

                try {
                    getline(ss, temp, ',');
                    ids[i] = stoi(temp);

                    getline(ss, names[i], ',');

                    getline(ss, brands[i], ',');

                    getline(ss, temp, ',');
                    dealers_id[i] = stoi(temp);

                    getline(ss, temp, ',');
                    qty[i] = stoi(temp);

                    getline(ss, temp, ',');
                    costPrices[i] = stof(temp);

                    getline(ss, temp, ',');
                    sellPrices[i] = stof(temp);
                } catch (...) {
                    cerr << "Warning: Skipping invalid line in CSV (line " << i+2 << ")\n";
                    cerr << "Line content: " << line << endl;
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

        void addItem()
        {
            items[itemcount].getInput();
            itemcount++;
            cout<<"Product added Successfully !";
        }

        void displayItems()
        {
            if (itemcount == 0)
            {
                cout << "NO Products are available !";
                return;
            }
            cout << "\n-----------AUTOMOBILE SPARE PARTS-----------\n";
            cout << left << setw(10) << "Prod ID"
                << setw(25) << "Name"
                << setw(20) << "Brand"
                << setw(12) << "Dealer ID"
                << setw(10) << "Qty"
                << setw(12) << "Cost Price"
                << setw(12) << "Sell Price" << endl;
            cout << string(106, '-') << endl;  // separator line       

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
            cout << "The Product ID you've entered is not available in stock!\n";
            cout << "Please enter a valid Product ID.\n";
        }


        void sellItems()
        {
            displayItems();
            cout << endl;
            bool itemthere = false;
            int id, qty, custtype;
            char mobile[15], custname[50];
            cout << "Enter the Product ID to sell- ";
            cin>>id;
            for (int i = 0; i < itemcount; i++) 
            {
                if (items[i].id == id) 
                {
                    itemthere = true;
                    cout << "Enter quantity to sell: ";
                    cin >> qty;
                    if (items[i].quantity < qty) {
                        cout << "Only "<< items[i].quantity <<  " is Available.\n";
                        return;
                    }
                    cin.ignore();
                    cout << "Enter Customer phone number: ";
                    cin.getline(mobile, 15);
                    cout << "Enter Customer name: ";
                    cin.getline(custname, 50);
                    cout << "Enter customer type (1 - Mechanic, 2 - Common Customer): ";
                    cin >> custtype;
                    while (custtype !=1 && custtype!=2)
                    {
                        cout << "Input is invalid - Try Again: ";
                        cin >> custtype;
                    }
                
                    float totsp = qty * items[i].sellingprice;
                    total_selled_sp += totsp;
                    float totcp = qty * items[i].costprice;
                    total_selled_cp += totcp;
                    items[i].quantity -= qty;
                    addCustomer(mobile, custname, custtype, totsp);
                    cout << "Bill Generated! Total price: Rs. " << totsp << "\n";
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
            cout << "\n----- Loyalty Points Report for Mechanics -----\n";
            bool isthere = false;
            cout << left << setw(25) << "Customer Name"
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
                cout << "No loyal Mechanics Found !" << endl;
            }
        }

        void displayCustomers()
        {
            cout << "\n-------- Customers Report --------\n";

            // Table headers
            cout << left << setw(25) << "Customer Name"
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
                cout << "Till now, NO Profit is Made!\n";
            }
            else
            {
                cout << "Profit Earned Today: Rs. " << fixed << setprecision(2) << profit << "\n";
            }
        }


        void saveData() 
        {
            ofstream fout("Items_data.csv");
            if (!fout.is_open()) 
            {
                cout << "Error: Could not open file for writing.\n";
                return;
            }
            fout << "ID,Name,Brand,DealerID,Qty,CostPrice,SellPrice\n";
            for (int i = 0; i < itemcount; i++) {
                fout << items[i].id << ","
                    << items[i].name << ","
                    << items[i].manufacturer << ","
                    << items[i].dealer_id << ","
                    << items[i].quantity << ","
                    << fixed << setprecision(2) << items[i].costprice << ","
                    << fixed << setprecision(2) << items[i].sellingprice
                    << "\n";
            }
            fout.close();
            cout << "Data saved successfully to Items_data.csv!\n";
        }

        void runMenu()
        {
            int choice;
        do 
        {
            cout << "\n=============Inventory Menu============\n";
            cout << "1. Sell Item\n";
            cout << "2. Display All Items\n";
            cout << "3. Add Items\n";
            cout << "4. Show Loyality Points\n";
            cout << "5. Show All Customers\n";
            cout << "6. Today's Profit\n";
            cout << "7. Save Items_data to File\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1: sellItems(); break;
            case 2: displayItems(); break;
            case 3: addItem(); break;
            case 4: loyality(); break;
            case 5: displayCustomers(); break;
            case 6: profitcalc(); break;
            case 7: saveData(); break;
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