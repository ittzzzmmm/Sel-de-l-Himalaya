#include <iostream>
using namespace std;

int main() {
    int choice , pt = 0 , tyk = 0 , pkp = 0 , fc = 0 , sum = 0;
    string menu[] = {"Padthai" , "Tomyumkung" , "Padkrapao" , "Fired Chicken"};

    do {
        cout << "==================================" << endl;
        cout << "             MAIN MENU            " << endl;
        cout << "==================================" << endl;
        cout << "1. Padthai 20 bath" << endl;
        cout << "2. Tomyumkung 50 bath" << endl;
        cout << "3. Padkrapao 40 bath" << endl;
        cout << "4. Fried Chicken 30 bath" << endl;
        cout << "5. Exit" << endl;
        cout << "==================================" << endl;
        cout << "Enter your choice (1-5): ";
        
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "You chose " << menu[0] << "." << endl;
                cout << "\n";
                pt++;
                break;
            case 2:
                cout << "You chose " << menu[1] << "." << endl;
                cout << "\n";
                tyk++;
                break;
            case 3:
                cout << "You chose " << menu[2] << "." << endl;
                cout << "\n";
                pkp++;
                break;
            case 4:
                cout << "You chose " << menu[3] << "." << endl;
                cout << "\n";
                fc++;
                break;
            case 5:
                sum = (pt*20) + (tyk*50) + (pkp*40) + (fc*30);
                cout << "\n";
                cout << "The price will be " << sum << " bath , Thanks for your order." << endl;
                break;
            default:
                //cout << choice;
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cin.get();

    } while (choice != 5);

    return 0;
}
