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

    cout << "Menu Items:\n";

    int i = 0;
    int j = 0;
    while(i < count){
        cout << j + 1 << ". " << menu[i] << " " << price[i] << " Bath\n";
        j++;
        i = i + 2;
    }
    

    return 0;
}

	
	
