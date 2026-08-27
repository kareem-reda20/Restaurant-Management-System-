#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>


using namespace std;

// ============================================================================
// SHARED CODE — copy exactly, do not modify
// ============================================================================
enum class OrderType { DineIn, Takeaway, Delivery };
enum class OrderStatus { New, Preparing, Ready, Served, Completed, Cancelled };
enum class TableStatus { Available, Reserved, Occupied, OutOfService };
enum class ReservationStatus { Pending, Confirmed, Completed, Cancelled };
enum class PaymentMethod { Cash, Card, MobilePayment };
enum class PaymentStatus { Completed, Refunded };
enum class DeliveryStatus { Assigned, OnTheWay, Delivered, Cancelled };
enum class EmployeeRole { Manager, Chef, Waiter, Cashier, DeliveryDriver };
enum class MenuCategory { Appetizer, MainCourse, Dessert, Drink };

// ============================================================================
// Helper to print OrderStatus as text
// ============================================================================
string statusToString(OrderStatus s)
{
    switch (s)
    {
    case OrderStatus::New:
        return "New";
    case OrderStatus::Preparing:
        return "Preparing";
    case OrderStatus::Ready:
        return "Ready";
    case OrderStatus::Served:
        return "Served";
    case OrderStatus::Completed:
        return "Completed";
    case OrderStatus::Cancelled:
        return "Cancelled";
    }
    return "Unknown";
}

string typeToString(OrderType t)
{
    switch (t)
    {
    case OrderType::DineIn:
        return "Dine-In";
    case OrderType::Takeaway:
        return "Takeaway";
    case OrderType::Delivery:
        return "Delivery";
    }
    return "Unknown";
}

// ============================================================================
// Helpers to print enums as text 
// ============================================================================
string paymentMethodToString(PaymentMethod m) {
    switch (m) {
    case PaymentMethod::Cash: return "Cash";
    case PaymentMethod::Card: return "Card";
    case PaymentMethod::MobilePayment: return "Mobile Payment";
    }
    return "Unknown";
}

string paymentStatusToString(PaymentStatus s) {
    switch (s) {
    case PaymentStatus::Completed: return "Completed";
    case PaymentStatus::Refunded: return "Refunded";
    }
    return "Unknown";
}

string deliveryStatusToString(DeliveryStatus s) {
    switch (s) {
    case DeliveryStatus::Assigned: return "Assigned";
    case DeliveryStatus::OnTheWay: return "On The Way";
    case DeliveryStatus::Delivered: return "Delivered";
    case DeliveryStatus::Cancelled: return "Cancelled";
    }
    return "Unknown";
}

string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[64];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d",
        1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
        ltm->tm_hour, ltm->tm_min);
    return string(buf);
}

void clearScreen() {//yousef
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}




// Customer

class Customer {
private:
    int customerID;
    string name;
    string phoneNumber;
    string address;
    string email;

public:
    // Constructor
    Customer(int id = 0, string n = "", string phone = "", string addr = "", string em = "")
        : customerID(id), name(n), phoneNumber(phone), address(addr), email(em) {   //recieve data then initialize variables
    }


    // Getters   (no modifications )
    int getCustomerID() const { return customerID; }
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    string getAddress() const { return address; }
    string getEmail() const { return email; }

    // Setters
    void setName(string n) { name = n; }                        //change and edit name
    void setPhoneNumber(string phone) { phoneNumber = phone; } // change and edit number
    void setAddress(string addr) { address = addr; }           //.................address
    void setEmail(string em) { email = em; }                   //................email


    // Display Methods
    void displayInfo() const {
        cout << "ID: " << customerID << "\n";
        cout << "Name: " << name << "\n";
        cout << "Phone: " << phoneNumber << "\n";
        cout << "Address: " << address << "\n";
        cout << "Email: " << email << "\n";

    }
};

//CustomerManager
class CustomerManager {
private:
    vector<Customer> customers;   //dynamic array.. هيتخزن فيها بيانات الcustomers

public:
    // Add Customer
    bool addCustomer(Customer c) {
        if (c.getName().empty()) {
            cout << "Error: Customer name cannot be empty.\n";
            return false;
        }

        if (c.getPhoneNumber().empty()) {
            cout << "Error: Phone number cannot be empty.\n";
            return false;
        }

        for (const auto& cust : customers) {   // no repeated id
            if (cust.getCustomerID() == c.getCustomerID()) {
                cout << "Error: Customer ID " << c.getCustomerID() << " already exists.\n";
                return false;
            }
        }

        customers.push_back(c);       // بتضيف ال customer في اخر ال vector
        // بتكبر حجم ال vector تلقائيا مكان زيادة
        cout << "Customer added successfully.\n";
        return true;
    }

    // Display All Customers
    void displayAllCustomers() const {
        if (customers.empty()) {
            cout << "No customers found.\n";
            return;
        }

        cout << "\n CUSTOMER LIST \n";
        for (const auto& cust : customers) {
            cust.displayInfo();
        }
    }

    // Search Customer
    Customer* searchCustomer(int customerID) {
        for (auto& cust : customers) {
            if (cust.getCustomerID() == customerID) {
                return &cust;
            }
        }
        return nullptr;
    }

    //  Update Customer
    bool updateCustomer(int customerID, string newName, string newPhone, string newAddress, string newEmail) {
        Customer* cust = searchCustomer(customerID);  // بنستدعي دالة البحث عشان تعمل pointer.. علي ال customer اللي عاوزينه

        if (cust == nullptr) {
            cout << "Error: Customer with ID " << customerID << " not found.\n";
            return false;
        }

        if (newName.empty()) {
            cout << "Error: Updated name cannot be empty.\n";
            return false;
        }

        if (newPhone.empty()) {
            cout << "Error: Updated phone number cannot be empty.\n";
            return false;
        }

        cust->setName(newName);    // saving updates
        cust->setPhoneNumber(newPhone);
        cust->setAddress(newAddress);
        cust->setEmail(newEmail);

        cout << "Customer updated successfully.\n";
        return true;
    }

    // Display Customer Orders (Stub)
    void displayCustomerOrders(int customerID) {   // لسه هتتظبط بعد ال integration
        if (searchCustomer(customerID) == nullptr) {
            cout << "Error: Customer with ID " << customerID << " not found.\n";
            return;
        }

    }

    //  Display Customer Reservations (Stub)
    void displayCustomerReservations(int customerID) { // بردو هتتظبط بعد ال integration
        if (searchCustomer(customerID) == nullptr) {
            cout << "Error: Customer with ID " << customerID << " not found.\n";
            return;
        }

    }
};



// Reservation

class Reservation {
private:
    int reservationID;
    int customerID;
    int tableID;
    string date;
    string time;
    int numberOfGuests;
    ReservationStatus status;

public:
    // Constructor
    Reservation(int rID = 0, int cID = 0, int tID = 0, string d = "", string t = "", int guests = 0, ReservationStatus s = ReservationStatus::Pending)
        : reservationID(rID), customerID(cID), tableID(tID), date(d), time(t), numberOfGuests(guests), status(s) {  //recieve data and initialize
    }


    // Getters
    int getReservationID() const { return reservationID; }
    int getCustomerID() const { return customerID; }
    int getTableID() const { return tableID; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    int getNumberOfGuests() const { return numberOfGuests; }
    ReservationStatus getStatus() const { return status; }


    // Setters
    void setCustomerID(int cID) { customerID = cID; }    //update or change id
    void setTableID(int tID) { tableID = tID; }
    void setDate(string d) { date = d; }
    void setTime(string t) { time = t; }
    void setNumberOfGuests(int guests) { numberOfGuests = guests; }
    void setStatus(ReservationStatus s) { status = s; }


    // Display Method

    void displayInfo() const {
        cout << "Reservation ID: " << reservationID << "\n";
        cout << "Customer ID: " << customerID << "\n";
        cout << "Table ID: " << tableID << "\n";
        cout << "Date: " << date << "\n";
        cout << "Time: " << time << "\n";
        cout << "Guests: " << numberOfGuests << "\n";
        cout << "Status: ";
        switch (status) {
        case ReservationStatus::Pending: cout << "Pending\n"; break;
        case ReservationStatus::Confirmed: cout << "Confirmed\n"; break;
        case ReservationStatus::Completed: cout << "Completed\n"; break;
        case ReservationStatus::Cancelled: cout << "Cancelled\n"; break;
        }

    }
};


// ReservationManager
class ReservationManager {
private:
    vector<Reservation> reservations;

public:
    // Create Reservation
    bool createReservation(Reservation r) {
        if (r.getNumberOfGuests() <= 0) {
            cout << "Error: Number of guests must be greater than zero.\n";
            return false;
        }

        for (const auto& res : reservations) {
            if (res.getReservationID() == r.getReservationID()) {
                cout << "Error: Reservation ID " << r.getReservationID() << " already exists.\n";
                return false;
            }
        }

        if (!checkTableAvailability(r.getTableID(), r.getDate(), r.getTime())) {
            cout << "Error: Table " << r.getTableID() << " is already reserved at this date and time \n";
            return false;
        }

        reservations.push_back(r);
        cout << "Reservation created successfully \n";
        return true;
    }

