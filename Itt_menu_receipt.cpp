#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;

void import_price(vector<int> &menu_tag){
    ifstream list("menu_tag.txt");
    string temp;
    while(getline(list,temp)){
        menu_tag.push_back(stof(temp));}
    list.close();
}


void import_menu(vector<string> &menu_name){
    ifstream list("menu_original.txt");
    string temp;
    while(getline(list,temp)){
        menu_name.push_back(temp);}
    list.close();
}

int main(){

    vector<int> menu_tag;
    vector<string> menu_name;
    vector<float> menu_price;
    
    import_menu(menu_name); // เราได้ array ของ menu_name เเล้ว
    cout << menu_name[0]<<" "<< menu_name[1]<<" "<< menu_name[2];    
}