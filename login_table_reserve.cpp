#include <iostream> 
using namespace std;

const int MAX_TABLES = 100; // กำหนดจำนวนโต๊ะสูงสุด
bool tables[MAX_TABLES] = {false}; // อาร์เรย์เก็บสถานะของโต๊ะ (true = ถูกจอง, false = ว่าง)
int numTables; // ตัวแปรเก็บจำนวนโต๊ะที่มีในร้าน

// ฟังก์ชันสำหรับจองโต๊ะ
void bookTable(int tableNumber) {
    if (tableNumber < 1 || tableNumber > numTables) { // ตรวจสอบว่าเลขโต๊ะที่รับเข้ามาอยู่ในช่วงที่ถูกต้องหรือไม่
        cout << "Invalid table number!" << endl;
        return;
    }
    
    if (!tables[tableNumber - 1]) { // ถ้าโต๊ะยังว่าง ให้ทำการจอง เช็คจาก!คือถ้าโต๊ะเป้น false คำสั่งใน{}จะทำงาน
        tables[tableNumber - 1] = true;
        cout << "Table " << tableNumber << " has been reserved." << endl;
    } else { // ถ้าโต๊ะถูกจองไปแล้ว แจ้งเตือนผู้ใช้
        cout << "Table " << tableNumber << " is already reserved!" << endl;
    }
}

// ฟังก์ชันสำหรับแสดงสถานะของโต๊ะทั้งหมด
void displayTables() {
    cout << "Table Status:" << endl;
    for (int i = 0; i < numTables; i++) {
        cout << "Table " << (i + 1) << ": " << (tables[i] ? "Reserved" : "Available") << endl; // (condition) ? value_if_true : value_if_false;
    }
}

int main() {
    int userType; 
    while (true) { //ทำงานตลอดจนกว่า จะเจอ break หรือ return :D
        cout << "Are you an Employee (1) or a Customer (2)? "; 
        cin >> userType;
        
        if (userType == 1) { // ถ้าเป็นพนักงานต้องใส่รหัสผ่าน
            string password;
            cout << "Enter password: ";
            cin >> password;
            if (password != "pleumkuylek") { // ตรวจสอบรหัสผ่าน ถ้าผิดให้ลองใหม่ 
                cout << "Incorrect password! Try again." << endl;
                continue; // วนไปถามใหม่
            }
            cout << "Access granted as Employee." << endl;

// สามารถ ใส่ฟังชันเพิ่มได้เเถวๆนี้เด้อเฮีย :3


        } else if (userType == 2) { // ถ้าเป็นลูกค้าก็ข้ามไปที่ระบบจองโต๊ะได้เลย
            break;
        } else { // ถ้าผู้ใช้ใส่ค่าที่ไม่ถูกต้อง ให้ลองใหม่
            cout << "Invalid selection! Try again." << endl;
            continue; //วนไปถามใหม่
        }
        break;
    }
    
    cout << "Enter number of tables: "; // ให้ผู้ใช้กำหนดจำนวนโต๊ะในร้าน
    cin >> numTables;
    
    int choice, tableNumber; // ตัวแปรเก็บตัวเลือกเมนู และหมายเลขโต๊ะที่ต้องการจอง
    do {
        cout << "\n1. Book a Table" << endl; // เมนูจองโต๊ะ
        cout << "2. Show Tables" << endl; // เมนูแสดงสถานะโต๊ะ
        cout << "3. Exit" << endl; // เมนูออกจากโปรแกรม
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter table number to book: "; // ขอให้ผู้ใช้ป้อนหมายเลขโต๊ะที่ต้องการจอง
                cin >> tableNumber;
                bookTable(tableNumber); // เรียกใช้ฟังก์ชันจองโต๊ะ
                break;
            case 2:
                displayTables(); // เรียกใช้ฟังก์ชันแสดงสถานะโต๊ะ
                break;
            case 3:
                cout << "Exiting program..." << endl; // ออกจากโปรแกรม
                break;
            default:
                cout << "Invalid choice!" << endl; // แจ้งเตือนหากผู้ใช้เลือกเมนูผิด
        }
    } while (choice != 3); // ทำซ้ำจนกว่าผู้ใช้จะเลือกออกจากโปรแกรม
    
    return 0;
}
