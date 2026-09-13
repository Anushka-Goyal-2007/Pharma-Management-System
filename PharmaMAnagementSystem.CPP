// Filename: PharmaManagementSystem.CPP
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <string>

using namespace std;

// Forward declaration of classes
class Medicine;
class Customer;
class Bill;

//------------------------------------ Class Medicine ------------------------------------------
class Medicine
{
protected:
    int med_id, med_qty;
    char med_name[30], med_mfg_date[15], med_exp_date[15];
    float med_price;

public:
    // To input details of medicine
    void med_input()
    {
        cout << "Enter medicine ID: ";
        cin >> med_id;
        cout << "Enter medicine name: ";
        cin.ignore();
        cin.getline(med_name, 30);
        cout << "Enter medicine price: ";
        cin >> med_price;
        cout << "Enter medicine quantity: ";
        cin >> med_qty;
        cout << "Enter manufacturing date (dd-mm-yy): ";
        cin >> med_mfg_date;
        cout << "Enter expiry date (dd-mm-yy): ";
        cin >> med_exp_date;
        cout << endl;
    }

    // To display details of medicine
    void med_display()
    {
        cout << "Medicine ID: " << med_id << endl;
        cout << "Name: " << med_name << endl;
        cout << "Price: Rs " << med_price << endl;
        cout << "Quantity: " << med_qty << endl;
        cout << "Mfg Date: " << med_mfg_date << endl;
        cout << "Exp Date: " << med_exp_date << endl;
        cout << endl;
    }

    // To get medicine ID
    int get_med_id()
    {
        return med_id;
    }

    // To get medicine price
    float get_med_price()
    {
        return med_price;
    }
};

//------------------------------------------ Functions declarations of class Medicine -----------------------------------------------
void insert_medicine();
void search_medicine();
void update_medicine();
void delete_medicine();
void display_all_medicines();

// To add medicines
void insert_medicine()
{
    Medicine m;
    int no_of_med;
    ofstream file("MedicineDataPMS.txt", ios::app | ios::binary);
    if (!file) {
        cout << "Error opening medicine file.\n";
        return;
    }
    cout << "Enter number of medicines to be added: ";
    cin >> no_of_med;
    for (int i = 0; i < no_of_med; i++)
    {
        cout << "\nEnter details for Medicine " << i + 1 << ":\n";
        m.med_input();
        file.write((char*)&m, sizeof(m));
    }
    file.close();
    cout << "\n*********************** Medicine(s) added successfully. ***************************\n";
}