    // Confirm Reservation
    bool confirmReservation(int reservationID) {
        for (auto& res : reservations) {
            if (res.getReservationID() == reservationID) {
                if (res.getStatus() == ReservationStatus::Cancelled) {
                    cout << "Error: Cannot confirm a cancelled reservation.\n";
                    return false;
                }
                res.setStatus(ReservationStatus::Confirmed);
                cout << "Reservation " << reservationID << " confirmed successfully.\n";
                return true;
            }
        }
        cout << "Error: Reservation ID " << reservationID << " not found.\n";
        return false;
    }

    //  Cancel Reservation
    bool cancelReservation(int reservationID) {
        for (auto& res : reservations) {
            if (res.getReservationID() == reservationID) {
                if (res.getStatus() == ReservationStatus::Completed) {
                    cout << "Error: Cannot cancel a completed reservation.\n";
                    return false;
                }
                res.setStatus(ReservationStatus::Cancelled);
                cout << "Reservation " << reservationID << " cancelled successfully.\n";
                return true;
            }
        }
        cout << "Error: Reservation ID " << reservationID << " not found.\n";
        return false;
    }

    //  Display Reservation
    void displayReservations() const {
        if (reservations.empty()) {
            cout << "No reservations found.\n";
            return;
        }

        cout << "\n RESERVATION LIST \n";
        for (const auto& res : reservations) {
            res.displayInfo();
        }
    }

    // Search Reservation
    Reservation* searchReservation(int reservationID) {
        for (auto& res : reservations) {          //بيلف علي كل الحجوزات يتأكد هل ال id موجود او لا
            if (res.getReservationID() == reservationID) {
                return &res;
            }
        }
        return nullptr;
    }

    // Check Table Availability
    bool checkTableAvailability(int tableID, string date, string time) const {
        for (const auto& res : reservations) {
            bool isActive = (res.getStatus() == ReservationStatus::Pending || res.getStatus() == ReservationStatus::Confirmed);
            if (isActive && res.getTableID() == tableID && res.getDate() == date && res.getTime() == time) {  //بيشوف لو الtable دي محجوزة في نفس التاريخ والوقت او لا 
                return false; // Table is not available
            }
        }
        return true; // Table is available
    }
};




// Table class
class Table {
public:
    // Constructor
    Table(int tableID, int capacity, string location, TableStatus status) {
        setTableID(tableID);
        setCapacity(capacity);
        setlocation(location);
        setStatus(status);
    }
    // Default constructor
    Table() {
        setTableID(0);
        setCapacity(1);
        setlocation("Undefined");
        setStatus(TableStatus::Available);
    }
    // Setters
    void setTableID(int tableID) {
        if (tableID >= 0) {
            this->tableID = tableID;
        }
        else {
            cout << "Error: Table ID must be a positive number. \n";
        }
    }

    void setCapacity(int capacity) {
        if (capacity > 0) {
            this->capacity = capacity;
        }
        else {
            cout << "Error: Capacity must be greater than Zero. \n";
        }
    }

    void setlocation(string location) {
        if (location.length() >= 3) {
            this->location = location;
        }
        else {
            cout << "Error: Location must be longer than 3 charcaters. \n";
        }
    }

    void setStatus(TableStatus status) {
        this->status = status;
    }


    // Getters
    int getTableID() const { return tableID; }

    int getCapacity() const { return capacity; }

    string getLocation() const { return location; }

    string getStatusString() const {
        switch (status) {
        case TableStatus::Available:
            return "Available";
        case TableStatus::Reserved:
            return "Reserved";
        case TableStatus::Occupied:
            return "Occupied";
        case TableStatus::OutOfService:
            return "Out of service";
        default:
            return "Unknown";
        }
    }

    TableStatus getStatus() const {
        return status;
    }

private:
    int tableID;
    int capacity;
    string location;
    TableStatus status;
};
// Table Manager class
class TableManager {
public:
    // Constructor

    // Functions
    bool addTable(Table t) {

        for (const Table& item : tables) {
            if (item.getTableID() == t.getTableID()) {
                return false;
            }
        }
        tables.push_back(t);
        cout << "Table added successfully.\n";
        return true;
    }

    void displayAvailableTables() {
        if (tables.empty()) {
            cout << "Error: There are no tables added yet. \n";
        }
        else {
            cout << string(70, '_') << endl;
            cout << string(27, ' ') + "available tables" + string(27, ' ') << endl;
            cout << string(70, '_') << endl;
            cout << left << setw(10) << "ID"
                << setw(14) << "Capacity"
                << setw(26) << "Location"
                << setw(20) << "Status" << endl;
            for (const Table& item : tables) {
                if (item.getStatus() == TableStatus::Available) {
                    cout << left << setw(10) << item.getTableID()
                        << setw(14) << item.getCapacity()
                        << setw(26) << item.getLocation()
                        << setw(20) << item.getStatusString() << endl;
                }
            }
        }

    }

    Table* searchTable(int tableID) {
        for (Table& item : tables) {
            if (item.getTableID() == tableID) {
                return &item;
            }
        }
        return nullptr;
    }

    bool updateTableStatus(int tableID, TableStatus newStatus) {
        for (Table& item : tables) {
            if (item.getTableID() == tableID) {
                item.setStatus(newStatus);
                return true;
            }
        }
        return false;
    }

    bool isTableAvailable(int tableID) {
        for (const Table& item : tables) {
            if (item.getTableID() == tableID) {
                if (item.getStatus() == TableStatus::Available)
                    return true;
            }
        }
        return false;
    }

    // ========================================================================
    // ADDED — required by the specification (and the original project spec,
    // section 2.2 "Assign a table to a customer/order"), was missing.
    // Marks the table Occupied only if it was actually Available; rejects
    // assigning a table that's Reserved / Occupied / Out of Service already.
    // ========================================================================
    bool assignTable(int tableID) {
        for (Table& item : tables) {
            if (item.getTableID() == tableID) {
                if (item.getStatus() != TableStatus::Available) {
                    cout << "Error: Table " << tableID << " is not available ("
                        << item.getStatusString() << ").\n";
                    return false;
                }
                item.setStatus(TableStatus::Occupied);
                cout << "Table " << tableID << " assigned successfully.\n";
                return true;
            }
        }
        cout << "Error: Table " << tableID << " not found.\n";
        return false;
    }

private:
    vector <Table> tables;
};

// MenuItem class
class MenuItem {
public:
    // Constructor
    MenuItem(int itemID, string name, double price, MenuCategory category, string description, bool isAvailable) {
        setItemID(itemID);
        setName(name);
        setPrice(price);
        setCategory(category);
        setDescription(description);
        setIsAvailable(isAvailable);
    }
    // Setters
    void setItemID(int itemID) {
        if (itemID >= 0) {
            this->itemID = itemID;
        }
        else {
            cout << "Error: Item ID must be a positive number. \n";
        }
    }

    void setName(string name) {
        if (name.length() >= 3) {
            this->name = name;
        }
        else {
            cout << "Error: Name must be longer than 3 charcaters. \n";
        }
    }

    void setPrice(double price) {
        if (price <= 0) {
            cout << "Error: Price must be more than Zero. \n";
        }
        else {
            this->price = price;
        }
    }

    void setCategory(MenuCategory category) {
        this->category = category;
    }

    void setDescription(string description) {
        if (description.length() >= 3) {
            this->description = description;
        }
        else {
            cout << "Error: Description must be longer than 3 charcaters. \n";
        }
    }

    void setIsAvailable(bool isavailable) {
        this->isavailable = isavailable;
    }

    // Getters
    int getItemID() const { return itemID; }

    string getName() const { return name; }

    double getPrice() const { return price; }

    MenuCategory getCategory() const { return category; }

    string getCategoryString() const {
        switch (category) {
        case MenuCategory::Appetizer:
            return "Appetizers";
        case MenuCategory::Dessert:
            return "Desserts";
        case MenuCategory::Drink:
            return "Drinks";
        case MenuCategory::MainCourse:
            return "Main Course";
        default:
            return "Unknown";
        }
    }

    string getDescription() const { return description; }

    bool getIsAvailable() const { return isavailable; }

    string getIsAvailableString() const {
        if (isavailable) {
            return "Yes";
        }
        else {
            return "No";
        }
    }

private:
    int itemID;
    string name;
    double price;
    MenuCategory category;
    string description;
    bool isavailable;
};

class MenuManager {
public:
    // Functions
    bool addItem(MenuItem item) {
        if (item.getPrice() <= 0) {
            cout << "Error: Price must be greater than zero to add an item.\n";
            return false;
        }

        for (const MenuItem& it : items) {
            if (it.getItemID() == item.getItemID()) {
                return false;
            }
        }
        items.push_back(item);
        cout << "Item added successfully.\n";
        return true;
    }

