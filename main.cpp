#include <wx/wx.h>
#include <vector>

class BookingDialog : public wxDialog {
public:
    BookingDialog(wxWindow* parent, std::vector<bool>& tables);
private:
    void OnBook(wxCommandEvent& event);
    std::vector<bool>& tables;
    wxTextCtrl* tableInput;
    wxTextCtrl* output;
};

class TableBookingApp : public wxApp {
public:
    virtual bool OnInit();
};

class TableBookingFrame : public wxFrame {
public:
    TableBookingFrame(const wxString& title);
private:
    void OnOpenBooking(wxCommandEvent& event);
    void OnShowTables(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);

    std::vector<bool> tables;
    int numTables;

    wxTextCtrl* tableCountInput;
    wxTextCtrl* output;
};

wxIMPLEMENT_APP(TableBookingApp);

bool TableBookingApp::OnInit() {
    TableBookingFrame* frame = new TableBookingFrame("Table Booking System");
    frame->Show(true);
    return true;
}

BookingDialog::BookingDialog(wxWindow* parent, std::vector<bool>& tables)
    : wxDialog(parent, wxID_ANY, "Book a Table", wxDefaultPosition, wxSize(300, 200)), tables(tables) {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    tableInput = new wxTextCtrl(this, wxID_ANY);
    wxButton* bookButton = new wxButton(this, wxID_ANY, "Book");
    output = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

    sizer->Add(new wxStaticText(this, wxID_ANY, "Enter table number:"), 0, wxALL, 5);
    sizer->Add(tableInput, 0, wxEXPAND | wxALL, 5);
    sizer->Add(bookButton, 0, wxEXPAND | wxALL, 5);
    sizer->Add(output, 1, wxEXPAND | wxALL, 5);

    SetSizer(sizer);
    bookButton->Bind(wxEVT_BUTTON, &BookingDialog::OnBook, this);
}

void BookingDialog::OnBook(wxCommandEvent& event) {
    long tableNumber;
    if (tableInput->GetValue().ToLong(&tableNumber) && tableNumber >= 1 && tableNumber <= tables.size()) {
        if (!tables[tableNumber - 1]) {
            tables[tableNumber - 1] = true;
            output->AppendText("Table " + std::to_string(tableNumber) + " has been reserved.\n");
        }
        else {
            output->AppendText("Table " + std::to_string(tableNumber) + " is already reserved!\n");
        }
    }
    else {
        output->AppendText("Invalid table number!\n");
    }
}

TableBookingFrame::TableBookingFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    tableCountInput = new wxTextCtrl(panel, wxID_ANY);
    wxButton* setTableButton = new wxButton(panel, wxID_ANY, "Set Number of Tables");
    wxButton* bookButton = new wxButton(panel, wxID_ANY, "Book a Table");
    wxButton* showButton = new wxButton(panel, wxID_ANY, "Show Tables");
    wxButton* exitButton = new wxButton(panel, wxID_ANY, "Exit");
    output = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

    sizer->Add(new wxStaticText(panel, wxID_ANY, "Enter number of tables:"), 0, wxALL, 5);
    sizer->Add(tableCountInput, 0, wxEXPAND | wxALL, 5);
    sizer->Add(setTableButton, 0, wxEXPAND | wxALL, 5);
    sizer->Add(bookButton, 0, wxEXPAND | wxALL, 5);
    sizer->Add(showButton, 0, wxEXPAND | wxALL, 5);
    sizer->Add(exitButton, 0, wxEXPAND | wxALL, 5);
    sizer->Add(output, 1, wxEXPAND | wxALL, 5);

    panel->SetSizer(sizer);

    setTableButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
        long num;
        if (tableCountInput->GetValue().ToLong(&num) && num > 0) {
            numTables = static_cast<int>(num);
            tables.assign(numTables, false);
            output->AppendText("Number of tables set to " + std::to_string(numTables) + "\n");
        }
        else {
            output->AppendText("Invalid number of tables!\n");
        }
        });

    bookButton->Bind(wxEVT_BUTTON, &TableBookingFrame::OnOpenBooking, this);
    showButton->Bind(wxEVT_BUTTON, &TableBookingFrame::OnShowTables, this);
    exitButton->Bind(wxEVT_BUTTON, &TableBookingFrame::OnExit, this);
}

void TableBookingFrame::OnOpenBooking(wxCommandEvent& event) {
    BookingDialog dlg(this, tables);
    dlg.ShowModal();
}

void TableBookingFrame::OnShowTables(wxCommandEvent& event) {
    output->AppendText("Table Status:\n");
    for (int i = 0; i < numTables; i++) {
        output->AppendText("Table " + std::to_string(i + 1) + ": " + (tables[i] ? "Reserved\n" : "Available\n"));
    }
}

void TableBookingFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}
