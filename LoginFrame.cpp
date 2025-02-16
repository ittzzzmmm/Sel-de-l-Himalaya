#include "LoginFrame.h"
#include "CustomerSystem.h"
#include "EmployeeSystem.h"

LoginFrame::LoginFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    usernameCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30));
    passwordCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30), wxTE_PASSWORD);
    loginButton = new wxButton(panel, wxID_ANY, "Login");
    registerButton = new wxButton(panel, wxID_ANY, "Register");

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Username:"), 0, wxALL, 5);
    sizer->Add(usernameCtrl, 0, wxALL, 5);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "Password:"), 0, wxALL, 5);
    sizer->Add(passwordCtrl, 0, wxALL, 5);
    sizer->Add(loginButton, 0, wxALL | wxCENTER, 5);
    sizer->Add(registerButton, 0, wxALL | wxCENTER, 5);

    panel->SetSizer(sizer);

    loginButton->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);
    registerButton->Bind(wxEVT_BUTTON, &LoginFrame::OnRegister, this);
}

void LoginFrame::OnLogin(wxCommandEvent& event) {
    wxString username = usernameCtrl->GetValue();
    wxString password = passwordCtrl->GetValue();

    if (ValidateLogin(username, password)) {
        wxMessageBox("Login Successful", "Success", wxOK | wxICON_INFORMATION);
        CustomerSystem* customerFrame = new CustomerSystem("Customer System");
        customerFrame->Show(true);
        this->Close();
    }
    else {
        wxMessageBox("Invalid username or password", "Error", wxOK | wxICON_ERROR);
    }
}

void LoginFrame::OnRegister(wxCommandEvent& event) {
    wxString username = usernameCtrl->GetValue();
    wxString password = passwordCtrl->GetValue();
    RegisterUser(username, password);
    wxMessageBox("Registration Successful", "Success", wxOK | wxICON_INFORMATION);
}

bool LoginFrame::ValidateLogin(const wxString& username, const wxString& password) {
    std::ifstream file("users.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string storedUser, storedPass;
        if (iss >> storedUser >> storedPass) {
            if (storedUser == username.ToStdString() && storedPass == password.ToStdString()) {
                return true;
            }
        }
    }
    return false;
}

void LoginFrame::RegisterUser(const wxString& username, const wxString& password) {
    std::ofstream file("users.txt", std::ios::app);
    file << username.ToStdString() << " " << password.ToStdString() << "\n";
}