// To search medicine by ID
void search_medicine()
{
    int id;
    bool found = false;
    Medicine m;
    cout << "Enter medicine ID to search: ";
    cin >> id;
    ifstream file("MedicineDataPMS.txt", ios::binary);
    if (!file) {
        cout << "Medicine records file not found.\n";
        return;
    }
    while (file.read((char*)&m, sizeof(m)))
    {
        if (m.get_med_id() == id)
        {
            cout << "\n********** Medicine found : ***********\n" << endl;
            m.med_display();
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "******** Medicine not found. *********\n";
    }
    file.close();
}

// To update details of medicine by ID
void update_medicine()
{
    int id;
    bool flag = false;
    Medicine m;
    fstream file("MedicineDataPMS.txt", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Medicine records file not found.\n";
        return;
    }
    cout << "Enter medicine ID to update: ";
    cin >> id;
    while (!file.eof()) {
        streampos pos = file.tellg();
        file.read((char*)&m, sizeof(m));
        if (!file) break;
        if (m.get_med_id() == id) {
            cout << "\nExisting medicine records:\n\n";
            m.med_display();
            cout << "\nEnter new details:\n\n";
            m.med_input();
            file.seekp(pos);
            file.write((char*)&m, sizeof(m));
            cout << "*********** Medicine updated. *********\n";
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        cout << " Medicine ID not found. \n";
        cout << "Please enter valid medicine ID\n";
    }
    file.close();
}

// To delete medicine by ID
void delete_medicine()
{
    int id;
    bool flag = false;
    Medicine m;
    ifstream infile("MedicineDataPMS.txt", ios::binary);
    ofstream outfile("tempMedicinePMS.txt", ios::binary);

    if (!infile) {
        cout << "Medicine records file not found.\n";
        return;
    }
    cout << "Enter medicine ID to delete: ";
    cin >> id;
    while (infile.read((char*)&m, sizeof(m)))
    {
        if (m.get_med_id() != id)
        {
            outfile.write((char*)&m, sizeof(m));
        }
        else {
            flag = true;
        }
    }
    infile.close();
    outfile.close();
    remove("MedicineDataPMS.txt");
    rename("tempMedicinePMS.txt", "MedicineDataPMS.txt");
    if (flag)
        cout << "********* Medicine deleted *******\n";
    else
        cout << "********* Medicine not found **********\n************** Please enter valid medicine ID *************\n";
}

// To display details of all medicines
void display_all_medicines()
{
    Medicine m;
    ifstream file("MedicineDataPMS.txt", ios::binary);
    if (!file)
    {
        cout << "Medicine records not found\n";
        return;
    }
    cout << "\n--------------------------------- List of Medicines ----------------------------------------\n";
    cout << endl;
    while (file.read((char*)&m, sizeof(m)))
    {
        m.med_display();
    }
    file.close();
}

//------------------------------------------------- class Customer ----------------------------------------
class Customer
{
protected:
    long long int contact_no;
    int cid;
    char cname[30], cemail_id[30];

public:
    void cus_input() // To input details of customer
    {
        cout << "Create and enter ID of your choice: ";
        cin >> cid;
        cout << "Enter name: ";
        cin.ignore();
        cin.getline(cname, 30);
        do {
            cout << "Enter email ID: ";
            cin >> cemail_id;
            if (strchr(cemail_id, '@') && strchr(cemail_id, '.'))
                break;
            else
                cout << "Invalid email. Try again.\n";
        } while (true);

        do
        {
            cout << "Enter 10-digit contact number: ";
            cin >> contact_no;
            if (to_string(contact_no).length() == 10)
                break;
            else {
                cout << "Invalid number. Contact number must be in 10 digits.\n";
            }
        } while (true);
    }

    // To display details of customer
    void cus_display()
    {
        cout << "Customer ID: " << cid << endl;
        cout << "Name: " << cname << endl;
        cout << "Email: " << cemail_id << endl;
        cout << "Contact No.: " << contact_no << endl;
    }

    int get_cus_id() // To get customer ID
    {
        return cid;
    }
};

//-------------------------------------- Functions declarations of class Customer -----------------------------------
void add_customer();
void search_customer();
void update_customer();
void delete_customer();
void display_all_customers();

// To add customers
void add_customer()
{
    Customer c;
    int no_of_cus;
    cout << "\nEnter number of customers to be added : ";
    cin >> no_of_cus;
    cout << endl;
    ofstream file("CustomerDataPMS.txt", ios::app | ios::binary);
    if (!file) {
        cout << "Error opening customer file.\n";
        return;
    }
    for (int i = 0; i < no_of_cus; i++)
    {
        cout << "Enter details for Customer " << i + 1 << ":\n";
        c.cus_input();
        cout << endl;
        file.write((char*)&c, sizeof(c));
    }
    file.close();
    cout << "\n********* Customer added successfully **********\n";
}

// To search customer by ID
void search_customer()
{
    int id;
    bool found = false;
    Customer c;
    cout << "Enter customer ID to search: ";
    cin >> id;
    ifstream file("CustomerDataPMS.txt", ios::binary);
    if (!file) {
        cout << "Customer records file not found.\n";
        return;
    }
    while (file.read((char*)&c, sizeof(c))) {
        if (c.get_cus_id() == id) {
            cout << "\n************ Customer found *************\n" << endl;
            c.cus_display();
            found = true;
            break;
        }
    }
    if (!found)
        cout << "\n*************** Customer not found *************\n*************** Please enter valid customer ID ******************\n";
    file.close();
}

// To update customer by ID
void update_customer()
{
    int id;
    bool flag = false;
    Customer c;
    fstream file("CustomerDataPMS.txt", ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout << "Error opening customer file.\n";
        return;
    }
    cout << "Enter customer ID to update: ";
    cin >> id;
    while (!file.eof())
    {
        streampos pos = file.tellg();
        file.read((char*)&c, sizeof(c));
        if (!file)
            break;
        if (c.get_cus_id() == id)
        {
            cout << "\nExisting Customer Record:\n\n";
            c.cus_display();
            cout << "\nEnter new details for this customer:\n\n";
            c.cus_input();
            file.seekp(pos);  // Move write pointer back to start of this record
            file.write((char*)&c, sizeof(c));
            cout << "\n************** Customer updated successfully ***************\n";
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        cout << "********** Customer ID not found *************\n ************* Please enter valid customer ID ************\n";
    }
    file.close();
}

void delete_customer() // To delete customer by ID
{
    int id;
    bool flag = false;
    Customer c;
    ifstream infile("CustomerDataPMS.txt", ios::binary);
    ofstream outfile("tempCustomerPMS.txt", ios::binary);
    if (!infile) {
        cout << "Customer records file not found.\n";
        return;
    }
    cout << "Enter customer ID to delete: ";
    cin >> id;
    while (infile.read((char*)&c, sizeof(c))) {
        if (c.get_cus_id() != id)
            outfile.write((char*)&c, sizeof(c));
        else
            flag = true;
    }
    infile.close();
    outfile.close();
    remove("CustomerDataPMS.txt");
    rename("tempCustomerPMS.txt", "CustomerDataPMS.txt");
    if (flag)
        cout << "\n******************* Customer deleted *****************\n";
    else
        cout << "******************* Customer not found *****************\n";
}

void display_all_customers() // To display details of all customers
{
    Customer c;
    ifstream file("CustomerDataPMS.txt", ios::binary);
    if (!file)
    {
        cout << "Customer records not found\n";
        return;
    }
    cout << "\n--------------------------------- List of Customers ----------------------------------------\n";
    cout << endl;
    while (file.read((char*)&c, sizeof(c)))
    {
        c.cus_display();
        cout << endl;
    }
    file.close();
}

//--------------------------------------------------- class Bill -------------------------------------------------------
class Bill : public Customer, public Medicine
{
private:
    int bill_no;
    char date[20];
    float total_amount;
    // Medicine information
    char med_name_bill[100][50];
    int med_qty_bill[100];
    float med_price_bill[100];
    int no; // No. of medicines in this bill

public:
    // Return bill number
    int get_bill_no() { return bill_no; }
    // Return bill date
    char* get_date() { return date; }

    // Return last bill number from file
    int get_last_bill_no()
    {
        int last_bill_no = 1000;
        ifstream file("Billno.txt", ios::binary);
        if (file.read((char*)&last_bill_no, sizeof(int))) {
            // Successfully read
        }
        file.close();
        return last_bill_no;
    }

    // Update bill number in file
    void update_bill_no(int new_bill_no) {
        ofstream file("Billno.txt", ios::binary | ios::trunc);
        file.write((char*)&new_bill_no, sizeof(int));
        file.close();
    }

    // Generate a new bill
    void generate_bill() {
        bill_no = get_last_bill_no() + 1;
        update_bill_no(bill_no);
        time_t now = time(0);
        strftime(date, sizeof(date), "%d-%m-%y", localtime(&now));
        cout << "\nEnter Customer Details:\n";
        cus_input();
        cout << "\nEnter number of medicines purchased: ";
        cin >> no;
        for (int i = 0; i < no; i++) {
            cout << "\nEnter details for Medicine " << i + 1 << ":\n";
            cout << "Medicine Name: ";
            cin.ignore();
            cin.getline(med_name_bill[i], 50);
            cout << "Quantity: ";
            cin >> med_qty_bill[i];
            cout << "Price per unit: ";
            cin >> med_price_bill[i];
        }
        total_amount = 0;
        for (int i = 0; i < no; i++) {
            total_amount += med_qty_bill[i] * med_price_bill[i];
        }
        cout << "\n********** Bill created successfully *************\n";
    }

    // Display full bill
    void display_bill() {
        cout << "\n------------------ BILL ------------------\n";
        cout << "Bill No. : " << bill_no << "\n";
        cout << "Date     : " << date << "\n";
        cout << "\nCustomer Details:\n";
        cus_display();
        cout << "\nMedicine Details:\n";
        float subtotal = 0;
        for (int i = 0; i < no; i++) {
            cout << "\nMedicine " << i + 1 << ":\n";
            cout << "Name     : " << med_name_bill[i] << "\n";
            cout << "Quantity : " << med_qty_bill[i] << "\n";
            cout << "Price    : Rs. " << med_price_bill[i] << "\n";
            float item_total = med_qty_bill[i] * med_price_bill[i];
            cout << "Subtotal : Rs. " << item_total << "\n";
            subtotal += item_total;
        }
        float gst = subtotal * 0.18;
        float final_amount = subtotal + gst;
        cout << "\n------------------------------------------\n";
        cout << "Total (before GST): Rs. " << subtotal << "\n";
        cout << "GST 18%           : Rs. " << gst << "\n";
        cout << "Final Amount      : Rs. " << final_amount << "\n";
        cout << "------------------------------------------\n";
    }

    // Write the bill to file
    void write_to_file() {
        ofstream file("BillsPMS.txt", ios::binary | ios::app);
        file.write((char*)this, sizeof(Bill));
        file.close();
    }

    // Search bill by date
    void search_bill_by_date(char date_to_search[20]) {
        ifstream file("BillsPMS.txt", ios::binary);
        if (!file) {
            cout << "\n Could not open Bills file.\n";
            return;
        }
        Bill temp;
        bool found = false;
        // First pass: just show matching bills
        while (file.read((char*)&temp, sizeof(Bill))) {
            if (strcmp(temp.date, date_to_search) == 0) {
                temp.display_bill();
                found = true;
            }
        }
        file.close();
        if (!found) {
            cout << "\n No bills found on: " << date_to_search << "\n";
            return;
        }
        // Ask user if they want to export
        string choice;
        cout << "\nDo you want to export the matching bills to a file? (Yes/No): ";
        cin >> choice;
        if (choice == "YES" || choice == "yes" || choice == "Yes") {
            ifstream file2("BillsPMS.txt", ios::binary);
            ofstream txt("BillsExport.txt");
            while (file2.read((char*)&temp, sizeof(Bill))) {
                if (strcmp(temp.date, date_to_search) == 0) {
                    txt << "Bill No.: " << temp.bill_no << "\n";
                    txt << "Date: " << temp.date << "\n";
                    txt << "Customer ID: " << temp.get_cus_id() << "\n";
                    txt << "Customer Name: " << temp.cname << "\n";
                    txt << "Customer Email: " << temp.cemail_id << "\n";
                    txt << "Customer Contact: " << temp.contact_no << "\n";
                    for (int i = 0; i < temp.no; i++) {
                        txt << "Medicine " << (i + 1) << ": " << temp.med_name_bill[i] << "\n";
                        txt << "Price: " << temp.med_price_bill[i] << "\n";
                        txt << "Quantity: " << temp.med_qty_bill[i] << "\n";
                    }
                    txt << "Total Amount: " << temp.total_amount << "\n";
                    txt << "-----------------------------------------\n";
                }
            }
            file2.close();
            txt.close();
            cout << "\nBills successfully exported to 'BillsExport.txt'.\n";
        }
    }

    // Search bill by bill number
    void search_bill_by_id(int id) {
        ifstream file("BillsPMS.txt", ios::binary);
        Bill temp;
        bool found = false;
        if (!file) {
            cout << "\n Could not open Bills file.\n";
            return;
        }
        while (file.read((char*)&temp, sizeof(Bill))) {
            if (temp.get_bill_no() == id) {
                temp.display_bill();
                found = true;
                break;
            }
        }
        file.close();
        if (!found)
            cout << "\n Bill not found with ID: " << id << "\n";
    }

    // Display all bills
    void display_all_bills() {
        ifstream file("BillsPMS.txt", ios::binary);
        if (!file) {
            cout << "\n Could not open Bills file.\n";
            return;
        }
        Bill temp;
        bool found = false;
        int counter = 0;
        cout << "\n------------------- ALL BILLS ----------------------\n";
        while (file.read((char*)&temp, sizeof(Bill))) {
            counter++;
            cout << "\n Reading bill " << counter << endl;
            temp.display_bill();
            found = true;
            // Infinite print protection
            if (counter > 100) {
                cout << "\n[ERROR] Too many bills! Stopping.\n";
                break;
            }
        }
        file.close();
        if (!found) {
            cout << "\n No bills found in the system.\n";
        }
    }

    void update_bill_by_id(int id) {
        fstream file("BillsPMS.txt", ios::in | ios::out | ios::binary);
        if (!file) {
            cout << " Error opening file.\n";
            return;
        }
        Bill temp;
        bool found = false;
        streampos pos;
        while (!file.eof()) {
            pos = file.tellg(); // Save current position
            file.read((char*)&temp, sizeof(Bill));
            if (file && temp.get_bill_no() == id) {
                cout << "\n Bill Found. Updating details...\n";
                // Re-enter customer details
                cout << "\n--- Update Customer Details ---\n";
                temp.cus_input();
                // Re-enter medicines
                cout << "\nEnter number of medicines purchased: ";
                cin >> temp.no;
                for (int i = 0; i < temp.no; i++) {
                    cout << "\nEnter details for Medicine " << i + 1 << ":\n";
                    cout << "Medicine Name: ";
                    cin.ignore();
                    cin.getline(temp.med_name_bill[i], 50);
                    cout << "Quantity: ";
                    cin >> temp.med_qty_bill[i];
                    cout << "Price per unit: ";
                    cin >> temp.med_price_bill[i];
                }
                // Recalculate total
                temp.total_amount = 0;
                for (int i = 0; i < temp.no; i++) {
                    temp.total_amount += temp.med_qty_bill[i] * temp.med_price_bill[i];
                }
                // Update date
                time_t now = time(0);
                strftime(temp.date, sizeof(temp.date), "%d-%m-%y", localtime(&now));
                // Move pointer back to start of this bill's record
                file.seekp(pos);
                file.write((char*)&temp, sizeof(Bill));
                cout << "\n Bill updated successfully.\n";
                found = true;
                break;
            }
        }
        if (!found)
            cout << " Bill ID " << id << " not found.\n";
        file.close();
    }

    // Delete bill by ID
    void delete_bill_by_id(int id) {
        ifstream infile("BillsPMS.txt", ios::binary);
        ofstream outfile("tempBillsPMS.txt", ios::binary);
        Bill temp;
        bool found = false;
        if (!infile) {
            cout << "\n Could not open Bills file.\n";
            return;
        }
        while (infile.read((char*)&temp, sizeof(Bill))) {
            if (temp.get_bill_no() != id) {
                outfile.write((char*)&temp, sizeof(Bill));
            } else {
                found = true;
            }
        }
        infile.close();
        outfile.close();
        remove("BillsPMS.txt");
        rename("tempBillsPMS.txt", "BillsPMS.txt");
        if (found)
            cout << "\n Bill with ID " << id << " deleted successfully.\n";
        else
            cout << "\n Bill with ID " << id << " not found.\n";
    }
};

// Simple password verification
bool login() {
    string pass;
    cout << "\n\nEnter password to login: ";
    cin >> pass;
    return (pass == "admin123");
}

int main() {
    int choice, bill_id;
    char bill_date[20];
    Bill bobj;

    cout << "\n------------------------------------ MEDITRACK : PHARMACY INVENTORY & SALES SYSTEM ---------------------------------\n";
    if (login()) {
        cout << "\nLogin successful." << endl;
        cout << "\nWelcome to the Meditrack : Pharmacy Inventory & Sales System \n";

        // Driving the pharma management system menu
        do {
            cout << endl << "PHARMA MANAGEMENT SYSTEM : FUNCTIONS MENU \n";
            cout << "\n1.  Add Medicine\n";
            cout << "2.  Search Medicine\n";
            cout << "3.  Update Medicine\n";
            cout << "4.  Delete Medicine\n";
            cout << "5.  Display all medicines\n";
            cout << "6.  Add Customer\n";
            cout << "7.  Search Customer\n";
            cout << "8.  Update Customer\n";
            cout << "9.  Delete Customer\n";
            cout << "10. Display all Customers\n";
            cout << "11. Create new bill\n";
            cout << "12. Display all bills\n";
            cout << "13. Search bill by Date\n";
            cout << "14. Search bill by ID\n";
            cout << "15. Delete bill by ID\n";
            cout << "16. Update bill by ID\n";
            cout << "17. Exit\n";
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: insert_medicine(); break;
            case 2: search_medicine(); break;
            case 3: update_medicine(); break;
            case 4: delete_medicine(); break;
            case 5: display_all_medicines(); break;
            case 6: add_customer(); break;
            case 7: search_customer(); break;
            case 8: update_customer(); break;
            case 9: delete_customer(); break;
            case 10: display_all_customers(); break;
            case 11: {
                bobj.generate_bill();
                bobj.write_to_file();
                break;
            }
            case 12: bobj.display_all_bills(); break;
            case 13: {
                cout << "Enter bill date to search (dd-mm-yy): ";
                cin >> bill_date;
                bobj.search_bill_by_date(bill_date);
                break;
            }
            case 14: {
                cout << "Enter Bill ID to search: ";
                cin >> bill_id;
                bobj.search_bill_by_id(bill_id);
                break;
            }
            case 15: {
                cout << "Enter Bill ID to delete: ";
                cin >> bill_id;
                bobj.delete_bill_by_id(bill_id);
                break;
            }
            case 16: {
                int update_id;
                cout << "Enter Bill ID to update: ";
                cin >> update_id;
                bobj.update_bill_by_id(update_id);
                break;
            }
            case 17:
                cout << "Exiting the program.... \nGOODBYE!\n";
                break;
            default:
                cout << "Invalid choice!!\n";
                break;
            }
        } while (choice != 17);
    }
    else {
        cout << "Incorrect password! Login unsuccessful.\n";
        cout << "Please enter valid password.\n";
    }

    return 0;
}
