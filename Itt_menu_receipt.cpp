#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;

void import_price(vector<int> &Itt_menu_tag){
    ifstream list("menu_tag.txt");
    string temp;
    while(getline(list,temp)){
        Itt_menu_tag.push_back(stof(temp));}
    list.close();
}


void import_menu(vector<string> &Itt_menu_name){
    ifstream list("menu_original.txt");
    string temp;
    while(getline(list,temp)){
        Itt_menu_name.push_back(temp);}
    list.close();
}

int main(){

    vector<int> Itt_menu_tag;
    vector<string> Itt_menu_name;
    vector<float> Itt_menu_price;
    
    import_menu(Itt_menu_name); // เราได้ array ของ menu_name เเล้ว
    cout << Itt_menu_name[0]<<" "<< Itt_menu_name[1]<<" "<< Itt_menu_name[2];    
}