
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream source("D:\\project-cpp\\menu_original.txt");

    if (!source) {
        cerr << "Error: Could not open the file.\n";
        return 1;
    }

    const int N = 100;
    string lines[N];
    string menu[N];
    string price[N];
    int count = 0;
    int key;

    while (source >> lines[count]  && count < N) {
        if(count%2==0) menu[count] = lines[count];
        else price[count-1] = lines[count];
        count++;
    }

    source.close();

    do {
        cout << "\nWhat do you want to do?\n";
        cout << "1. Check menu\n";
        cout << "2. Edit menu\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> key;

        switch (key) {
            case 1:
                cout << "\nMenu Items:\n";
                for (int i = 0; i < count; i++) {
                    if(i%2==0)cout << i + 1 << ". " << menu[i] << " " << price[i] << " Bath\n";
                    else continue;
                }
                break;

            case 2:
                cout << "Edit menu\n";
                break;

            case 0:
                cout << "Exiting this.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (key != 0);

    return 0;
}
	
	
