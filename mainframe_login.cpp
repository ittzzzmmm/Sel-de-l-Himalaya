#include "MainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this);

    wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, "Name", wxPoint(285, 270));
    wxTextCtrl* textCtrl1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(350, 270), wxSize(200, -1));

    wxStaticText* staticText2 = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(285, 300));
    wxTextCtrl* textCtrl2 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(350, 300), wxSize(200, -1), wxTE_PASSWORD);
}
