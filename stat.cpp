#include <iostream>
#include <string>
#include <iomanip> // สำหรับจัดรูปแบบการแสดงผล

using namespace std;

int main() {
    // เมนูอาหาร (ใช้ array หลายมิติ เพื่อจัดกลุ่มข้อมูลที่เกี่ยวข้อง)
    string menu[3][4] = {
        {"1", "ข้าวผัดกะเพรา", "อาหาร", "50.0"},
        {"2", "ต้มยำกุ้ง", "อาหาร", "80.0"},
        {"3", "น้ำอัดลม", "เครื่องดื่ม", "20.0"}
    };
    int menuSize = sizeof(menu) / sizeof(menu[0]); // คำนวณขนาดอัตโนมัติ

    // ออเดอร์ (ใช้ array หลายมิติ เพื่อจัดกลุ่มข้อมูลที่เกี่ยวข้อง)
    string orders[2][5] = {
        {"1", "2024-05-16", "12:00", "1", "2"},
        {"2", "2024-05-16", "12:00", "3", "1"}
    };
    int orderSize = sizeof(orders) / sizeof(orders[0]); // คำนวณขนาดอัตโนมัติ

    // ตัวแปรเก็บสถิติ
    double totalSales = 0.0;
    int bestSellerId = 0, maxSold = 0;
    int soldCount[menuSize] = {0}; // เก็บจำนวนที่ขายของแต่ละเมนู

    // คำนวณยอดขาย
    for (int i = 0; i < orderSize; i++) { // Loop นอก วนซ้ำตามจำนวนออเดอร์ทั้งหมด
        for (int j = 0; j < menuSize; j++) { // Loop ใน วนซ้ำตามจำนวนเมนูทั้งหมด
            if (orders[i][3] == menu[j][0]) { // ตรวจสอบว่าเมนูในออเดอร์ตรงกับเมนูใดในเมนูทั้งหมด
                totalSales += stod(menu[j][3]) * stoi(orders[i][4]); // คำนวณยอดขายของเมนูนั้นๆ
                soldCount[j] += stoi(orders[i][4]); // เพิ่มจำนวนที่ขายของเมนูนั้นๆ
                if (soldCount[j] > maxSold) { // ตรวจสอบว่าเมนูนี้ขายดีที่สุดหรือไม่
                    maxSold = soldCount[j]; // อัพเดทจำนวนที่ขายดีที่สุด
                    bestSellerId = stoi(menu[j][0]); // อัพเดท ID ของเมนูที่ขายดีที่สุด
                }
        }
    }
}

    // แสดงผล
    
    cout << "ยอดขายรวมทั้งหมด: " << totalSales << " บาท" << endl;

    // แสดงเมนูขายดีที่สุด
    for (int i = 0; i < menuSize; i++) {
        if (stoi(menu[i][0]) == bestSellerId) {
            cout << "เมนูขายดีที่สุด: " << menu[i][1] << " (" << maxSold << " จาน)" << endl;
        }
    }

    return 0;
}