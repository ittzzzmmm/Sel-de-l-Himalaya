#include <wx/wx.h>
#include "LoginFrame.h"
#include "CustomerSystem.h"
#include "EmployeeSystem.h"

class RestaurantApp : public wxApp {
public:
    virtual bool OnInit();
};

class MainFrame : public wxFrame {
public:
    MainFrame();
    void ShowLogin();
    void ShowCustomerSystem();
    void ShowEmployeeSystem();

private:
    wxPanel* currentPanel;
};

wxIMPLEMENT_APP(RestaurantApp);

bool RestaurantApp::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Show(true);
    return true;
}

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Restaurant Management System", wxDefaultPosition, wxSize(500, 400)) {
    currentPanel = nullptr;
    ShowLogin();
}

void MainFrame::ShowLogin() {
    if (currentPanel) currentPanel->Destroy();
    currentPanel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxTextCtrl* usernameCtrl = new wxTextCtrl(currentPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30));
    wxTextCtrl* passwordCtrl = new wxTextCtrl(currentPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30), wxTE_PASSWORD);
    wxButton* loginButton = new wxButton(currentPanel, wxID_ANY, "Login");

    sizer->Add(new wxStaticText(currentPanel, wxID_ANY, "Username:"), 0, wxALL, 5);
    sizer->Add(usernameCtrl, 0, wxALL, 5);
    sizer->Add(new wxStaticText(currentPanel, wxID_ANY, "Password:"), 0, wxALL, 5);
    sizer->Add(passwordCtrl, 0, wxALL, 5);
    sizer->Add(loginButton, 0, wxALL | wxCENTER, 5);

    currentPanel->SetSizer(sizer);

    loginButton->Bind(wxEVT_BUTTON, [this, usernameCtrl, passwordCtrl](wxCommandEvent&) {
        wxString username = usernameCtrl->GetValue();
        wxString password = passwordCtrl->GetValue();
        if (username == "customer") {
            ShowCustomerSystem();
        }
        else if (username == "employee" && password == "1234") {
            ShowEmployeeSystem();
        }
        else {
            wxMessageBox("Invalid username or password", "Error", wxOK | wxICON_ERROR);
        }
    });
}

void MainFrame::ShowCustomerSystem() {
    if (currentPanel) currentPanel->Destroy();
    currentPanel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxButton* bookTableButton = new wxButton(currentPanel, wxID_ANY, "Book Table");
    wxButton* orderFoodButton = new wxButton(currentPanel, wxID_ANY, "Order Food");
    wxButton* viewBillButton = new wxButton(currentPanel, wxID_ANY, "View Bill");

    sizer->Add(bookTableButton, 0, wxALL | wxCENTER, 5);
    sizer->Add(orderFoodButton, 0, wxALL | wxCENTER, 5);
    sizer->Add(viewBillButton, 0, wxALL | wxCENTER, 5);

    currentPanel->SetSizer(sizer);
}

void MainFrame::ShowEmployeeSystem() {
    if (currentPanel) currentPanel->Destroy();
    currentPanel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxButton* manageOrdersButton = new wxButton(currentPanel, wxID_ANY, "Manage Orders");
    wxButton* calculateBillButton = new wxButton(currentPanel, wxID_ANY, "Calculate Bill");

    sizer->Add(manageOrdersButton, 0, wxALL | wxCENTER, 5);
    sizer->Add(calculateBillButton, 0, wxALL | wxCENTER, 5);

    currentPanel->SetSizer(sizer);
}

