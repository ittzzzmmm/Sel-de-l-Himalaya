#include <iostream>
#include <string>

using namespace std;

// กำหนดจำนวนบัญชีที่รองรับ
const int NUM_USERS = 4;
const int NUM_FIELDS = 2; // username, password

// สร้างบัญชีที่กำหนดไว้ล่วงหน้า (username, password)
string users[NUM_USERS][NUM_FIELDS] = {
    {"Gear", "P'Donut"},
    {"Tie", "Bit"},
    {"Ohm", "Nurs"},
    {"Itz", "Ponia"}
};

const int TABLE_COUNT = 10;  // Total number of tables
const int MAX_ORDERS = 100;  // Large number to allow unlimited orders

// Food menu
const string MENU[] = {"Fried Rice", "Tom Yum Soup", "Papaya Salad", "Pad Thai", "Green Curry"};
const int MENU_SIZE = sizeof(MENU) / sizeof(MENU[0]);

// Table data
bool tables[TABLE_COUNT] = {false};         // Table status (true = Reserved, false = Available)
string orders[TABLE_COUNT][MAX_ORDERS];     // Orders per table
int orderCount[TABLE_COUNT] = {0};          // Number of orders per table

// ฟังก์ชันล็อกอิน
void loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // ตรวจสอบว่าชื่อผู้ใช้และรหัสผ่านถูกต้องหรือไม่
    bool found = false;
    for (int i = 0; i < NUM_USERS; i++) {
        if (users[i][0] == username && users[i][1] == password) {
            found = true;
            cout << "Login successful! Welcome, " << username << ".\n";
            break;
        }
    }

    if (!found) {
        cout << "Invalid username or password.\n";
    }
}

// Function to display table status
void displayTables() {
    cout << "\n=== Table Status ===\n";
    for (int i = 0; i < TABLE_COUNT; i++) {
        cout << "Table " << i + 1 << ": " << (tables[i] ? "Reserved" : "Available") << "\n";
        if (tables[i] && orderCount[i] > 0) {
            cout << "  - Ordered Food: ";
            for (int j = 0; j < orderCount[i]; j++) {
                cout << orders[i][j] << ", ";
            }
            cout << "\n";
        }
    }
}

// Function to display the food menu
void displayMenu() {
    cout << "\n=== Food Menu ===\n";
    for (int i = 0; i < MENU_SIZE; i++) {
        cout << i + 1 << ". " << MENU[i] << "\n";
    }
}

// Function to order food for a table
void orderFood(int tableNumber) {
    if (tableNumber < 1 || tableNumber > TABLE_COUNT || !tables[tableNumber - 1]) {
        cout << "Invalid table number or table is not reserved!\n";
        return;
    }

    displayMenu();

    int foodChoice;
    cout << "Enter the menu number to order (0 to finish): ";
    while (true) {
        cin >> foodChoice;
        if (foodChoice == 0) break;

        if (foodChoice < 1 || foodChoice > MENU_SIZE) {
            cout << "Invalid menu number!\n";
        } else {
            orders[tableNumber - 1][orderCount[tableNumber - 1]] = MENU[foodChoice - 1];
            orderCount[tableNumber - 1]++;
            cout << "Added: " << MENU[foodChoice - 1] << "!\n";
        }
        cout << "Enter the menu number to order (0 to finish): ";
    }
}

// Function to book a table
void bookTable() {
    int tableNumber;
    cout << "Enter the table number to book (1-" << TABLE_COUNT << "): ";
    cin >> tableNumber;

    if (tableNumber < 1 || tableNumber > TABLE_COUNT) {
        cout << "Invalid table number!\n";
        return;
    }

    if (tables[tableNumber - 1]) {
        cout << "This table is already reserved!\n";
    } else {
        tables[tableNumber - 1] = true;
        orderCount[tableNumber - 1] = 0; // Reset food orders
        cout << "Table " << tableNumber << " has been reserved!\n";

        // Automatically proceed to order food
        cout << "Now, let's order food for Table " << tableNumber << ".\n";
        orderFood(tableNumber);
    }
}

// Function to cancel a table reservation
void cancelBooking() {
    int tableNumber;
    cout << "Enter the table number to cancel (1-" << TABLE_COUNT << "): ";
    cin >> tableNumber;

    if (tableNumber < 1 || tableNumber > TABLE_COUNT) {
        cout << "Invalid table number!\n";
        return;
    }

    if (!tables[tableNumber - 1]) {
        cout << "This table is not reserved!\n";
    } else {
        tables[tableNumber - 1] = false;
        orderCount[tableNumber - 1] = 0; // Clear food orders
        cout << "Table " << tableNumber << " reservation has been canceled!\n";
    }
}

// Function to show the main menu
void showMenu() {
    cout << "\n=== Restaurant Table Reservation System ===\n";
    cout << "1. View Table Status\n";
    cout << "2. Book a Table (with food ordering)\n";
    cout << "3. Cancel a Reservation\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}
// Main function
void mainmenu(){
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                displayTables();
                break;
            case 2:
                bookTable();
                break;
            case 3:
                cancelBooking();
                break;
            case 4:
                cout << "Thank you for using our service!\n";
                break;
            default:
                cout << "Please choose a valid option!\n";
        }
    } while (choice != 4);
}

int main() {

    int userType;

    do {
        cout << "\n=== Restaurant Table Reservation System ===\n";
        cout << "1. Customer Login\n";
        cout << "2. Employee Login\n";
        cout << "3. Exit\n";
        cout << "Select user type: ";
        cin >> userType;

        if (userType == 1) { // Customer
            mainmenu();
        } else if (userType == 2) { // Employee
            loginUser();
        }
    } while (userType != 3);
    
    return 0;
}
