#include "EmployeeSystem.h"

EmployeeSystem::EmployeeSystem(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxButton* manageOrdersButton = new wxButton(panel, wxID_ANY, "Manage Orders");
    wxButton* calculateBillButton = new wxButton(panel, wxID_ANY, "Calculate Bill");

    sizer->Add(manageOrdersButton, 0, wxALL | wxCENTER, 5);
    sizer->Add(calculateBillButton, 0, wxALL | wxCENTER, 5);

    panel->SetSizer(sizer);
}