    bool removeItem(int itemID) {
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].getItemID() == itemID) {

                items.erase(items.begin() + i);
                cout << "Item removed successfully.\n";
                return true;
            }
        }
        return false;
    }

    bool updateItem(int itemID, string name, double price, MenuCategory category, string description, bool isavailable) {
        for (MenuItem& item : items) {
            if (item.getItemID() == itemID) {

                item.setName(name);
                item.setPrice(price);
                item.setCategory(category);
                item.setDescription(description);
                item.setIsAvailable(isavailable);

                cout << "Item updated successfully.\n";
                return true;
            }
        }
        cout << "Error: Item ID not found.\n";
        return false;
    }

    MenuItem* searchItem(int itemID) {
        for (MenuItem& item : items) {
            if (item.getItemID() == itemID) {
                return &item;
            }
        }
        return nullptr;
    }

    void displayMenu() {
        if (items.empty()) {
            cout << "Error: There are no items added yet. \n";
        }
        else {
            cout << string(90, '_') << endl;
            cout << string(40, ' ') + "Menu" + string(40, ' ') << endl;
            cout << string(90, '_') << endl;
            cout << left << setw(8) << "Item Id"
                << setw(27) << "Name"
                << setw(10) << "Price"
                << setw(35) << "Description"
                << setw(10) << "Avilability" << endl;
            cout << string(39, ' ') + "Appetizers" + string(39, ' ') << endl;
            for (const MenuItem& item : items) {
                if (item.getCategory() == MenuCategory::Appetizer) {
                    printItemRow(item);
                }
            }
            cout << string(39, ' ') + "Main Course" + string(39, ' ') << endl;
            for (const MenuItem& item : items) {
                if (item.getCategory() == MenuCategory::MainCourse) {
                    printItemRow(item);

                }
            }
            cout << string(39, ' ') + "Desserts" + string(39, ' ') << endl;
            for (const MenuItem& item : items) {
                if (item.getCategory() == MenuCategory::Dessert) {
                    printItemRow(item);
                }
            }
            cout << string(39, ' ') + "Drinks" + string(39, ' ') << endl;
            for (const MenuItem& item : items) {
                if (item.getCategory() == MenuCategory::Drink) {
                    printItemRow(item);
                }
            }
        }
    }

    bool changeAvailability(int itemID, bool available) {
        for (MenuItem& item : items) {
            if (itemID == item.getItemID()) {
                item.setIsAvailable(available);
                return true;
            }
        }
        return false;
    }


private:
    vector<MenuItem> items;
    // Helper print row

    void printItemRow(const MenuItem& item) const {
        cout << left << setw(8) << item.getItemID()
            << setw(27) << item.getName()
            << setw(10) << item.getPrice()
            << setw(35) << item.getDescription()
            << setw(10) << item.getIsAvailableString() << endl;
    }
};



// ============================================================================
// OrderItem struct
// ============================================================================
struct OrderItem
{
    int itemID;
    string itemName;
    int quantity;
    double price;

    OrderItem() : itemID(0), quantity(0), price(0.0) {}
    OrderItem(int id, string name, int qty, double p)
        : itemID(id), itemName(name), quantity(qty), price(p) {
    }
};

// ============================================================================
// Order class
// ============================================================================
class Order
{
private:
    int orderID;
    int customerID;
    int tableID;
    vector<OrderItem> items;
    string orderDateTime;
    OrderType orderType;
    OrderStatus status;
    double subtotal;
    double taxAmount;
    double serviceCharge;
    double totalPrice;

public:
    // constructors
    Order() : orderID(0), customerID(0), tableID(0),
        orderType(OrderType::DineIn), status(OrderStatus::New),
        subtotal(0.0), taxAmount(0.0), serviceCharge(0.0), totalPrice(0.0) {
    }

    Order(int oid, int cid, int tid, OrderType type, string dt)
        : orderID(oid), customerID(cid), tableID(tid),
        orderType(type), status(OrderStatus::New),
        subtotal(0.0), taxAmount(0.0), serviceCharge(0.0), totalPrice(0.0)
    {
        orderDateTime = dt;
    }

    // getters
    int getOrderID() const { return orderID; }
    int getCustomerID() const { return customerID; }
    int getTableID() const { return tableID; }
    string getOrderDateTime() const { return orderDateTime; }
    OrderType getOrderType() const { return orderType; }
    OrderStatus getStatus() const { return status; }
    double getSubtotal() const { return subtotal; }
    double getTaxAmount() const { return taxAmount; }
    double getServiceCharge() const { return serviceCharge; }
    double getTotalPrice() const { return totalPrice; }
    vector<OrderItem>& getItems() { return items; }
    const vector<OrderItem>& getItems() const { return items; }

    // setters
    void setOrderID(int id) { orderID = id; }
    void setCustomerID(int id) { customerID = id; }
    void setTableID(int id) { tableID = id; }
    void setOrderDateTime(string dt) { orderDateTime = dt; }
    void setOrderType(OrderType t) { orderType = t; }
    void setStatus(OrderStatus s) { status = s; }
    void setSubtotal(double val) { subtotal = val; }
    void setTaxAmount(double val) { taxAmount = val; }
    void setServiceCharge(double val) { serviceCharge = val; }
    void setTotalPrice(double val) { totalPrice = val; }

    // add item to order
    void addItem(const OrderItem& it)
    {
        // if same item exists, just increase quantity
        for (auto& existing : items)
        {
            if (existing.itemID == it.itemID)
            {
                existing.quantity += it.quantity;
                return;
            }
        }
        items.push_back(it);
    }

    // remove item by itemID
    bool removeItem(int itemID)
    {
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if (it->itemID == itemID)
            {
                items.erase(it);
                return true;
            }
        }
        return false;
    }

    // change quantity of an item
    bool changeQuantity(int itemID, int newQty)
    {
        if (newQty <= 0)
            return false;
        for (auto& it : items)
        {
            if (it.itemID == itemID)
            {
                it.quantity = newQty;
                return true;
            }
        }
        return false;
    }

    // recalculate financials
    void recalculate()
    {
        subtotal = 0.0;
        for (const auto& it : items)
        {
            subtotal += it.price * it.quantity;
        }
        taxAmount = subtotal * 0.14;     // 14% tax
        serviceCharge = subtotal * 0.12; // 12% service
        totalPrice = subtotal + taxAmount + serviceCharge;
    }

    // display order header info
    void displayInfo() const
    {
        cout << "\n--- Order #" << orderID << " ---\n";
        cout << "Customer ID : " << customerID << "\n";
        if (tableID != 0)
            cout << "Table ID    : " << tableID << "\n";
        cout << "Type        : " << typeToString(orderType) << "\n";
        cout << "Status      : " << statusToString(status) << "\n";
        cout << "Date/Time   : " << orderDateTime << "\n";
    }

    // display items
    void displayItems() const
    {
        if (items.empty())
        {
            cout << "  (no items)\n";
            return;
        }
        cout << "\n  Items:\n";
        cout << "  " << left << setw(6) << "ID"
            << setw(20) << "Name"
            << setw(10) << "Qty"
            << setw(10) << "Unit"
            << setw(10) << "Total" << "\n";
        cout << "  " << string(56, '-') << "\n";
        for (const auto& it : items)
        {
            cout << "  " << left << setw(6) << it.itemID
                << setw(20) << it.itemName
                << setw(10) << it.quantity
                << setw(10) << fixed << setprecision(2) << it.price
                << setw(10) << it.price * it.quantity << "\n";
        }
    }

    // display financial summary
    void displayFinancials() const
    {
        cout << "\n  Financials:\n";
        cout << "  Subtotal      : " << fixed << setprecision(2) << subtotal << "\n";
        cout << "  Tax (14%)     : " << taxAmount << "\n";
        cout << "  Service (12%) : " << serviceCharge << "\n";
        cout << "  TOTAL         : " << totalPrice << "\n";
    }
};

// ============================================================================
// OrderManager class
// ============================================================================
class OrderManager
{
private:
    vector<Order> orders;
    int nextOrderID;

    // check if status transition is valid
    bool canTransition(OrderStatus from, OrderStatus to)
    {
        if (from == to)
            return true;

        // allowed forward flow
        if (from == OrderStatus::New && to == OrderStatus::Preparing)
            return true;
        if (from == OrderStatus::New && to == OrderStatus::Cancelled)
            return true;

        if (from == OrderStatus::Preparing && to == OrderStatus::Ready)
            return true;
        if (from == OrderStatus::Preparing && to == OrderStatus::Cancelled)
            return true;

        if (from == OrderStatus::Ready && to == OrderStatus::Served)
            return true;
        if (from == OrderStatus::Ready && to == OrderStatus::Cancelled)
            return true;

        if (from == OrderStatus::Served && to == OrderStatus::Completed)
            return true;

        // no other transitions allowed
        return false;
    }

public:
    OrderManager() : nextOrderID(1000) {}

    // ------------------------------------------------------------------------
    // create a new order, returns the new orderID or -1 on failure
    // ------------------------------------------------------------------------
    int createOrder(int customerID, int tableID, OrderType type)
    {
        if (customerID <= 0)
        {
            cout << "Error: invalid customer ID.\n";
            return -1;
        }

        // get current date/time as string
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buf[64];
        snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d",
            1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
            ltm->tm_hour, ltm->tm_min);

