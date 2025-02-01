#include <iostream>
#include <string>
#include <iomanip> // สำหรับจัดรูปแบบการแสดงผล
#include <limits> // สำหรับ numeric_limits

using namespace std;

const int MAX_MENU_ITEMS = 100;

int main() {
    string menuName[MAX_MENU_ITEMS];
    double menuPrice[MAX_MENU_ITEMS];
    int soldCount[MAX_MENU_ITEMS] = {0}; // เริ่มต้นจำนวนขายเป็น 0
    int menuSize = 0; // จำนวนรายการอาหารปัจจุบัน

    double totalSales = 0.0;
    int bestSellerId = 0, maxSold = 0;

    while (true) {
        cout << "\n--- เพิ่มรายการอาหาร ---" << endl;
        string name;
        double price;

        cout << "ชื่ออาหาร (หรือพิมพ์ 'หยุด' เพื่อสิ้นสุด): ";
        getline(cin >> ws, name); // อ่านชื่ออาหารรวมช่องว่าง

        if (name == "หยุด") {
            break; // ออกจาก loop ถ้าผู้ใช้พิมพ์ "หยุด"
        }

        cout << "ราคา: ";
        cin >> price;

        // ตรวจสอบว่าราคาเป็นตัวเลขที่ถูกต้อง
        if (cin.fail()) {
            cout << "ราคากรอกไม่ถูกต้อง กรุณาลองอีกครั้ง" << endl;
            cin.clear(); // ล้างค่า error ใน cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
            continue;
        }

        if (menuSize < MAX_MENU_ITEMS) {
            menuName[menuSize] = name;
            menuPrice[menuSize] = price;
            menuSize++;
        } else {
            cout << "รายการอาหารเต็มแล้ว ไม่สามารถเพิ่มได้อีก" << endl;
        }
    }

    while (true) {
        cout << "\n--- สั่งอาหาร ---" << endl;
        int orderMenuId;
        int quantity;

        // แสดงเมนูให้ผู้ใช้เลือก
        for (int i = 0; i < menuSize; i++) {
            cout << i + 1 << ". " << menuName[i] << " (" << menuPrice[i] << " บาท)" << endl;
        }

        cout << "ID อาหารที่ต้องการ (หรือพิมพ์ 0 เพื่อสิ้นสุด): ";
        cin >> orderMenuId;

        if (orderMenuId == 0) {
            break; // ออกจาก loop ถ้าผู้ใช้พิมพ์ 0
        }

        if (orderMenuId > menuSize || orderMenuId <= 0) {
            cout << "ID อาหารไม่ถูกต้อง กรุณาลองอีกครั้ง" << endl;
            continue;
        }

        cout << "จำนวน: ";
        cin >> quantity;

        // ตรวจสอบว่าจำนวนเป็นตัวเลขที่ถูกต้อง
        if (cin.fail()) {
            cout << "จำนวนที่สั่งไม่ถูกต้อง กรุณาลองอีกครั้ง" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        int menuIndex = orderMenuId - 1;//เพื่อให้เริ่มที่arr[0]

        totalSales += menuPrice[menuIndex] * quantity;
        soldCount[menuIndex] += quantity;

        if (soldCount[menuIndex] > maxSold) {
            maxSold = soldCount[menuIndex];
            bestSellerId = orderMenuId;
        }
    }

    // แสดงผล
    cout << fixed << setprecision(2);
    cout << "\n--- สรุปผล ---" << endl;
    cout << "ยอดขายรวมทั้งหมด: " << totalSales << " บาท" << endl;

    if (maxSold > 0) {
        cout << "เมนูขายดีที่สุด: " << menuName[bestSellerId - 1] << " (" << maxSold << " จาน)" << endl;
    } else {
        cout << "ยังไม่มีการสั่งซื้อ" << endl;
    }

    // แสดงรายการอาหารที่ขายได้และขายไม่ได้
    cout << "\n--- รายการอาหาร ---" << endl;
    for (int i = 0; i < menuSize; i++) {
        cout << menuName[i] << " (" << menuPrice[i] << " บาท): ";
        if (soldCount[i] > 0) {
            cout << "ขายได้ (" << soldCount[i] << " จาน)" << endl;
        } else {
            cout << "ขายไม่ได้" << endl;
        }
    }

    return 0;
}