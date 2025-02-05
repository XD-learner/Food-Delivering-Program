#include <iostream>
#include <string>
#include <sstream> 
using namespace std;

void out(string str, int padding=10){
    int spacePadding = padding - str.length();
    cout << str;
    for (int j = 0; j < spacePadding; ++j) cout << " ";
    cout << "| " ;
}
void out(int digit, int padding=10){
    int spacePadding = padding - to_string(digit).length();
    cout << digit;
    for (int j = 0; j < spacePadding; ++j) cout << " ";
    cout << "| " ;
}
struct DriverNode; // 🔹 Forward declaration of DriverNode
struct OrderNode {
    int orderId;
    string customerName;
    string deliveryAddress;
    string foodDescription;
    string contactNumber;
    string status; // e.g., Pending, Preparing, Out for Delivery, Delivered
    DriverNode* CWDriver;
    OrderNode* next;
};

struct DriverNode {
    int driverId;
    string driverName;
    string status; // e.g., Available, Delivering, Offline
    //int orderNumber;
    OrderNode* CWOrder;
    string contactNumber;
    int totalDelivered;
    DriverNode* next;
};
struct QueueNode {
    OrderNode* order;
    QueueNode* next;
};

class OrderQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    OrderQueue(){
        front = rear = nullptr;
    }
    QueueNode* getFront() {
        return front;
    }
    // Add an order to the queue (doesn't change the linked list)
    void addOrderToQueue(OrderNode* order) {
        QueueNode* newQueueNode = new QueueNode{ order, nullptr };
        order->status = "Pending";
        if (!rear) {
            front = rear = newQueueNode;
        } else {
            rear->next = newQueueNode;
            rear = newQueueNode;
        }
    }

    // Serve an order (assign to driver)
    OrderNode* serveOrder() {
        if (!front) {
            cout << "No orders in the queue!" << endl;
            return nullptr;
        }

        // Get the order node from the front of the queue
        QueueNode* servedQueueNode = front;
        front = front->next;

        // If queue is empty after serving, reset rear to nullptr
        if (!front) {
            rear = nullptr;
        }

        OrderNode* servedOrder = servedQueueNode->order;
        delete servedQueueNode;  // Free the QueueNode, not the OrderNode
        return servedOrder;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    
    
}orderQueue;
class OrderList{
    private:
        OrderNode* front;
        int orderIdCounter;
        
    public:
        OrderList() {
            front = nullptr;
            orderIdCounter = 0;
        }
        // Add new order to the linked list
        OrderNode* getFront(){

            return front;
            
        }
        
