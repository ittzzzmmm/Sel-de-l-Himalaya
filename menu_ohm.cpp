#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int N = 100;
const string filename = "D:\\project-cpp\\menu_original.txt";

void displayMenu(string menu[], string price[], int count) {
    cout << "\nMenu Items:\n";
    for (int i = 0, j = 1; i < count; i += 2, j++) {
        cout << j << ". " << menu[i] << " " << price[i] << " Bath\n";
    }
}

void loadMenu(string menu[], string price[], int &count, const string &filename) {
    ifstream source(filename);
    if (!source) {
        cerr << "Error: Could not open the file.\n";
        return;
    }

    count = 0;
    string word;

    while (source >> word && count < N) {
        if (count % 2 == 0)
            menu[count] = word;
        else
            price[count - 1] = word;

        count++;
    }

    source.close();
}

void addMenuItems(const string &filename) {
    ofstream desk(filename, ios::app);
    if (!desk) {
        cerr << "Error: Could not open the file for writing.\n";
        return;
    }

    int add_count;
    cout << "How many items do you want to add? ";
    cin >> add_count;
    cin.ignore();

    for (int i = 0; i < add_count; i++) {
        string new_menu, new_price;
        cout << "Enter menu name: ";
        getline(cin, new_menu);
        cout << "Enter price: ";
        getline(cin, new_price);
        desk << new_menu << " " << new_price << endl;
    }
    desk.close();
    cout << "Menu items added successfully.\n";
}

void deleteMenuItem(string menu[], string price[], int &count, const string &filename) {
    displayMenu(menu, price, count);

    int itemNumber;
    cout << "\nEnter the number of the item to delete: ";
    cin >> itemNumber;

    int index = (itemNumber - 1) * 2;
    if (itemNumber < 1 || index >= count) {
        cout << "Invalid item number.\n";
        return;
    }

    // Shift items to remove the selected menu
    for (int i = index; i < count - 2; i += 2) {
        menu[i] = menu[i + 2];
        price[i] = price[i + 2];
    }
    count -= 2;

    // Overwrite the file with updated menu
    ofstream desk(filename);
    if (!desk) {
        cerr << "Error: Could not open the file for writing.\n";
        return;
    }

    for (int i = 0; i < count; i += 2) {
        desk << menu[i] << " " << price[i] << endl;
    }
    desk.close();
    cout << "Menu item deleted successfully.\n";
}

int main() {
    string menu[N], price[N];
    int choice, count = 0;

    do {
        loadMenu(menu, price, count, filename);

        cout << "\nWhat do you want to do?\n";
        cout << "1. Check menu\n";
        cout << "2. Add menu items\n";
        cout << "3. Delete menu item\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                displayMenu(menu, price, count);
                break;
            case 2:
                addMenuItems(filename);
                break;
            case 3:
                deleteMenuItem(menu, price, count, filename);
                break;
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
