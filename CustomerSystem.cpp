#include "CustomerSystem.h"

CustomerSystem::CustomerSystem(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxButton* bookTableButton = new wxButton(panel, wxID_ANY, "Book Table");
    wxButton* orderFoodButton = new wxButton(panel, wxID_ANY, "Order Food");
    wxButton* viewBillButton = new wxButton(panel, wxID_ANY, "View Bill");

    sizer->Add(bookTableButton, 0, wxALL | wxCENTER, 5);
    sizer->Add(orderFoodButton, 0, wxALL | wxCENTER, 5);
    sizer->Add(viewBillButton, 0, wxALL | wxCENTER, 5);

    panel->SetSizer(sizer);
}
