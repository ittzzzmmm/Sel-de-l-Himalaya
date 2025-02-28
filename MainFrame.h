#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/mstream.h>
#include <wx/grid.h>
#include <wx/msgdlg.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include "List.h" // assuming this defines the struct/class List

class MainFrame : public wxFrame {
public:
    MainFrame();
    // switch panel rapid
    void SwitchPanel(wxPanel* newPanel);

    // Updated function declarations with tableNumber parameters where needed
    void ShowRole();
    void BookTable();
    void ShowLogin();
    void ShowEmployeeSystem();
    void ShowManageTables();
    void ShowManageMenu();
    void ShowAddPanel();
    void ShowRemovePanel();
    void ShowTableToOrderMenu();

    // These functions now accept the table number as parameter
    int tableCount;
    int numTables;
    void LoadTableData();
    void ShowOrderFood(int tableNumber);
    void CalculateTotal(int tableNumber);

    void ShowDataTable();
    void DeleteListBox();


private:
    wxPanel* currentPanel;
    std::vector<wxButton*> buttons;

    // Data structure to store orders per table.
    // Key: table number; Value: vector of List items (each order item)
    std::map<int, std::vector<List>> tableOrders;

    std::vector<wxString> names;
    std::vector<wxString> details;

    std::vector<std::vector<std::tuple<std::string, std::string, std::string>>> tableDetails;
    std::vector<bool> tableBooked;

};

#endif // MAINFRAME_H