        Order o(nextOrderID, customerID, tableID, type, string(buf));
        orders.push_back(o);
        nextOrderID++;
        return o.getOrderID();
    }

    // ------------------------------------------------------------------------
    // add item to an existing order
    // ------------------------------------------------------------------------
    bool addItem(int orderID, OrderItem item)
    {
        if (item.quantity <= 0)
        {
            cout << "Error: quantity must be greater than zero.\n";
            return false;
        }
        if (item.price < 0)
        {
            cout << "Error: price cannot be negative.\n";
            return false;
        }

        Order* o = searchOrder(orderID);
        if (!o)
        {
            cout << "Error: order not found.\n";
            return false;
        }

        if (o->getStatus() != OrderStatus::New)
        {
            cout << "Error: cannot modify items after order is no longer New.\n";
            return false;
        }

        o->addItem(item);
        o->recalculate();
        return true;
    }

    // ------------------------------------------------------------------------
    // remove item from order
    // ------------------------------------------------------------------------
    bool removeItem(int orderID, int itemID)
    {
        Order* o = searchOrder(orderID);
        if (!o)
        {
            cout << "Error: order not found.\n";
            return false;
        }
        if (o->getStatus() != OrderStatus::New)
        {
            cout << "Error: cannot modify items after order is no longer New.\n";
            return false;
        }

        bool ok = o->removeItem(itemID);
        if (ok)
            o->recalculate();
        return ok;
    }

    // ------------------------------------------------------------------------
    // change quantity of an item
    // ------------------------------------------------------------------------
    bool changeQuantity(int orderID, int itemID, int newQty)
    {
        if (newQty <= 0)
        {
            cout << "Error: new quantity must be greater than zero.\n";
            return false;
        }

        Order* o = searchOrder(orderID);
        if (!o)
        {
            cout << "Error: order not found.\n";
            return false;
        }
        if (o->getStatus() != OrderStatus::New)
        {
            cout << "Error: cannot modify items after order is no longer New.\n";
            return false;
        }

        bool ok = o->changeQuantity(itemID, newQty);
        if (ok)
            o->recalculate();
        return ok;
    }

    // ------------------------------------------------------------------------
    // calculate subtotal
    // ------------------------------------------------------------------------
    double calculateSubtotal(int orderID)
    {
        Order* o = searchOrder(orderID);
        if (!o)
            return -1.0;
        o->recalculate();
        return o->getSubtotal();
    }

    // ------------------------------------------------------------------------
    // calculate tax (14%)
    // ------------------------------------------------------------------------
    double calculateTax(int orderID)
    {
        Order* o = searchOrder(orderID);
        if (!o)
            return -1.0;
        o->recalculate();
        return o->getTaxAmount();
    }

    // ------------------------------------------------------------------------
    // calculate total (subtotal + tax + service)
    // ------------------------------------------------------------------------
    double calculateTotal(int orderID)
    {
        Order* o = searchOrder(orderID);
        if (!o)
            return -1.0;
        o->recalculate();
        return o->getTotalPrice();
    }

    // ------------------------------------------------------------------------
    // cancel order — only from New, Preparing, or Ready
    // ------------------------------------------------------------------------
    bool cancelOrder(int orderID)
    {
        Order* o = searchOrder(orderID);
        if (!o)
        {
            cout << "Error: order not found.\n";
            return false;
        }

        OrderStatus s = o->getStatus();
        if (s == OrderStatus::Served || s == OrderStatus::Completed || s == OrderStatus::Cancelled)
        {
            cout << "Error: cannot cancel order in status '" << statusToString(s) << "'.\n";
            return false;
        }

        o->setStatus(OrderStatus::Cancelled);
        return true;
    }

    // ------------------------------------------------------------------------
    // update order status with validation
    // ------------------------------------------------------------------------
    bool updateOrderStatus(int orderID, OrderStatus newStatus)
    {
        Order* o = searchOrder(orderID);
        if (!o)
        {
            cout << "Error: order not found.\n";
            return false;
        }

        OrderStatus current = o->getStatus();
        if (!canTransition(current, newStatus))
        {
            cout << "Error: invalid status transition from '"
                << statusToString(current) << "' to '"
                << statusToString(newStatus) << "'.\n";
            return false;
        }

        o->setStatus(newStatus);
        return true;
    }

    // ------------------------------------------------------------------------
    // display full order details
    // ------------------------------------------------------------------------
    void displayOrderDetails(int orderID)
    {
        Order* o = searchOrder(orderID);
        if (!o)
        {
            cout << "Order #" << orderID << " not found.\n";
            return;
        }
        o->displayInfo();
        o->displayItems();
        o->displayFinancials();
        cout << "\n";
    }

    // ------------------------------------------------------------------------
    // search order by ID (returns pointer or nullptr)
    // ------------------------------------------------------------------------
    Order* searchOrder(int orderID)
    {
        for (auto& o : orders)
        {
            if (o.getOrderID() == orderID)
                return &o;
        }
        return nullptr;
    }

    // ------------------------------------------------------------------------
    // display all orders (brief list)
    // ------------------------------------------------------------------------
    void displayAllOrders()
    {
        if (orders.empty())
        {
            cout << "No orders yet.\n";
            return;
        }
        cout << "\n=== All Orders ===\n";
        cout << left << setw(10) << "Order#"
            << setw(12) << "CustID"
            << setw(12) << "Type"
            << setw(14) << "Status"
            << setw(12) << "Total" << "\n";
        cout << string(60, '-') << "\n";
        for (const auto& o : orders)
        {
            cout << left << setw(10) << o.getOrderID()
                << setw(12) << o.getCustomerID()
                << setw(12) << typeToString(o.getOrderType())
                << setw(14) << statusToString(o.getStatus())
                << setw(12) << fixed << setprecision(2) << o.getTotalPrice() << "\n";
        }
        cout << "\n";
    }

    // ------------------------------------------------------------------------
    // get reference to all orders (for integration with Kitchen/Reports)
    // ------------------------------------------------------------------------
    vector<Order>& getOrders() { return orders; }
};





//Employee class
class Employee
{
protected:
    int employeeID;
    string name;
    string phoneNumber;
    double salary;
    bool isActive;
    EmployeeRole role;

public:
    Employee(int employeeID, string name, string phoneNumber, double salary, bool isActive, EmployeeRole role)
    {
        this->employeeID = employeeID;
        this->name = name;
        this->phoneNumber = phoneNumber;
        this->salary = salary;
        this->isActive = isActive;
        this->role = role;
    }
    int getEmployeeID() { return employeeID; }
    string getName() { return name; }
    bool getIsActive() { return isActive; }
    EmployeeRole getRole() { return role; }
    void setName(string name) { this->name = name; }
    void setPhoneNumber(string phoneNumber) { this->phoneNumber = phoneNumber; }
    void setSalary(double salary) { this->salary = salary; }
    void setIsActive(bool isActive) { this->isActive = isActive; }
    virtual void displayInfo() = 0;
    virtual ~Employee() {}
};


//chef
class Chef : public Employee
{
public:
    Chef(int employeeID, string name, string phoneNumber, double salary, bool isActive)
        : Employee(employeeID, name, phoneNumber, salary, isActive, EmployeeRole::Chef) {
    }
    void displayInfo() override
    {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Salary: " << salary << endl;
    }
};


//waiter
class Waiter : public Employee
{
public:
    Waiter(int employeeID, string name, string phoneNumber, double salary, bool isActive)
        : Employee(employeeID, name, phoneNumber, salary, isActive, EmployeeRole::Waiter) {
    }
    void displayInfo() override
    {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Salary: " << salary << endl;
    }
};


//manager
class Manager : public Employee
{
public:
    Manager(int employeeID, string name, string phoneNumber, double salary, bool isActive)
        : Employee(employeeID, name, phoneNumber, salary, isActive, EmployeeRole::Manager) {
    }
    void displayInfo() override
    {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Salary: " << salary << endl;
    }
};


//cashier
class Cashier : public Employee
{
public:
    Cashier(int employeeID, string name, string phoneNumber, double salary, bool isActive)
        : Employee(employeeID, name, phoneNumber, salary, isActive, EmployeeRole::Cashier) {
    }
    void displayInfo() override
    {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Salary: " << salary << endl;
    }
};

//delivery driver
class DeliveryDriver : public Employee
{
public:
    DeliveryDriver(int employeeID, string name, string phoneNumber, double salary, bool isActive)
        : Employee(employeeID, name, phoneNumber, salary, isActive, EmployeeRole::DeliveryDriver) {
    }
    void displayInfo() override
    {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Salary: " << salary << endl;
    }
};


//employee manager
class EmployeeManager
{
private:
    vector<Employee*> employees;

public:
    ~EmployeeManager()
    {
        for (Employee* employee : employees)
        {
            delete employee;
        }
    }

    void displayEmployees()
    {
        bool found = false;
        for (Employee* employee : employees)
        {
            employee->displayInfo();
            cout << "--------------------" << endl;
            found = true;
        }
        if (!found)
        {
            cout << "No employees found." << endl;
        }
    }

