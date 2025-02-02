#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;

void import_menu(vector<string> &menu_tag,vector<string> &menu_name,vector<float> &menu_price){
    string temp;
    ifstream list1("Itt_menu_tag.txt");
    while(getline(list1,temp)){
        menu_tag.push_back(temp);}
    list1.close();

    ifstream list2("Itt_menu_name.txt");
    while(getline(list2,temp)){
        menu_name.push_back(temp);}
    list2.close();

    ifstream list3("Itt_menu_price.txt");
    while(getline(list3,temp)){
        menu_price.push_back(stof(temp));}
    list3.close();
}

void menu_update(vector<string> &menu_tag, vector<string> &menu_name, vector<float> &menu_price){
    int N = menu_tag.size();

    ofstream tag("Itt_menu_tag.txt");
    for(int i = 0; i<N; i++){tag << menu_tag[i] << endl ;}
    tag.close();

    ofstream name("Itt_menu_name.txt");
    for(int i = 0; i<N; i++){name << menu_name[i] << endl ;}
    name.close();

    ofstream price("Itt_menu_price.txt");
    for(int i = 0; i<N; i++){price << menu_price[i] << endl ;}
    price.close();

}

void show_menu(vector<string> &menu_tag, vector<string> &menu_name, vector<float> &menu_price){
    cout<<setw(8)<<"tag"<<setw(20)<<"name"<<setw(8)<<"price"<<endl<<endl;
    for(int i=0; i<menu_tag.size(); i++){
        cout<<setw(8)<<menu_tag[i]<<setw(20)<<menu_name[i]<<setw(8)<<menu_price[i]<<endl;
    }
}

int main(){

    vector<string> menu_tag;
    vector<string> menu_name;
    vector<float> menu_price;

    import_menu(menu_tag,menu_name,menu_price); // ได้ array menu

    do{
        cout << "----------------------------------------\n\n";
        cout << "What would you like to do.\n\n";
        cout << "[1] add menu\n";
        cout << "[2] remove menu\n";
        cout << "[3] show menu\n";
        cout << "[4] Exit\n\n";
        cout << "Select : " ;
        int action;
        cin >> action ;
        cout << "----------------------------------------\n";

        if(action==1){
            string tag = "";
            string name = "";
            float price ;
            cout << "Please enter the menu tag : ";
            cin >> tag ;
            cout << "Please enter the menu name : ";
            cin.ignore();
            getline(cin,name);
            cout << "Please enter the menu price : ";
            cin >> price ;
            menu_tag.push_back(tag); menu_name.push_back(name);menu_price.push_back(price); 
            menu_update(menu_tag,menu_name,menu_price);
            cout << "----------------------------------------\n";
            cout << "*** menu updated ***" << endl;
        }
        else if(action==2){
            show_menu(menu_tag,menu_name,menu_price); 
            cout << "----------------------------------------\n";
            cout << "Please enter the menu tag of the menu that you would like to remove : ";
            string temp2;
            cin>>temp2;
            for(int i2=0; i2<menu_tag.size();i2++){
                if(temp2==menu_tag[i2]){
                    menu_tag.erase(menu_tag.begin()+i2);
                    menu_name.erase(menu_name.begin()+i2);
                    menu_price.erase(menu_price.begin()+i2);
                }
            }
            menu_update(menu_tag,menu_name,menu_price);
            cout << "----------------------------------------\n";
            cout << "*** menu updated ***" << endl;
        }
        else if(action==3){
            show_menu(menu_tag,menu_name,menu_price); 
        }
        else if(action==4){break;}
        else{cout << "Please try again\n";}

    }while(1);

}