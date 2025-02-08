#include <iostream>
#include <string>

using namespace std;

const int NUM_USERS = 4;
const int NUM_FIELDS = 2; // username, password

struct Table {
    bool isReserved;
    string* orders;
    int orderCount;
};

string users[NUM_USERS][NUM_FIELDS] = {
    {"Gear", "P'Donut"},
    {"Tie", "Bit"},
    {"Ohm", "Nurs"},
    {"Itz", "Ponia"}
};

const int MAX_ORDERS = 100;
const string MENU[] = {"Fried Rice", "Tom Yum Soup", "Papaya Salad", "Pad Thai", "Green Curry"};
const int MENU_SIZE = sizeof(MENU) / sizeof(MENU[0]);

Table* tables;
int tableCount;
bool tablesInitialized = false;  // Ensure setupTables() runs only once

bool loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < NUM_USERS; i++) {
        if (users[i][0] == username && users[i][1] == password) {
            cout << "Login successful! Welcome, " << username << ".\n";
            return true;
        }
    }

    cout << "Invalid username or password.\n";
    return false;
}

void setupTables() {
    if (tablesInitialized) return; // Prevent multiple initializations

    cout << "Enter the number of tables in the restaurant: ";
    cin >> tableCount;

    tables = new Table[tableCount];
    for (int i = 0; i < tableCount; i++) {
        tables[i].isReserved = false;
        tables[i].orders = new string[MAX_ORDERS];
        tables[i].orderCount = 0;
    }

    tablesInitialized = true;
    cout << "Successfully set up " << tableCount << " tables!\n";
}

void displayTables() {
    cout << "\n=== Table Status ===\n";
    for (int i = 0; i < tableCount; i++) {
        cout << "Table " << i + 1 << ": " << (tables[i].isReserved ? "Reserved" : "Available") << "\n";
        if (tables[i].isReserved && tables[i].orderCount > 0) {
            cout << "  - Ordered Food: ";
            for (int j = 0; j < tables[i].orderCount; j++) {
                cout << tables[i].orders[j] << ", ";
            }
            cout << "\n";
        }
    }
}

void displayMenu() {
    cout << "\n=== Food Menu ===\n";
    for (int i = 0; i < MENU_SIZE; i++) {
        cout << i + 1 << ". " << MENU[i] << "\n";
    }
}

void orderFood(int tableNumber) {
    if (tableNumber < 1 || tableNumber > tableCount || !tables[tableNumber - 1].isReserved) {
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
            int index = tableNumber - 1;
            tables[index].orders[tables[index].orderCount] = MENU[foodChoice - 1];
            tables[index].orderCount++;
            cout << "Added: " << MENU[foodChoice - 1] << "!\n";
        }
        cout << "Enter the menu number to order (0 to finish): ";
    }
}

void bookTable() {
    int tableNumber;
    cout << "Enter the table number to book (1-" << tableCount << "): ";
    cin >> tableNumber;

    if (tableNumber < 1 || tableNumber > tableCount) {
        cout << "Invalid table number!\n";
        return;
    }

    if (tables[tableNumber - 1].isReserved) {
        cout << "This table is already reserved!\n";
    } else {
        tables[tableNumber - 1].isReserved = true;
        tables[tableNumber - 1].orderCount = 0;
        cout << "Table " << tableNumber << " has been reserved!\n";

        orderFood(tableNumber);
    }
}

void cancelBooking() {
    int tableNumber;
    cout << "Enter the table number to cancel (1-" << tableCount << "): ";
    cin >> tableNumber;

    if (tableNumber < 1 || tableNumber > tableCount) {
        cout << "Invalid table number!\n";
        return;
    }

    if (!tables[tableNumber - 1].isReserved) {
        cout << "This table is not reserved!\n";
    } else {
        tables[tableNumber - 1].isReserved = false;
        tables[tableNumber - 1].orderCount = 0;
        cout << "Table " << tableNumber << " reservation has been canceled!\n";
    }
}

void cleanupTables() {
    for (int i = 0; i < tableCount; i++) {
        delete[] tables[i].orders;
    }
    delete[] tables;
}

void showMenu() {
    cout << "\n=== Restaurant Table Reservation System ===\n";
    cout << "1. View Table Status\n";
    cout << "2. Book a Table (with food ordering)\n";
    cout << "3. Cancel a Reservation\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

void customerMenu() {
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

void employeeMenu() {
    if (!loginUser()) return;
    
    int empChoice;
    do {
        cout << "\n=== Employee Menu ===\n";
        cout << "1. Set Up Tables\n";
        cout << "2. View Table Status\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> empChoice;

        switch (empChoice) {
            case 1:
                setupTables();
                break;
            case 2:
                displayTables();
                break;
            case 3:
                cout << "Exiting Employee Menu...\n";
                break;
            default:
                cout << "Please choose a valid option!\n";
        }
    } while (empChoice != 3);
}

int main() {
    int userType;

    do {
        cout << "\n=== Restaurant Table Reservation System ===\n";
        cout << "1. Customer \n";
        cout << "2. Employee Login\n";
        cout << "3. Exit\n";
        cout << "Select user type: ";
        cin >> userType;

        if (userType == 1) { 
            customerMenu();
        } else if (userType == 2) {
            employeeMenu();
        }
    } while (userType != 3);

    cleanupTables();
    return 0;
}