    void changeAvailability()
    {
        int id;
        int status;
        cout << "Enter Employee ID: ";
        cin >> id;
        for (Employee* employee : employees)
        {
            if (employee->getEmployeeID() == id)
            {
                cout << "Enter new availability (1 = Available, 0 = Not Available): ";
                cin >> status;
                if (status != 0 && status != 1)
                {
                    cout << "Invalid availability." << endl;
                    return;
                }
                employee->setIsActive(status);
                cout << "Availability updated successfully." << endl;
                return;
            }
        }
        cout << "Employee not found." << endl;
    }

    void searchEmployee()
    {
        int id;
        cout << "Enter Employee ID: ";
        cin >> id;
        for (Employee* employee : employees)
        {
            if (employee->getEmployeeID() == id)
            {
                employee->displayInfo();
                return;
            }
        }
        cout << "Employee not found." << endl;
    }

    bool isEmployeeIDUsed(int id)
    {
        for (Employee* employee : employees)
        {
            if (employee->getEmployeeID() == id)
            {
                return true;
            }
        }
        return false;
    }

    void updateEmployee()
    {
        int id;
        cout << "Enter Employee ID: ";
        cin >> id;
        for (Employee* employee : employees)
        {
            if (employee->getEmployeeID() == id)
            {
                int choice;
                cout << "1. Update Name" << endl;
                cout << "2. Update Phone Number" << endl;
                cout << "3. Update Salary" << endl;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    string name;
                    cout << "Enter new name: ";
                    cin >> name;
                    employee->setName(name);
                    break;
                }
                case 2:
                {
                    string phoneNumber;
                    cout << "Enter new phone number: ";
                    cin >> phoneNumber;
                    employee->setPhoneNumber(phoneNumber);
                    break;
                }
                case 3:
                {
                    double salary;
                    cout << "Enter new salary: ";
                    cin >> salary;
                    employee->setSalary(salary);
                    break;
                }
                default:
                    cout << "Invalid choice." << endl;
                }
                return;
            }
        }
        cout << "Employee not found." << endl;
    }

    void addEmployee()
    {
        int choice;
        cout << "1. Manager" << endl;
        cout << "2. Chef" << endl;
        cout << "3. Waiter" << endl;
        cout << "4. Cashier" << endl;
        cout << "5. Delivery Driver" << endl;
        cin >> choice;
        if (choice < 1 || choice > 5)
        {
            cout << "Invalid choice." << endl;
            return;
        }
        int employeeID;
        string name;
        string phoneNumber;
        double salary;
        bool isActive;
        cout << "Enter Employee ID: ";
        cin >> employeeID;
        if (isEmployeeIDUsed(employeeID))
        {
            cout << "Employee ID already exists." << endl;
            return;
        }
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Phone Number: ";
        cin >> phoneNumber;
        cout << "Enter Salary: ";
        cin >> salary;
        cout << "Is Active? (1 = Yes, 0 = No): ";
        cin >> isActive;
        switch (choice)
        {
        case 1:
            employees.push_back(new Manager(employeeID, name, phoneNumber, salary, isActive));
            break;
        case 2:
            employees.push_back(new Chef(employeeID, name, phoneNumber, salary, isActive));
            break;
        case 3:
            employees.push_back(new Waiter(employeeID, name, phoneNumber, salary, isActive));
            break;
        case 4:
            employees.push_back(new Cashier(employeeID, name, phoneNumber, salary, isActive));
            break;
        case 5:
            employees.push_back(new DeliveryDriver(employeeID, name, phoneNumber, salary, isActive));
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }

    // ========================================================================
    // ADDED — required by the specification, was missing:
    // ========================================================================

    // display all employees of a given role only
    void displayByRole(EmployeeRole role)
    {
        bool found = false;
        for (Employee* employee : employees)
        {
            if (employee->getRole() == role)
            {
                employee->displayInfo();
                cout << "--------------------" << endl;
                found = true;
            }
        }
        if (!found)
        {
            cout << "No employees found for this role." << endl;
        }
    }

    // gives other modules (Reports, Delivery) read access to the employee list
    // without going through cin — needed so Delivery can check a driver is
    // active before assigning them, and so Reports can loop over employees.
    vector<Employee*>& getEmployees() { return employees; }

    // non-interactive lookup by ID — returns nullptr if not found.
    // Same purpose as searchEmployee(), but usable from code (not just from
    // the console), which searchEmployee() couldn't do since it does cin itself.
    Employee* findEmployeeByID(int id)
    {
        for (Employee* employee : employees)
        {
            if (employee->getEmployeeID() == id)
            {
                return employee;
            }
        }
        return nullptr;
    }
};


//kitchen class
class Kitchen
{
private:
    OrderManager& orderManager;

public:
    Kitchen(OrderManager& orderManager) : orderManager(orderManager) {}

    void viewPendingOrders()
    {
        vector<Order>& orders = orderManager.getOrders();
        bool found = false;
        for (Order& order : orders)
        {
            if (order.getStatus() == OrderStatus::New)
            {
                found = true;
                cout << "Order ID: " << order.getOrderID() << endl;
                cout << "Status: New" << endl;
                cout << "--------------------" << endl;
            }
        }
        if (!found)
        {
            cout << "No pending orders." << endl;
        }
    }

    void startPreparing()
    {
        int orderID;
        cout << "Enter Order ID: ";
        cin >> orderID;
        if (orderManager.updateOrderStatus(orderID, OrderStatus::Preparing))
        {
            cout << "Order is now being prepared." << endl;
        }
    }

    void markReady()
    {
        int orderID;
        cout << "Enter Order ID: ";
        cin >> orderID;
        if (orderManager.updateOrderStatus(orderID, OrderStatus::Ready))
        {
            cout << "Order is ready." << endl;
        }
    }

    // ========================================================================
    // ADDED — required by the specification (and the original project spec,
    // section 5.2), was missing:
    // ========================================================================

    // display orders that are currently being prepared / ready to serve
    void displayPreparedOrders()
    {
        vector<Order>& orders = orderManager.getOrders();
        bool found = false;
        for (Order& order : orders)
        {
            if (order.getStatus() == OrderStatus::Preparing || order.getStatus() == OrderStatus::Ready)
            {
                found = true;
                cout << "Order ID: " << order.getOrderID() << endl;
                cout << "Status: " << (order.getStatus() == OrderStatus::Preparing ? "Preparing" : "Ready") << endl;
                cout << "--------------------" << endl;
            }
        }
        if (!found)
        {
            cout << "No orders currently being prepared." << endl;
        }
    }
};

// ============================================================================
// Payment class
// ============================================================================
class Payment {
private:
    int paymentID;
    int orderID;
    double amount;
    PaymentMethod method;
    string paymentDateTime;
    PaymentStatus status;

public:
    Payment(int pID = 0, int oID = 0, double amt = 0.0, PaymentMethod m = PaymentMethod::Cash,
        string dt = "", PaymentStatus s = PaymentStatus::Completed)
        : paymentID(pID), orderID(oID), amount(amt), method(m), paymentDateTime(dt), status(s) {
    }

    // Getters
    int getPaymentID() const { return paymentID; }
    int getOrderID() const { return orderID; }
    double getAmount() const { return amount; }
    PaymentMethod getMethod() const { return method; }
    string getPaymentDateTime() const { return paymentDateTime; }
    PaymentStatus getStatus() const { return status; }

    // Setter (status is the only thing that legitimately changes after creation)
    void setStatus(PaymentStatus s) { status = s; }

    // Display
    void displayInfo() const {
        cout << "\n--- Payment #" << paymentID << " ---\n";
        cout << "Order ID   : " << orderID << "\n";
        cout << "Amount     : " << fixed << setprecision(2) << amount << "\n";
        cout << "Method     : " << paymentMethodToString(method) << "\n";
        cout << "Date/Time  : " << paymentDateTime << "\n";
        cout << "Status     : " << paymentStatusToString(status) << "\n";
    }
};

// ============================================================================
// PaymentManager class
// ============================================================================
class PaymentManager {
private:
    vector<Payment> payments;
    int nextPaymentID;

public:
    PaymentManager() : nextPaymentID(3000) {}

    // ------------------------------------------------------------------------
    // process a payment for an order, returns new paymentID or -1 on failure
    // ------------------------------------------------------------------------
    int processPayment(int orderID, double amount, PaymentMethod method) {
        if (orderID <= 0) {
            cout << "Error: invalid order ID.\n";
            return -1;
        }
        if (amount <= 0) {
            cout << "Error: amount must be greater than zero.\n";
            return -1;
        }

        Payment p(nextPaymentID, orderID, amount, method, getCurrentDateTime(), PaymentStatus::Completed);
        payments.push_back(p);
        cout << "Payment recorded successfully! Payment ID: " << nextPaymentID << "\n";
        nextPaymentID++;
        return p.getPaymentID();
    }

    // ------------------------------------------------------------------------
    // display details of one payment
    // ------------------------------------------------------------------------
    void displayPaymentDetails(int paymentID) {
        Payment* p = searchPayment(paymentID);
        if (!p) {
            cout << "Error: payment not found.\n";
            return;
        }
        p->displayInfo();
    }

