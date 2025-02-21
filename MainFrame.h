#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <vector>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/msgdlg.h>
#include <map>

class MainFrame : public wxFrame {
public:
    MainFrame();
    void ShowLogin();
    void ShowEmployeeSystem();
    void ShowRole();
    void ShowOrderFood();
    void ShowManageMenu();
    void BookTable();
    void ShowOrderMenu();
    void CalculateTotal();

private:
    wxPanel* currentPanel;
    std::vector<wxButton*> buttons;
    std::vector<bool> tableBooked;
};

#endif // MAINFRAME_H