        void addOrder(string customerName, string deliveryAddress, string foodDescription, string contactNumber) {
            OrderNode* newNode = new OrderNode{ ++orderIdCounter, customerName, deliveryAddress, foodDescription, contactNumber, "Unassigned", nullptr, nullptr };
            if (!front) {
                front = newNode;
            } else {
                OrderNode* temp = front;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        void removeOrder(int orderId) {
            OrderNode* temp = front;
            OrderNode* prev = nullptr;

            // Case: List is empty
            if (!front) {
                cout << "No orders available to remove!\n";
                return;
            }

            // Case: First node is the target node
            if (front->orderId == orderId) {
                front = front->next;  // Move the head
                delete temp;  // Free memory
                cout << "Order " << orderId << " removed successfully!\n";
                return;
            }

            // Traverse the list to find the node
            while (temp != nullptr && temp->orderId != orderId) {
                prev = temp;
                temp = temp->next;
            }

            // If orderId not found
            if (!temp) {
                cout << "Order not found!\n";
                return;
            }

            // Update the previous node's next pointer
            prev->next = temp->next;
            delete temp;  // Free memory

            cout << "Order " << orderId << " removed successfully!\n";
        }
        void updateOrderCustomerName(int selectedOrder, const string& newCustomerName) {
            OrderNode* temp = front;
            while (temp != NULL) {
                if (temp->orderId == selectedOrder) {
                    temp->customerName = newCustomerName;
                    // cout << "Order " << selectedOrder << "'s customer name is now updated to " << newCustomerName << "!" << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "Order not found!\n" << endl;
        }
        void updateOrderDeliveryAddress(int selectedOrder, const string& newDeliveryAddress) {
            OrderNode* temp = front;
            while (temp != NULL) {
                if (temp->orderId == selectedOrder) {
                    temp->deliveryAddress = newDeliveryAddress;
                    // cout << "Order " << selectedOrder << "'s delivery address is now updated!" << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "Order not found!\n" << endl;
        }
        void updateOrderFoodDescription(int selectedOrder, const string& newFoodDescription) {
            OrderNode* temp = front;
            while (temp != NULL) {
                if (temp->orderId == selectedOrder) {
                    temp->foodDescription = newFoodDescription;
                    // cout << "Order " << selectedOrder << "'s food description is now updated!" << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "Order not found!\n" << endl;
        }
        void updateOrderStatus(int selectedOrder, int option) {
            OrderNode* temp = front;
            bool found = false;  // Flag to check if the order is found
            while (temp != NULL) {
                if (temp->orderId == selectedOrder) {
                    found = true;  // Mark as found
                    switch (option) {
                        case 1:
                            temp->status = "Unassigned";
                            break;
                        case 2:
                            temp->status = "Pending";
                            break;
                        case 3:
                            temp->status = "Delivering";
                            break;
                        case 4:
                            temp->status = "Delivered";
                            break;
                        default:
                            cout << "Invalid option. Keeping current status.\n";
                            break;
                    }
                    break;  
                }
                temp = temp->next;  
            }

            if (!found) {
                cout << "Order not found!\n" << endl;
            }
        }

        void updateOrderContact(int selectedOrder, const string& newContactNumber) {
            OrderNode* temp = front;
            while (temp != NULL) {
                if (temp->orderId == selectedOrder) {
                    temp->contactNumber = newContactNumber;
                    return;
                }
                temp = temp->next;
            }
            cout << "Driver not found!\n" << endl;
        }

        
        void displayOrders(string key = "All", string value = "") {
            cout << "Orders List (" << key << ": " << value << ")" << endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "ID   | Customer Name   | Status          | Contact         | Address         | Food Descr      | DriverId        | DriverName      |" << endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;

            
            bool found = false;

            // Show all orders if 'key' is "All" or filter by a specific key-value pair
            if(key == "status" && value == "Pending"){
                QueueNode* queueNode = orderQueue.getFront();
                while(queueNode != NULL){
                        out(queueNode->order->orderId, 5);
                        out(queueNode->order->customerName, 16);
                        out(queueNode->order->status, 16);
                        out(queueNode->order->contactNumber, 16);
                        out(queueNode->order->deliveryAddress, 16);
                        out(queueNode->order->foodDescription, 16);

                        if (queueNode->order->CWDriver != nullptr) {
                            out(to_string(queueNode->order->CWDriver->driverId), 16);
                            out(queueNode->order->CWDriver->driverName, 16);
                            
                        }else{
                            out("None", 16);
                            out("None", 16);
                        }
                        cout << endl;
                        found = true;
                    queueNode = queueNode->next;
                }
            }else{
                OrderNode* temp = front;
                while (temp != NULL) {
                    bool match = false;

                    // Apply the filter based on the key-value pair
                    if (key == "All") {
                        match = true;  // Show all orders if key is "All"
                    } else if (key == "status" && temp->status == value) {
                        match = true;  // Match if status matches the value
                    } else if (key == "customerName" && temp->customerName == value) {
                        match = true;  // Match if customerName matches the value
                    } else if (key == "orderId" && to_string(temp->orderId) == value) {
                        match = true;  // Match if orderId matches the value
                    } else if (key == "contactNumber" && temp->contactNumber == value) {
                        match = true;  // Match if contactNumber matches the value
                    } else if (key == "deliveryAddress" && temp->deliveryAddress == value) {
                        match = true;  // Match if deliveryAddress matches the value
                    } else if (key == "foodDescription" && temp->foodDescription == value) {
                        match = true;  // Match if foodDescription matches the value
                    } else if(temp->CWDriver != nullptr){
                            if (key == "driverId" && temp->CWDriver->driverId == stoi(value)) {
                                match = true;  // Match if driverId matches the value
                            } else if (key == "driverName" && temp->CWDriver->driverName == value) {
                                match = true;  // Match if driverName matches the value
                            }
                    }

                    // Display the order details if it matches the filter
                    if (match) {
                        out(temp->orderId, 5);
                        out(temp->customerName, 16);
                        out(temp->status, 16);
                        out(temp->contactNumber, 16);
                        out(temp->deliveryAddress, 16);
                        out(temp->foodDescription, 16);
                        if (temp->CWDriver != nullptr) {
                            out(to_string(temp->CWDriver->driverId), 16);
                            out(temp->CWDriver->driverName, 16);
                            
                        }else{
                            out("None", 16);
                            out("None", 16);
                        }
                        cout << endl;
                        found = true;  // Mark that at least one order matches the filter
                    }

                    temp = temp->next;
                }
            }
                // If no order matches the filter, display a message
            if (!found) {
                cout << "No order results returned matching '" << value << "'" << endl;
            }

            cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl<< endl;
        }
            

        // Get a pointer to an order by orderId (used by the queue)
        OrderNode* getOrderById(int orderId) {
            OrderNode* temp = front;
            while (temp) {
                if (temp->orderId == orderId) {
                    return temp;
                }
                temp = temp->next;
            }
            return nullptr;  // If not found
        }
};


class DriverList {
private:
    DriverNode* front;
    int driverId =0;

public:
    DriverList() {
        front = NULL;
        
    }
    int getDriverId() {
        return driverId;
    }
    DriverNode* getFront() {
        return front;
    }
    void addDriver(string driverName, string contact) {
        driverId++;
        DriverNode* newNode = new DriverNode{driverId, driverName, "Available", 0, contact, 0, NULL};
        // If the list is empty, the new node becomes the front (first node)
        if (!front) {
            front = newNode;
        } else {
            // Traverse to the last node to add the new driver
            DriverNode* temp = front;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode; // Add new node at the end
        }
    }

    void removeDriver(int driverId) {
        DriverNode* temp = front;
        DriverNode* prev = nullptr;

        // Case: List is empty
        if (!front) {
            cout << "No drivers available to remove!\n";
            return;
        }

        // Case: First node is the target node
        if (front->driverId == driverId) {
            front = front->next;
            delete temp;
            cout << "Driver " << driverId << " removed successfully!\n";
            return;
        }

        // Traverse the list to find the node
        while (temp != nullptr && temp->driverId != driverId) {
            prev = temp;
            temp = temp->next;
        }

        // If driverId not found
        if (!temp) {
            cout << "Driver not found!\n";
            return;
        }

        // Update the previous node's next pointer
        prev->next = temp->next;
        delete temp;

        cout << "Driver " << driverId << " removed successfully!\n";
    }
    void displayDrivers(string key = "All", string value = "") {
        cout << "Driver Assignments (" << key << ": " << value << ")" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "ID   | Driver Name     | Status          | Ongoing OrderID | Contact         | Total Delivered |" << endl;
        cout << "------------------------------------------------------------------------------------------------" << endl;

        DriverNode* temp = front;
        bool found = false;  // Flag to check if any drivers are displayed based on the filter

        while (temp != NULL) {
            bool match = false;

            // Apply the filter based on the key-value pair
            if (key == "All") {
                match = true;  // Show all drivers if key is "All"
            } else if (key == "status" && temp->status == value) {
                match = true;  // Match if status matches the value
            } else if (key == "driverName" && temp->driverName == value) {
                match = true;  // Match if driverName matches the value
            } else if (key == "driverId" && to_string(temp->driverId) == value) {
                match = true;  // Match if driverId matches the value
            } else if (key == "contactNumber" && temp->contactNumber == value) {
                match = true;  // Match if contactNumber matches the value
            } else if (key == "totalDelivered" && temp->totalDelivered == stoi(value)) {
                match = true;  // Match if totalDelivered matches the value
            } else if (key == "orderId" && temp->CWOrder != nullptr && temp->CWOrder->orderId == stoi(value)) {
                match = true;  // Match if orderId matches the value and the CWOrder is not null
            }

            // If there's a match, display the driver's information
            if (match) {
                out(temp->driverId, 5);
                out(temp->driverName, 16);
                out(temp->status, 16);
                if (temp->CWOrder != nullptr) {
                    out(temp->CWOrder->orderId, 16);
                } else {
                    out("None", 16);
                }
                out(temp->contactNumber, 16);
                out(temp->totalDelivered, 16);
                cout << endl;
                found = true;  // Mark that at least one driver matches the filter
            }

            temp = temp->next;
        }

        if (!found) {
            cout << "No driver results found matching '" << value << "'                                                                  " << endl;
        }

        cout << "------------------------------------------------------------------------------------------------"<< endl << endl;
    }



    void updateDriverName(int driverId, const string& newDriverName) {
        DriverNode* temp = front;
        while (temp != NULL) {
            if (temp->driverId == driverId) {
                temp->driverName = newDriverName;
                cout << "Driver " << driverId << "'s name has been updated to " << newDriverName << ".\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Driver not found!\n" << endl;
    }
    void updateDriverStatus(int driverId, int option) {
        DriverNode* temp = front; // Assuming 'front' is the head of the list
        while(temp != NULL) {
            if (temp->driverId == driverId) {
                switch (option) {
                    case 1:
                        temp->status = "Available";
                        break;
                    case 2:
                        temp->status = "Delivering";
                        break;
                    case 3:
                        temp->status = "Offline";
                        break;
                    default:
                        cout << "Invalid option. Keeping current status.\n";
                        break;
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Driver not found!\n" << endl;
    }

    void addOrderToDriver(OrderQueue& orderQueue, int driverId) {
        
        // First, check if the driver exists
        DriverNode* driver = front;
        while (driver != nullptr) {
            if (driver->driverId == driverId) {
                break;
            }
            driver = driver->next;
        }

        if (driver == nullptr) {
            cout << "Driver not found!" << endl;
            return;
        }

        if (driver->status == "Offline"){
            cout << "Driver " << driver->driverName << " is currentyl offline. Cannot assign an order." << endl;
            return;
        }else if(driver->status == "Delivering") {
            cout << "Driver " << driver->driverName << " is already delivering an order. Cannot assign another." << endl;
            return;
        }

        // Serve an order from the OrderQueue
        OrderNode* servedOrder = orderQueue.serveOrder();
        if (servedOrder == nullptr) {
            cout << "No orders available to assign!" << endl;
            return;
        }

        // Append the order to the driver's orders list (using the existing OrderNode)
        // servedOrder->next = driver->orders;  // Point the new order to the current head
        driver->CWOrder = servedOrder; 


        // Update the driver’s status to "Delivering"
        driver->status = "Delivering";

        // Update the order's status to "Assigned"
        servedOrder->status = "Delivering";
        servedOrder->CWDriver = driver;
       

        
        cout << "Order " << servedOrder->orderId << " has been assigned to Driver " << driver->driverName << endl;
    }
    void completeOrder(OrderQueue& orderQueue, int driverId){
        DriverNode* driver = front;
        while (driver!= NULL) {
            if (driver->driverId == driverId) {
                break;
            }
            driver = driver->next;
        }
        if (driver == NULL) {
            cout << "Driver not found!" << endl;
            return;
        }
        if (driver->CWOrder == nullptr) {
            cout << "Driver " << driver->driverName << " does not have any orders to complete." << endl;
            return;
        }
        
        driver->CWOrder->status = "Delivered";
        driver->status = "Available";
        driver->totalDelivered +=1;
        driver->CWOrder = nullptr;

    }

    void updateDriverContact(int driverId, const string& newContactNumber) {
        DriverNode* temp = front;
        while (temp != NULL) {
            if (temp->driverId == driverId) {
                temp->contactNumber = newContactNumber;
                cout << "Driver " << temp->driverName << "'s contact number updated successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Driver not found!\n" << endl;
    }
    void updateDriverTotalDelivered(int driverId, int amountToAdd) {
        DriverNode* temp = front;
            while (temp != NULL) {
                if (temp->driverId == driverId) {
                    temp->totalDelivered += amountToAdd;
                    cout << "Driver " << temp->driverName << " now has " << temp->totalDelivered << " deliveries.\n";
                    return;
                }
                temp = temp->next;
            }
            cout << "Driver not found!\n" << endl;
    }

};




int main() {
    DriverList driverList;
    OrderList  orderList;
    
    driverList.addDriver("John", "012345");
    driverList.addDriver("Jane", "0234");
    driverList.addDriver("Emily", "012312");

    orderList.addOrder("John Doe", "123 Main St", "Pizza, Salad", "0123123");
    orderList.addOrder("baby GAY7", "321 BUYEE St", "BUN, BOM", "0123123");
    orderList.addOrder("Jane Smith", "456 Elm St", "Burger, Fries", "0123123");
    orderList.addOrder("Emily Davis", "789 Oak St", "Sushi, Miso Soup", "0123123");


    char choice = '\0';
    while (choice != 'X') {

        system("CLS");
        cout << "========================================\n";
        cout << "         Food Delivery System          \n";
        cout << "========================================\n";
        cout << "     Quick Actions\n";
        cout << "----------------------------------------\n";
        cout << "[Q] Add Order To Queue\n";
        cout << "[A] Assign Driver\n";
        cout << "[C] Complete Order\n\n";

        cout << "     View & Manage\n";
        cout << "----------------------------------------\n";
        cout << "[M] Administration (Manage Orders & Drivers)\n";
        cout << "[X] Exit\n";
        
        cout << "Enter your choice: ";
        cin >> choice;
        choice = toupper(choice);
        cin.ignore();

        int driverId = 0, orderId = 0;
        
        
        switch (choice){
            case 'Q':{
                string input;
                while (true) {
                    system("CLS");
                    orderList.displayOrders("status", "Unassigned");
                    cout << "Queue Orders:" << endl;
                    orderList.displayOrders("status", "Pending");
                    cout << "\nEnter Order ID to add to the queue, or press Enter to add topmost order, or 'Q' to quit: ";
                    getline(cin, input);

                    // Check if input is empty (pressing Enter)
                    // Inside the loop

                    // Check if input is 'Q' to quit
                    if (input == "Q" || input == "q") {
                        cout << "Exiting..." << endl;
                        break;
                    }
                    if (input.empty()) {
                        // Check for the first unassigned order
                        OrderNode* order = orderList.getFront();
                        bool added = false;  // Flag to track if an order is added

                        while (order != nullptr) {
                            if (order->status == "Unassigned") {
                                orderQueue.addOrderToQueue(order);
                                cout << "Topmost unassigned order (ID: " << order->orderId << ") added to the queue." << endl;
                                added = true;
                                break;  // Stop once an unassigned order is added
                            }
                            order = order->next;
                        }

                        if (!added) {
                            cout << "No unassigned orders available." << endl;
                        }
                    }

                    // Check if input is a number (Order ID) using stringstream
                    else {
                        stringstream ss(input);
                        int orderId;
                        ss >> orderId;  // Convert string to integer

                        if (ss.fail()) {
                            cout << "Invalid input! Please enter a valid Order ID, press Enter to add topmost order, or 'Q' to quit." << endl;
                            continue;
                        }

                        // Find the order by ID in the order list
                        OrderNode* order = orderList.getOrderById(orderId);
                        if (order) {
                            if (order->status == "Unassigned"){
                                orderQueue.addOrderToQueue(order);
                                cout << "Order " << orderId << " added to the queue." << endl;
                            }else{
                                cout << "Order ID is already assigned!";
                            }
                            
                        }else{
                            cout << "Order ID not found !" << endl;
                        }
                    }
                    
                }
                break;
            }
            case 'A':{  // Assign Driver
                while(true){
                    string input;

                    system("CLS");
                    orderList.displayOrders("status", "Pending");  // Display pending orders
                    // Display available drivers
                    driverList.displayDrivers("status","Available");
                    cout << "\nEnter Driver ID to assign, or 'Q' to quit: ";
                    cin >> input;

                    if(input == "Q" || input == "q"){
                        break;
                    }
                    stringstream ss(input);
                        int driverId;
                        ss >> driverId;  // Convert string to integer

                        if (ss.fail()) {
                            cout << "Invalid input! Please enter a valid Order ID, press Enter to add topmost order, or 'Q' to quit." << endl;
                            continue;
                        }
                    
                    
                    cin.ignore();

                    driverList.addOrderToDriver(orderQueue, driverId);
                    
                }
                break;
            }
            case 'C':{
                while(true){
                    string input;

                    system("CLS");
                    driverList.displayDrivers("status","Delivering");
                    cout << "Enter Driver ID to complete order, or 'Q' to quit: ";
                    cin >> input;
                    cin.ignore();

                    if(input == "Q" || input == "q"){
                        break;
                    }
                    stringstream ss(input);
                        int driverId;
                        ss >> driverId;
                    driverList.completeOrder(orderQueue, driverId);
                    
                }
                break;
            }
            
            case 'V':{
                break;
            }
            case 'M':{
                char adminChoice  = '\0';
                while(adminChoice !='B'){
                    system("CLS");
                    cout << "    Administration\n";
                    cout << "[O] Manage Orders\n";
                    cout << "[D] Manage Drivers\n";
                    cout << "[B] Back\n";
                    cout << "Enter choice: ";
                    cin >> adminChoice;
                    adminChoice = toupper(adminChoice);
                    choice = toupper(adminChoice);
                    cin.ignore();

                    char orderChoice = '\0';
                    char driverChoice = '\0';
                    int statusOption = 0;
                    char statusChoice = '\0';
                    char updateChoice = '\0';
                    string key = "All", value = "";

                    
                    switch(adminChoice){
                        case 'O':{  // Orders Menu
                            while(orderChoice != 'B'){
                                system("CLS");
                                orderList.displayOrders();  // Display all orders to choose from
                                cout << "📦 Orders\n";
                                cout << "[C] Create Order\n";  
                                cout << "[R] Read/Search Orders\n";
                                cout << "[U] Update Order Info\n";
                                cout << "[D] Delete Order\n";
                                cout << "[B] Back\n";

                                cin >> orderChoice;
                                orderChoice = toupper(orderChoice);
                                cin.ignore();

                                switch (orderChoice) {
                                    
                                    case 'C': {
                                        // Add Order
                                        system("CLS");
                                        orderList.displayOrders();
                                        cout << "Enter customer name: ";
                                        string customerName;
                                        getline(cin, customerName);
                                        cout << "Enter contact: ";
                                        string contact;
                                        getline(cin, contact);
                                        cout << "Enter delivery address: ";
                                        string deliveryAddress;
                                        getline(cin, deliveryAddress);
                                        cout << "Enter food description: ";
                                        string foodDescription;
                                        getline(cin, foodDescription);
                                        orderList.addOrder(customerName, deliveryAddress, foodDescription, contact);
                                        break;
                                    }
                                    case 'R': { // View Orders (Filter by various criteria)
                                        system("CLS");
                                        orderList.displayOrders();

                                        // Display filter options to the user
                                        char filterChoice;
                                        cout << "View Orders by Filter\n";
                                        cout << "[S] Status             [C] Customer Name\n";
                                        cout << "[O] Order ID           [N] Contact Number\n";
                                        cout << "[D] Delivery Address   [F] Food Description\n";
                                        cout << "[R] Driver Name        [I] Driver ID\n";
                                        cin >> filterChoice;
                                        filterChoice = toupper(filterChoice);  // Convert input to uppercase for consistency
                                        cin.ignore();  // Clear the input buffer
                                        
                                        
                                        // Use a switch statement for primary filtering choices
                                        switch (filterChoice) {
                                            case 'S':{
                                                key = "status";
                                                system("CLS");
                                                orderList.displayOrders();
                                                // Prompt the user to choose the filter
                                                char statusChoice;
                                                cout << "View Orders by Status\n";
                                                cout << "[U] Unassigned Orders  [P] Pending Orders\n";
                                                cout << "[D] Delivered Orders   [R] Delivered Orders\n";
                                                cin >> statusChoice;
                                                statusChoice = toupper(statusChoice);  // Convert input to uppercase for consistency
                                                cin.ignore();  // Clear the input buffer
                                                
                                                // Determine the filter key and value based on user input
                                                switch (statusChoice) {
                                                    case 'U':{ // Unassigned Orders
                                                        value = "Unassigned";
                                                        break;
                                                    }

                                                    case 'P':{ // Pending Orders
                                                        value = "Pending";
                                                        break;
                                                    }

                                                    case 'D':{ // Delivering Orders
                                                        value = "Delivering";
                                                        break;
                                                    }
                                                    case 'R':{// Delivered Orders
                                                        value = "Delivered";
                                                        break;
                                                    }


                                                    default:{ // Invalid input
                                                        cout << "Invalid choice. Please select a valid option.\n";
                                                        break;
                                                    }
                                                }
                                                
                                                break;
                                            }

                                            case 'C': { // Customer Name
                                                key = "customerName";
                                                cout << "Enter Customer Name: ";
                                                getline(cin, value);
                                                break;
                                            }

                                            case 'O':{  // Order ID
                                                key = "orderId";
                                                cout << "Enter Order ID: ";
                                                getline(cin, value);
                                                break;
                                            }

                                            case 'N':{ // Contact Number
                                                key = "contactNumber";
                                                cout << "Enter Contact Number: ";
                                                getline(cin, value);
                                                break;
                                            }

                                            case 'D':{// Delivery Address
                                                key = "deliveryAddress";
                                                cout << "Enter Delivery Address: ";
                                                getline(cin, value);
                                                break;
                                            }

                                            case 'F':{// Food Description
                                                key = "foodDescription";
                                                cout << "Enter Food Description: ";
                                                getline(cin, value);
                                                break;
                                            }

                                            case 'R':{ // Driver Name
                                                key = "driverName";
                                                cout << "Enter Driver Name: ";
                                                getline(cin, value);
                                                break;
                                            }

                                            case 'I':{  // Driver ID
                                                key = "driverId";
                                                cout << "Enter Driver ID: ";
                                                getline(cin, value);
                                                break;
                                            }

                                            default:{  // Invalid choice
                                                cout << "Invalid choice. Please select a valid option.\n";
                                                break;  // Exit the case block on invalid input
                                            }
                                        }   
                                        
                                        // If a valid filter was selected, display the filtered orders
                                        if (!key.empty()) {
                                            system("CLS");
                                            orderList.displayOrders(key, value);
                                            cout << "Enter to continue...";
                                            cin.ignore();
                                        }

                                        break;
                                    }

                                    case 'U': { 
                                        // Update Order Information
                                        system("CLS");
                                        orderList.displayOrders();  // Display all orders to choose from
                                        cout << "Enter Order ID to update: ";
                                        cin >> orderId;
                                        cin.ignore();  // Clear the input buffer

                                        system("CLS");
                                        orderList.displayOrders("orderId", to_string(orderId));
                                        cout << "Select what to update:\n";
                                        cout << "[N] Customer Name\n";
                                        cout << "[C] Contact\n";
                                        cout << "[D] Delivery Address\n";
                                        cout << "[F] Food Description\n";
                                        cout << "Enter choice: ";
                                        cin >> updateChoice;
                                        updateChoice =toupper(updateChoice);
                                        cin.ignore();

                                        switch (updateChoice) {
                                            case 'N': {  // Update Customer Name
                                                cout << "Enter new customer name: ";
                                                string newCustomerName;
                                                getline(cin, newCustomerName);
                                                orderList.updateOrderCustomerName(orderId, newCustomerName);
                                                break;
                                            }
                                            case 'C':{
                                                cout << "Enter new contact: ";
                                                string newContact;
                                                getline(cin, newContact);
                                                orderList.updateOrderContact(orderId, newContact);
                                                break;
                                                }
                                            case 'D': {  // Update Delivery Address
                                                cout << "Enter new delivery address: ";
                                                string newDeliveryAddress;
                                                getline(cin, newDeliveryAddress);
                                                orderList.updateOrderDeliveryAddress(orderId, newDeliveryAddress);
                                                break;
                                            }
                                            case 'F': {  // Update Food Description
                                                cout << "Enter new food description: ";
                                                string newFoodDescription;
                                                getline(cin, newFoodDescription);
                                                orderList.updateOrderFoodDescription(orderId, newFoodDescription);
                                                break;
                                            }
                                            
                                            default:{
                                                cout << "Invalid choice! Returning to the menu.\n";
                                                break;
                                            }
                                        }
                                        break;
                                    
                                    }
                                    case 'D':{
                                        cout << "Enter Order ID to remove: ";
                                        cin >> orderId;
                                        cout << "Are you sure you want to remove this order? (Y/N): ";
                                        char confirmation;
                                        cin >> confirmation;
                                        cin.ignore();
                                        if (confirmation == 'Y' || confirmation == 'y') {
                                            orderList.removeOrder(orderId);
                                            cout << "Order removed successfully!" << endl;
                                        } else {
                                            cout << "Order removal cancelled." << endl;
                                        }
                                        break;
                                    }
                                    case 'B':{
                                        break;
                                    }
                                        
                                    default:{
                                        cout << "Invalid choice!\n";
                                        break;
                                    }
                                }
                            
                            }
                            break;
                        }
                        case 'D': {  // Drivers Menu

                        while(driverChoice != 'B'){
                            system("CLS");

                            driverList.displayDrivers();

                            cout << "🚗 Drivers\n";
                            cout << "[C] Create Driver\n";
                            cout << "[R] Read/Search Driver\n";
                            cout << "[U] Update Driver Information\n";
                            cout << "[D] Delete Driver\n";
                            cout << "[B] Back\n";

                            cout << "Enter choice: ";
                            cin >> driverChoice;
                            driverChoice = toupper(driverChoice);
                            cin.ignore();

                            switch (driverChoice) {
                                
                                case 'C': {

                                    system("CLS");
                                    driverList.displayDrivers();
                                    string driverName;
                                    string contact;
                                    cout << "Enter Driver Information: " << endl;
                                    cout << "Driver Name: " << endl;
                                    getline(cin, driverName);
                                    cout << "Contact Number: " << endl ;
                                    getline(cin, contact);
                                    driverList.addDriver(driverName, contact);
                                    break;
                                }

                                case 'R':{
                                    system("CLS");
                                    driverList.displayDrivers();

                                    // Display filter options to the user
                                    char filterChoice;
                                    cout << "Search Drivers by Filter\n";
                                    cout << "[S] Status           [N] Driver Name\n";
                                    cout << "[D] Driver ID        [C] Contact \n";
                                    cout << "[T] Total Delivery   [O] Order Id\n";
                                    cin >> filterChoice;
                                    filterChoice = toupper(filterChoice);  // Convert input to uppercase for consistency
                                    cin.ignore();  // Clear the input buffer

                                    switch (filterChoice) {
                                        case 'S':{
                                                key = "status";
                                                system("CLS");
                                                driverList.displayDrivers();
                                                // Prompt the user to choose the filter
                                                char statusChoice;
                                                cout << "Search Orders by Status\n";
                                                cout << "[A] Available  [D] Delivering  [O] Offline ";
                                                cin >> statusChoice;
                                                statusChoice = toupper(statusChoice);  // Convert input to uppercase for consistency
                                                cin.ignore();  // Clear the input buffer
                                                
                                                // Determine the filter key and value based on user input
                                                switch (statusChoice) {
                                                    case 'A':{ // Unassigned Orders
                                                        value = "Available";
                                                        break;
                                                    }

                                                    case 'D':{ // Pending Orders
                                                        value = "Delivering";
                                                        break;
                                                    }

                                                    case 'O':{// Delivered Orders
                                                        value = "Offline";
                                                        break;
                                                    }


                                                    default:{ // Invalid input
                                                        cout << "Invalid choice. Please select a valid option.\n";
                                                        break;
                                                    }
                                                }
                                                
                                                break;
                                        }
                                        case 'N':{  // Driver Name
                                                    key = "driverName";
                                                    cout << "Enter Driver Name: ";
                                                    getline(cin, value);
                                                    break;
                                                }
                                        case 'D':{  // Driver ID
                                                    key = "driverId";
                                                    cout << "Enter Driver ID: ";
                                                    getline(cin, value);
                                                    break;
                                        }
                                        case 'C':{  // Driver Contact
                                                    key = "contactNumber";
                                                    cout << "Enter Contact: ";
                                                    getline(cin, value);
                                                    break;
                                        }
                                        case 'T':{  // Driver Total Delivery
                                                    key = "totalDelivered";
                                                    cout << "Enter Total Delivered Count: ";
                                                    getline(cin, value);
                                                    break;
                                        }
                                        case 'O':{  // Driver Current Working Order Id
                                                    key = "orderId";
                                                    cout << "Enter Order ID: ";
                                                    getline(cin, value);
                                                    break;
                                        }

                                        default:{  // Invalid choice
                                            cout << "Invalid choice. Please select a valid option.\n";
                                            break;  // Exit the case block on invalid input
                                        }
                                    }
                                    if (!key.empty()) {
                                            system("CLS");
                                            driverList.displayDrivers(key, value);
                                            cout << "Enter to continue...";
                                            cin.ignore();
                                        }
                                    
                                    break;
                                }

                                case 'U': {  // Update Driver Information
                                    system("CLS");
                                    driverList.displayDrivers();
                                    cout << "Enter Driver ID to update: ";
                                    cin >> driverId;
                                    cin.ignore();


                                    system("CLS");
                                    driverList.displayDrivers("driverId",to_string(driverId));
                                    cout << "Select what to update:\n";
                                    cout << "[N] Driver Name\n";
                                    cout << "[C] Contact Number\n";
                                    cout << "[S] Status\n";
                                    cout << "[R] Remove Driver\n";
                                    cout << "Enter choice: ";
                                    cin >> updateChoice;
                                    updateChoice = toupper(updateChoice);
                                    cin.ignore();

                                    switch (updateChoice) {
                                        case 'N': {  // Update Driver Name
                                            cout << "Enter new driver name: ";
                                            string newName;
                                            getline(cin, newName);
                                            driverList.updateDriverName(driverId, newName);
                                            break;
                                        }
                                        case 'C': {  // Update Driver Contact Number
                                            cout << "Enter new contact number: ";
                                            string newContact;
                                            getline(cin, newContact);
                                            driverList.updateDriverContact(driverId, newContact);
                                            break;
                                        }
                                        case 'S': {  // Update Driver Status
                                            cout << "Select Status Option:\n";
                                            cout << "1. Available\n2. Delivering\n3. Offline\n";
                                            cin >> statusOption;
                                            cin.ignore();
                                            driverList.updateDriverStatus(driverId, statusOption);
                                            break;
                                        }
                                        
                                        default:
                                            cout << "Invalid choice!\n";
                                            break;
                                    }
                                    
                                    break;

                                }

                                case 'D': {  // Remove Driver
                                            cout << "Are you sure you want to remove this driver? (Y/N): ";
                                            char confirmation;
                                            cin >> confirmation;
                                            cin.ignore();
                                            if (confirmation == 'Y' || confirmation == 'y') {
                                                driverList.removeDriver(driverId);
                                                cout << "Driver removed successfully!" << endl;
                                            } else {
                                                cout << "Driver removal cancelled." << endl;
                                            }
                                            break;
                                        }


                                case 'B':  // Back
                                    break;

                                default:
                                    cout << "Invalid choice!\n";
                                    break;
                            }
                            
                        }
                        
                        break;
                    }

                    }
                }
                break;
            }

            case 'X':{
                break;
            }

            default: {
                cout << "Invalid choice! Please try again.\n";
                break;
            }
        }
    }  
}