    // ------------------------------------------------------------------------
    // refund a payment
    // ------------------------------------------------------------------------
    bool refundPayment(int paymentID) {
        Payment* p = searchPayment(paymentID);
        if (!p) {
            cout << "Error: payment not found.\n";
            return false;
        }
        if (p->getStatus() == PaymentStatus::Refunded) {
            cout << "Error: payment is already refunded.\n";
            return false;
        }
        p->setStatus(PaymentStatus::Refunded);
        cout << "Payment " << paymentID << " refunded successfully.\n";
        return true;
    }

    // ------------------------------------------------------------------------
    // generate and print a simple receipt
    // ------------------------------------------------------------------------
    void generateReceipt(int paymentID) {
        Payment* p = searchPayment(paymentID);
        if (!p) {
            cout << "Error: payment not found.\n";
            return;
        }
        cout << "\n========== RECEIPT ==========\n";
        cout << "Payment ID : " << p->getPaymentID() << "\n";
        cout << "Order ID   : " << p->getOrderID() << "\n";
        cout << "Amount Paid: " << fixed << setprecision(2) << p->getAmount() << "\n";
        cout << "Method     : " << paymentMethodToString(p->getMethod()) << "\n";
        cout << "Date/Time  : " << p->getPaymentDateTime() << "\n";
        cout << "==============================\n";
    }

    // ------------------------------------------------------------------------
    // view full payment history
    // ------------------------------------------------------------------------
    void viewPaymentHistory() {
        if (payments.empty()) {
            cout << "No payments recorded yet.\n";
            return;
        }
        cout << "\n=== Payment History ===\n";
        cout << left << setw(10) << "Pay#"
            << setw(10) << "Order#"
            << setw(12) << "Amount"
            << setw(16) << "Method"
            << setw(12) << "Status" << "\n";
        cout << string(60, '-') << "\n";
        for (const auto& p : payments) {
            cout << left << setw(10) << p.getPaymentID()
                << setw(10) << p.getOrderID()
                << setw(12) << fixed << setprecision(2) << p.getAmount()
                << setw(16) << paymentMethodToString(p.getMethod())
                << setw(12) << paymentStatusToString(p.getStatus()) << "\n";
        }
        cout << "\n";
    }

    // ------------------------------------------------------------------------
    // search payment by ID
    // ------------------------------------------------------------------------
    Payment* searchPayment(int paymentID) {
        for (auto& p : payments) {
            if (p.getPaymentID() == paymentID)
                return &p;
        }
        return nullptr;
    }

    // ADDED — needed by ReportManager
    vector<Payment>& getPayments() { return payments; }
};

// ============================================================================
// Delivery class
// ============================================================================
class Delivery {
private:
    int deliveryID;
    int orderID;
    int customerID;
    string deliveryAddress;
    int driverEmployeeID;
    DeliveryStatus status;
    string estimatedTime;
    string actualDeliveryTime;
    double deliveryFee;

public:
    Delivery(int dID = 0, int oID = 0, int cID = 0, string addr = "", int driverID = 0,
        DeliveryStatus s = DeliveryStatus::Assigned, string est = "", string actual = "", double fee = 0.0)
        : deliveryID(dID), orderID(oID), customerID(cID), deliveryAddress(addr),
        driverEmployeeID(driverID), status(s), estimatedTime(est), actualDeliveryTime(actual), deliveryFee(fee) {
    }

    // Getters
    int getDeliveryID() const { return deliveryID; }
    int getOrderID() const { return orderID; }
    int getCustomerID() const { return customerID; }
    string getDeliveryAddress() const { return deliveryAddress; }
    int getDriverEmployeeID() const { return driverEmployeeID; }
    DeliveryStatus getStatus() const { return status; }
    string getEstimatedTime() const { return estimatedTime; }
    string getActualDeliveryTime() const { return actualDeliveryTime; }
    double getDeliveryFee() const { return deliveryFee; }

    // Setters
    void setStatus(DeliveryStatus s) { status = s; }
    void setActualDeliveryTime(string t) { actualDeliveryTime = t; }

    // Display
    void displayInfo() const {
        cout << "\n--- Delivery #" << deliveryID << " ---\n";
        cout << "Order ID    : " << orderID << "\n";
        cout << "Customer ID : " << customerID << "\n";
        cout << "Address     : " << deliveryAddress << "\n";
        cout << "Driver ID   : " << driverEmployeeID << "\n";
        cout << "Status      : " << deliveryStatusToString(status) << "\n";
        cout << "Est. Time   : " << estimatedTime << "\n";
        cout << "Fee         : " << fixed << setprecision(2) << deliveryFee << "\n";
    }
};

// ============================================================================
// DeliveryManager class
// ============================================================================
class DeliveryManager {
private:
    vector<Delivery> deliveries;
    int nextDeliveryID;

public:
    DeliveryManager() : nextDeliveryID(5000) {}

    // ------------------------------------------------------------------------
    // assign a delivery to a driver, returns new deliveryID or -1 on failure
    // ------------------------------------------------------------------------
    int assignDelivery(int orderID, int driverEmployeeID, string address) {
        if (orderID <= 0) {
            cout << "Error: invalid order ID.\n";
            return -1;
        }
        if (driverEmployeeID <= 0) {
            cout << "Error: invalid driver employee ID.\n";
            return -1;
        }
        if (address.empty()) {
            cout << "Error: delivery address cannot be empty.\n";
            return -1;
        }

        // NOTE: checking that the driver is actually free/active happens during
        // integration, once Eman's EmployeeManager is connected.

        double fee = 25.0; // flat fee for now — can be made distance-based later
        Delivery d(nextDeliveryID, orderID, 0, address, driverEmployeeID,
            DeliveryStatus::Assigned, "35 minutes", "", fee);
        deliveries.push_back(d);
        cout << "Delivery assigned successfully! Delivery ID: " << nextDeliveryID << "\n";
        nextDeliveryID++;
        return d.getDeliveryID();
    }

    // ------------------------------------------------------------------------
    // track (display) a single delivery's status
    // ------------------------------------------------------------------------
    void trackDeliveryStatus(int deliveryID) {
        Delivery* d = searchDelivery(deliveryID);
        if (!d) {
            cout << "Error: delivery not found.\n";
            return;
        }
        d->displayInfo();
    }

    // ------------------------------------------------------------------------
    // update delivery status
    // ------------------------------------------------------------------------
    bool updateDeliveryStatus(int deliveryID, DeliveryStatus newStatus) {
        Delivery* d = searchDelivery(deliveryID);
        if (!d) {
            cout << "Error: delivery not found.\n";
            return false;
        }
        if (d->getStatus() == DeliveryStatus::Delivered || d->getStatus() == DeliveryStatus::Cancelled) {
            cout << "Error: cannot change status of a delivery that is already '"
                << deliveryStatusToString(d->getStatus()) << "'.\n";
            return false;
        }

        d->setStatus(newStatus);
        if (newStatus == DeliveryStatus::Delivered) {
            d->setActualDeliveryTime(getCurrentDateTime());
        }
        cout << "Delivery status updated to " << deliveryStatusToString(newStatus) << ".\n";
        return true;
    }

    // ------------------------------------------------------------------------
    // view all deliveries
    // ------------------------------------------------------------------------
    void viewAllDeliveries() {
        if (deliveries.empty()) {
            cout << "No deliveries yet.\n";
            return;
        }
        cout << "\n=== All Deliveries ===\n";
        cout << left << setw(10) << "Del#"
            << setw(10) << "Order#"
            << setw(10) << "Driver#"
            << setw(14) << "Status"
            << setw(10) << "Fee" << "\n";
        cout << string(56, '-') << "\n";
        for (const auto& d : deliveries) {
            cout << left << setw(10) << d.getDeliveryID()
                << setw(10) << d.getOrderID()
                << setw(10) << d.getDriverEmployeeID()
                << setw(14) << deliveryStatusToString(d.getStatus())
                << setw(10) << fixed << setprecision(2) << d.getDeliveryFee() << "\n";
        }
        cout << "\n";
    }

    // ------------------------------------------------------------------------
    // calculate delivery fee
    // ------------------------------------------------------------------------
    double calculateDeliveryFee(int deliveryID) {
        Delivery* d = searchDelivery(deliveryID);
        if (!d) return -1.0;
        return d->getDeliveryFee();
    }

    // ------------------------------------------------------------------------
    // search delivery by ID
    // ------------------------------------------------------------------------
    Delivery* searchDelivery(int deliveryID) {
        for (auto& d : deliveries) {
            if (d.getDeliveryID() == deliveryID)
                return &d;
        }
        return nullptr;
    }

    // ADDED — needed by ReportManager
    vector<Delivery>& getDeliveries() { return deliveries; }
};





// ============================================================================
// ReportManager class — Owner: Kareem
// Reads data from OrderManager, PaymentManager, EmployeeManager, DeliveryManager.
// Built last because it needs everyone else's data to already exist.
// ============================================================================
class ReportManager {
private:
    OrderManager& orderManager;
    PaymentManager& paymentManager;
    EmployeeManager& employeeManager;
    DeliveryManager& deliveryManager;

public:
    ReportManager(OrderManager& om, PaymentManager& pm, EmployeeManager& em, DeliveryManager& dm)
        : orderManager(om), paymentManager(pm), employeeManager(em), deliveryManager(dm) {
    }

