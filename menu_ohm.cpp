#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int N = 100;

int main() {
    string  word[N];
    string menu[N];
    string price[N];
    int show_count = 0;
    int choice, add_count;

    do {
        ifstream source("D:\\project-cpp\\menu_original.txt");
        if (!source) {
            cerr << "Error: Could not open the file.\n";
            return 1;
        }

        show_count = 0;

        while (source >> word[show_count]  && show_count < N) {
            if(show_count%2==0) menu[show_count] = word[show_count];
            else price[show_count-1] = word[show_count];
            show_count++;
        }

        source.close();
        cout << "\nWhat do you want to do?\n";
        cout << "1. Check menu\n";
        cout << "2. Add menu items\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int j = 0;
                cout << "\nMenu Items:\n";
                for (int i = 0; i < show_count; i++) {
                    if(i%2==0){
                        cout << j + 1 << ". " << menu[i] << " " << price[i] << " Bath\n";
                        j++;
                    }
                    else continue;
                }
                break;
            }
            case 2: {
                cout << "How many items do you want to add? ";
                cin >> add_count;

                ofstream desk("D:\\project-cpp\\menu_original.txt", ios::app);
                if (!desk) {
                    cerr << "Error: Could not open the file for writing.\n";
                    return 1;
                }

                for (int i = 0; i < add_count; i++) {
                    string new_menu, new_price;
                    cout << "Enter menu name: ";
                    cin >> ws;
                    getline(cin, new_menu);
                    cout << "Enter price: ";
                    cin >> new_price;
                    desk << new_menu << " " << new_price << endl;
                }
                desk.close();
                cout << "Menu items added successfully\n";
                break;
            }
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