    // date format expected: "YYYY-MM-DD" (matches the first 10 chars of orderDateTime)
    void generateDailySalesReport(string date) {
        vector<Order>& orders = orderManager.getOrders();
        int totalOrders = 0;
        double totalRevenue = 0.0;
        for (auto& o : orders) {
            if (o.getOrderDateTime().substr(0, 10) == date && o.getStatus() != OrderStatus::Cancelled) {
                totalOrders++;
                totalRevenue += o.getTotalPrice();
            }
        }
        cout << "\n----- Daily Sales Report (" << date << ") -----\n";
        cout << "Total Orders  : " << totalOrders << "\n";
        cout << "Total Revenue : " << fixed << setprecision(2) << totalRevenue << "\n";
    }

    // month format expected: "YYYY-MM"
    void generateMonthlyRevenueReport(string month) {
        vector<Order>& orders = orderManager.getOrders();
        int count = 0;
        double totalRevenue = 0.0;
        for (auto& o : orders) {
            if (o.getOrderDateTime().substr(0, 7) == month && o.getStatus() != OrderStatus::Cancelled) {
                count++;
                totalRevenue += o.getTotalPrice();
            }
        }
        cout << "\n----- Monthly Revenue Report (" << month << ") -----\n";
        cout << "Total Orders  : " << count << "\n";
        cout << "Total Revenue : " << fixed << setprecision(2) << totalRevenue << "\n";
    }

    void generateTopSellingItemsReport() {
        vector<Order>& orders = orderManager.getOrders();
        vector<int> ids;
        vector<string> names;
        vector<int> qtys;

        for (auto& o : orders) {
            if (o.getStatus() == OrderStatus::Cancelled) continue;
            for (auto& it : o.getItems()) {
                bool found = false;
                for (size_t i = 0; i < ids.size(); i++) {
                    if (ids[i] == it.itemID) { qtys[i] += it.quantity; found = true; break; }
                }
                if (!found) { ids.push_back(it.itemID); names.push_back(it.itemName); qtys.push_back(it.quantity); }
            }
        }

        // simple selection sort, descending by quantity sold
        for (size_t i = 0; i < qtys.size(); i++) {
            size_t maxIdx = i;
            for (size_t j = i + 1; j < qtys.size(); j++)
                if (qtys[j] > qtys[maxIdx]) maxIdx = j;
            swap(qtys[i], qtys[maxIdx]);
            swap(ids[i], ids[maxIdx]);
            swap(names[i], names[maxIdx]);
        }

        cout << "\n----- Top Selling Items -----\n";
        if (qtys.empty()) {
            cout << "No items sold yet.\n";
            return;
        }
        for (size_t i = 0; i < qtys.size(); i++) {
            cout << left << setw(4) << (i + 1) << setw(24) << names[i] << "Qty Sold: " << qtys[i] << "\n";
        }
    }

    // NOTE: the current data model only links a delivery driver to an order
    // (via driverEmployeeID), so this report can only measure completed
    // deliveries per employee — not waiter/cashier order handling, since
    // Order does not store which staff member served it.
    void generateEmployeePerformanceReport() {
        vector<Employee*>& employees = employeeManager.getEmployees();
        vector<Delivery>& deliveries = deliveryManager.getDeliveries();

        cout << "\n----- Employee Performance Report -----\n";
        if (employees.empty()) {
            cout << "No employees yet.\n";
            return;
        }
        for (auto* e : employees) {
            int completedDeliveries = 0;
            for (auto& d : deliveries) {
                if (d.getDriverEmployeeID() == e->getEmployeeID() && d.getStatus() == DeliveryStatus::Delivered)
                    completedDeliveries++;
            }
            cout << "Employee ID: " << e->getEmployeeID()
                << " | Name: " << e->getName()
                << " | Completed Deliveries: " << completedDeliveries << "\n";
        }
    }

    void generateDeliveryReport() {
        vector<Delivery>& deliveries = deliveryManager.getDeliveries();
        cout << "\n----- Delivery Report -----\n";
        if (deliveries.empty()) {
            cout << "No deliveries yet.\n";
            return;
        }
        int assigned = 0, onWay = 0, delivered = 0, cancelled = 0;
        for (auto& d : deliveries) {
            switch (d.getStatus()) {
            case DeliveryStatus::Assigned:   assigned++;  break;
            case DeliveryStatus::OnTheWay:   onWay++;     break;
            case DeliveryStatus::Delivered:  delivered++; break;
            case DeliveryStatus::Cancelled:  cancelled++; break;
            }
        }
        cout << "Total Deliveries : " << deliveries.size() << "\n";
        cout << "Assigned         : " << assigned << "\n";
        cout << "On The Way       : " << onWay << "\n";
        cout << "Delivered        : " << delivered << "\n";
        cout << "Cancelled        : " << cancelled << "\n";
    }
};

// ============================================================================
// RestaurantSystem class — Owner: Kareem
// Owns one instance of every manager and runs the main menu.
// This is the only class allowed to make different managers work together.
// ============================================================================
class RestaurantSystem {
private:
    CustomerManager customerManager;
    TableManager tableManager;
    MenuManager menuManager;
    ReservationManager reservationManager;
    OrderManager orderManager;
    EmployeeManager employeeManager;
    Kitchen kitchen;
    PaymentManager paymentManager;
    DeliveryManager deliveryManager;
    ReportManager reportManager;

public:
    RestaurantSystem()
        : kitchen(orderManager),
        reportManager(orderManager, paymentManager, employeeManager, deliveryManager) {
    }

    void run() {
        int choice;
        do {
            cout << "\n========== RESTAURANT MANAGEMENT SYSTEM ==========\n";
            cout << "1. Customer Management\n";
            cout << "2. Table Management\n";
            cout << "3. Menu Management\n";
            cout << "4. Reservation Management\n";
            cout << "5. Order Management\n";
            cout << "6. Employee Management\n";
            cout << "7. Kitchen Management\n";
            cout << "8. Payment Management\n";
            cout << "9. Delivery Management\n";
            cout << "10. Reports\n";
            cout << "0. Exit\n";
            cout << "Choice: ";
            if (!(cin >> choice)) { cin.clear(); cin.ignore(10000, '\n'); continue; }

            switch (choice) {
            case 1: customerMenu(); break;
            case 2: tableMenu(); break;
            case 3: menuMenu(); break;
            case 4: reservationMenu(); break;
            case 5: orderMenu(); break;
            case 6: employeeMenu(); break;
            case 7: kitchenMenu(); break;
            case 8: paymentMenu(); break;
            case 9: deliveryMenu(); break;
            case 10: reportsMenu(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
            }
        } while (choice != 0);
    }

private:
    // -------------------- Customer --------------------
    void customerMenu() {
        int c;
        cout << "\n-- Customer Management --\n1. Add Customer\n2. Display All\n3. Search Customer\n4. Update Customer\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) {
            int id; string name, phone, addr, email;
            cout << "Enter Customer ID: "; cin >> id;
            cout << "Enter Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter Phone: "; getline(cin, phone);
            cout << "Enter Address: "; getline(cin, addr);
            cout << "Enter Email: "; getline(cin, email);
            customerManager.addCustomer(Customer(id, name, phone, addr, email));
        }
        else if (c == 2) {
            customerManager.displayAllCustomers();
        }
        else if (c == 3) {
            int id; cout << "Enter Customer ID: "; cin >> id;
            Customer* cust = customerManager.searchCustomer(id);
            if (cust) cust->displayInfo(); else cout << "Customer not found.\n";
        }
        else if (c == 4) {
            int id; string name, phone, addr, email;
            cout << "Enter Customer ID: "; cin >> id;
            cout << "New Name: "; cin.ignore(); getline(cin, name);
            cout << "New Phone: "; getline(cin, phone);
            cout << "New Address: "; getline(cin, addr);
            cout << "New Email: "; getline(cin, email);
            customerManager.updateCustomer(id, name, phone, addr, email);
        }
    }

    // -------------------- Table --------------------
    void tableMenu() {
        int c;
        cout << "\n-- Table Management --\n1. Add Table\n2. Display Available\n3. Search Table\n4. Update Status\n5. Assign Table\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) {
            int id, cap; string loc;
            cout << "Enter Table ID: "; cin >> id;
            cout << "Enter Capacity: "; cin >> cap;
            cout << "Enter Location: "; cin.ignore(); getline(cin, loc);
            tableManager.addTable(Table(id, cap, loc, TableStatus::Available));
        }
        else if (c == 2) {
            tableManager.displayAvailableTables();
        }
        else if (c == 3) {
            int id; cout << "Enter Table ID: "; cin >> id;
            Table* t = tableManager.searchTable(id);
            if (t) cout << "Table " << t->getTableID() << " | Status: " << t->getStatusString() << "\n";
            else cout << "Table not found.\n";
        }
        else if (c == 4) {
            int id, s; cout << "Enter Table ID: "; cin >> id;
            cout << "New Status (0=Available,1=Reserved,2=Occupied,3=OutOfService): "; cin >> s;
            tableManager.updateTableStatus(id, static_cast<TableStatus>(s));
        }
        else if (c == 5) {
            int id; cout << "Enter Table ID: "; cin >> id;
            tableManager.assignTable(id);
        }
    }

    // -------------------- Menu --------------------
    void menuMenu() {
        int c;
        cout << "\n-- Menu Management --\n1. Add Item\n2. Remove Item\n3. Search Item\n4. Display Menu\n5. Change Availability\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) {
            int id, cat; double price; string name, desc;
            cout << "Enter Item ID: "; cin >> id;
            cout << "Enter Price: "; cin >> price;
            cout << "Category (0=Appetizer,1=MainCourse,2=Dessert,3=Drink): "; cin >> cat;
            cout << "Enter Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter Description: "; getline(cin, desc);
            menuManager.addItem(MenuItem(id, name, price, static_cast<MenuCategory>(cat), desc, true));
        }
        else if (c == 2) {
            int id; cout << "Enter Item ID: "; cin >> id;
            menuManager.removeItem(id);
        }
        else if (c == 3) {
            int id; cout << "Enter Item ID: "; cin >> id;
            MenuItem* it = menuManager.searchItem(id);
            if (it) cout << it->getName() << " - " << it->getPrice() << "\n"; else cout << "Item not found.\n";
        }
        else if (c == 4) {
            menuManager.displayMenu();
        }
        else if (c == 5) {
            int id, av; cout << "Enter Item ID: "; cin >> id;
            cout << "Available? (1/0): "; cin >> av;
            menuManager.changeAvailability(id, av);
        }
    }

    // -------------------- Reservation --------------------
    void reservationMenu() {
        int c;
        cout << "\n-- Reservation Management --\n1. Create Reservation\n2. Confirm\n3. Cancel\n4. Display All\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) {
            int rid, cid, tid, guests; string date, time;
            cout << "Enter Reservation ID: "; cin >> rid;
            cout << "Enter Customer ID: "; cin >> cid;
            cout << "Enter Table ID: "; cin >> tid;
            cout << "Enter Date (YYYY-MM-DD): "; cin >> date;
            cout << "Enter Time: "; cin >> time;
            cout << "Number of Guests: "; cin >> guests;
            reservationManager.createReservation(Reservation(rid, cid, tid, date, time, guests, ReservationStatus::Pending));
        }
        else if (c == 2) {
            int id; cout << "Enter Reservation ID: "; cin >> id;
            reservationManager.confirmReservation(id);
        }
        else if (c == 3) {
            int id; cout << "Enter Reservation ID: "; cin >> id;
            reservationManager.cancelReservation(id);
        }
        else if (c == 4) {
            reservationManager.displayReservations();
        }
    }

    // -------------------- Order --------------------
    void orderMenu() {
        int c;
        cout << "\n-- Order Management --\n1. Create Order\n2. Add Item\n3. Update Status\n4. Cancel Order\n5. Display Order\n6. List All\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) {
            int cid, tid, t;
            cout << "Enter Customer ID: "; cin >> cid;
            cout << "Enter Table ID (0 if not dine-in): "; cin >> tid;
            cout << "Order Type (0=DineIn,1=Takeaway,2=Delivery): "; cin >> t;
            int oid = orderManager.createOrder(cid, tid, static_cast<OrderType>(t));
            if (oid != -1) cout << "Order created! ID: " << oid << "\n";
        }
        else if (c == 2) {
            int oid, iid, qty; double price; string name;
            cout << "Enter Order ID: "; cin >> oid;
            cout << "Enter Item ID: "; cin >> iid;
            cout << "Enter Item Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter Quantity: "; cin >> qty;
            cout << "Enter Price: "; cin >> price;
            orderManager.addItem(oid, OrderItem(iid, name, qty, price));
        }
        else if (c == 3) {
            int oid, s; cout << "Enter Order ID: "; cin >> oid;
            cout << "New Status (0=New,1=Preparing,2=Ready,3=Served,4=Completed,5=Cancelled): "; cin >> s;
            orderManager.updateOrderStatus(oid, static_cast<OrderStatus>(s));
        }
        else if (c == 4) {
            int oid; cout << "Enter Order ID: "; cin >> oid;
            orderManager.cancelOrder(oid);
        }
        else if (c == 5) {
            int oid; cout << "Enter Order ID: "; cin >> oid;
            orderManager.displayOrderDetails(oid);
        }
        else if (c == 6) {
            orderManager.displayAllOrders();
        }
    }

    // -------------------- Employee --------------------
    void employeeMenu() {
        int c;
        cout << "\n-- Employee Management --\n1. Add Employee\n2. Display All\n3. Search\n4. Update\n5. Change Availability\n6. Display By Role\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) employeeManager.addEmployee();
        else if (c == 2) employeeManager.displayEmployees();
        else if (c == 3) employeeManager.searchEmployee();
        else if (c == 4) employeeManager.updateEmployee();
        else if (c == 5) employeeManager.changeAvailability();
        else if (c == 6) {
            int r; cout << "Role (0=Manager,1=Chef,2=Waiter,3=Cashier,4=DeliveryDriver): "; cin >> r;
            employeeManager.displayByRole(static_cast<EmployeeRole>(r));
        }
    }

    // -------------------- Kitchen --------------------
    void kitchenMenu() {
        int c;
        cout << "\n-- Kitchen Management --\n1. View Pending\n2. Start Preparing\n3. Mark Ready\n4. Display Prepared\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) kitchen.viewPendingOrders();
        else if (c == 2) kitchen.startPreparing();
        else if (c == 3) kitchen.markReady();
        else if (c == 4) kitchen.displayPreparedOrders();
    }

    // -------------------- Payment --------------------
    void paymentMenu() {
        int c;
        cout << "\n-- Payment Management --\n1. Process Payment\n2. Display Details\n3. Refund\n4. Receipt\n5. History\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) {
            int oid, m; double amt;
            cout << "Enter Order ID: "; cin >> oid;
            cout << "Enter Amount: "; cin >> amt;
            cout << "Method (0=Cash,1=Card,2=MobilePayment): "; cin >> m;
            paymentManager.processPayment(oid, amt, static_cast<PaymentMethod>(m));
        }
        else if (c == 2) {
            int id; cout << "Enter Payment ID: "; cin >> id;
            paymentManager.displayPaymentDetails(id);
        }
        else if (c == 3) {
            int id; cout << "Enter Payment ID: "; cin >> id;
            paymentManager.refundPayment(id);
        }
        else if (c == 4) {
            int id; cout << "Enter Payment ID: "; cin >> id;
            paymentManager.generateReceipt(id);
        }
        else if (c == 5) {
            paymentManager.viewPaymentHistory();
        }
    }

    // -------------------- Delivery --------------------
    void deliveryMenu() {
        int c;
        cout << "\n-- Delivery Management --\n1. Assign Delivery\n2. Track Status\n3. Update Status\n4. View All\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) {
            int oid, driverID; string addr;
            cout << "Enter Order ID: "; cin >> oid;
            cout << "Enter Driver Employee ID: "; cin >> driverID;
            cout << "Enter Delivery Address: "; cin.ignore(); getline(cin, addr);
            deliveryManager.assignDelivery(oid, driverID, addr);
        }
        else if (c == 2) {
            int id; cout << "Enter Delivery ID: "; cin >> id;
            deliveryManager.trackDeliveryStatus(id);
        }
        else if (c == 3) {
            int id, s; cout << "Enter Delivery ID: "; cin >> id;
            cout << "New Status (0=Assigned,1=OnTheWay,2=Delivered,3=Cancelled): "; cin >> s;
            deliveryManager.updateDeliveryStatus(id, static_cast<DeliveryStatus>(s));
        }
        else if (c == 4) {
            deliveryManager.viewAllDeliveries();
        }
    }

    // -------------------- Reports --------------------
    void reportsMenu() {
        int c;
        cout << "\n-- Reports --\n1. Daily Sales\n2. Monthly Revenue\n3. Top Selling Items\n4. Employee Performance\n5. Delivery Report\n0. Back\nChoice: ";
        cin >> c;
        if (c == 1) {
            string date; cout << "Enter Date (YYYY-MM-DD): "; cin >> date;
            reportManager.generateDailySalesReport(date);
        }
        else if (c == 2) {
            string month; cout << "Enter Month (YYYY-MM): "; cin >> month;
            reportManager.generateMonthlyRevenueReport(month);
        }
        else if (c == 3) {
            reportManager.generateTopSellingItemsReport();
        }
        else if (c == 4) {
            reportManager.generateEmployeePerformanceReport();
        }
        else if (c == 5) {
            reportManager.generateDeliveryReport();
        }
    }
};

// ============================================================================
// main() 
// ============================================================================
int main() {
    clearScreen();
    cout << "Welcome to the Restaurant Management System!\n";

    RestaurantSystem system;
    system.run();

    return 0;
}