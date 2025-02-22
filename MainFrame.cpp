#include "MainFrame.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Restaurant Management System", wxDefaultPosition, wxSize(500, 400))
{
    currentPanel = nullptr;

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(frameSizer);


    tableBooked.resize(numTables, false);
    tableDetails.resize(numTables, { "", "" });

    ShowRole();

    Layout();
}

void MainFrame::ShowRole() {
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxButton* customerButton = new wxButton(currentPanel, wxID_ANY, "Customer");
    wxButton* employeeButton = new wxButton(currentPanel, wxID_ANY, "Employee");

    sizer->Add(customerButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(employeeButton, 0, wxALL | wxALIGN_CENTER, 5);
    currentPanel->SetSizer(sizer);

    customerButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        // แสดงข้อความ "Welcome" เมื่อกดปุ่ม Customer
        wxMessageBox("สถานะโต๊ะที่เห็นคือของปัจจุบัน ถ้าหากต้องการจองโต๊ะที่ไม่ว่างต้องรออย่างน้อย30นาทีโต๊ะถึงจะว่าง", "Welcome", wxOK | wxICON_INFORMATION, this);
        BookTable();
        });

    employeeButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowLogin();
        });

    Layout();
}

void MainFrame::BookTable() {
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);

    wxGridSizer* gridSizer = new wxGridSizer(0, 2, 10, 10);
    buttons.clear();

    for (int i = 0; i < numTables; i++) {
        wxString label = wxString::Format("Table : %d%s", i + 1, tableBooked[i] ? " (Unavailable)" : "");
        wxButton* button = new wxButton(currentPanel, wxID_ANY, label, wxDefaultPosition, wxSize(300, 100));
        buttons.push_back(button);
        gridSizer->Add(button, 0, wxEXPAND | wxALL, 5);

        if (tableBooked[i]) {
            button->SetBackgroundColour(*wxRED);
        }

        button->Bind(wxEVT_ENTER_WINDOW, [button, this, i](wxMouseEvent&) {
            if (!tableBooked[i]) {
                button->SetBackgroundColour(*wxYELLOW);
                button->Refresh();
            }
            });

        button->Bind(wxEVT_LEAVE_WINDOW, [button, this, i](wxMouseEvent&) {
            if (!tableBooked[i]) {
                button->SetBackgroundColour(wxNullColour);
                button->Refresh();
            }
            });

        button->Bind(wxEVT_BUTTON, [this, i, button](wxCommandEvent&) {
            wxDialog dialog(this, wxID_ANY, "Table Booking");
            wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

            wxStaticText* nameLabel = new wxStaticText(&dialog, wxID_ANY, "Enter your name:");
            wxTextCtrl* nameCtrl = new wxTextCtrl(&dialog, wxID_ANY, "");
            wxStaticText* detailsLabel = new wxStaticText(&dialog, wxID_ANY, "Enter additional details (Time / Phone Number):");
            wxTextCtrl* detailsCtrl = new wxTextCtrl(&dialog, wxID_ANY, "");
            wxButton* okButton = new wxButton(&dialog, wxID_OK, "OK");
            wxButton* cancelButton = new wxButton(&dialog, wxID_CANCEL, "Cancel");

            dialogSizer->Add(nameLabel, 0, wxALL | wxEXPAND, 5);
            dialogSizer->Add(nameCtrl, 0, wxALL | wxEXPAND, 5);
            dialogSizer->Add(detailsLabel, 0, wxALL | wxEXPAND, 5);
            dialogSizer->Add(detailsCtrl, 0, wxALL | wxEXPAND, 5);

            wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
            buttonSizer->Add(okButton, 0, wxALL, 5);
            buttonSizer->Add(cancelButton, 0, wxALL, 5);

            dialogSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);
            dialog.SetSizer(dialogSizer);
            dialog.SetSize(300, 250);
            dialog.CenterOnParent(); 

            if (dialog.ShowModal() == wxID_OK) {
                wxString name = nameCtrl->GetValue();
                wxString details = detailsCtrl->GetValue();

                tableDetails[i] = { name, details };
                tableBooked[i] = true;

                button->SetLabel(wxString::Format("Table : %d (Unavailable)", i + 1));
                button->SetBackgroundColour(*wxRED);
                button->Refresh();
                wxMessageBox(wxString::Format("Table %d booked for %s\nDetails: %s", i + 1, name, details), "Confirmation", wxOK | wxICON_INFORMATION, this);
            }


            });
    }

    wxButton* backButton = new wxButton(currentPanel, wxID_ANY, "Back");
    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowRole();
        });

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 5);

    currentPanel->SetSizer(mainSizer);
    Layout();
}


void MainFrame::ShowLogin() {
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }
    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* userLabel = new wxStaticText(currentPanel, wxID_ANY, "Username:");
    wxTextCtrl* usernameCtrl = new wxTextCtrl(currentPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30));
    wxStaticText* passLabel = new wxStaticText(currentPanel, wxID_ANY, "Password:");
    wxTextCtrl* passwordCtrl = new wxTextCtrl(currentPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30), wxTE_PASSWORD);
    wxButton* loginButton = new wxButton(currentPanel, wxID_ANY, "Login");
    wxButton* backButton = new wxButton(currentPanel, wxID_ANY, "Back");

    sizer->Add(userLabel, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(usernameCtrl, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(passLabel, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(passwordCtrl, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(loginButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);
    currentPanel->SetSizer(sizer);

    loginButton->Bind(wxEVT_BUTTON, [this, usernameCtrl, passwordCtrl](wxCommandEvent&) {
        wxString username = usernameCtrl->GetValue();
        wxString password = passwordCtrl->GetValue();
        if (username == "1" && password == "1") {
            ShowEmployeeSystem();
        }
        else {
            wxMessageBox("Invalid username or password", "Error", wxOK | wxICON_ERROR);
        }
        });

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowRole();
        });

    Layout();
}

void MainFrame::ShowEmployeeSystem() {
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }
    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxButton* tableOrderButton = new wxButton(currentPanel, wxID_ANY, "Table");
    wxButton* manageMenuButton = new wxButton(currentPanel, wxID_ANY, "Manage Menu");

    sizer->Add(tableOrderButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(manageMenuButton, 0, wxALL | wxALIGN_CENTER, 5);

    wxButton* addTableButton = new wxButton(currentPanel, wxID_ANY, "Add Table");
    wxButton* removeTableButton = new wxButton(currentPanel, wxID_ANY, "Remove Table");

    sizer->Add(addTableButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(removeTableButton, 0, wxALL | wxALIGN_CENTER, 5);

    currentPanel->SetSizer(sizer);

    tableOrderButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowOrderMenu();
        });

    manageMenuButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowManageMenu();
        });

    addTableButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        numTables++;
        tableBooked.push_back(false);
        tableDetails.push_back({ "", "" });

        wxMessageBox(wxString::Format("Added Table %d", numTables), "Success", wxOK | wxICON_INFORMATION, this);
        });

    removeTableButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        if (numTables > 1) {
            numTables--;
            tableBooked.pop_back();
            tableDetails.pop_back();

            wxMessageBox(wxString::Format("Removed Table %d", numTables + 1), "Success", wxOK | wxICON_INFORMATION, this);
        }
        else {
            wxMessageBox("At least one table is required!", "Error", wxOK | wxICON_ERROR, this);
        }
        });

    Layout();
}

void MainFrame::ShowManageMenu() {
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(currentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxHSCROLL | wxVSCROLL);

    scrolledWindow->SetScrollRate(10, 10);

    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);

    for (int i = 0; i < 20; ++i) {
        wxButton* foodButton = new wxButton(scrolledWindow, wxID_ANY, wxString::Format("Food Item %d", i + 1));
        scrolledSizer->Add(foodButton, 0, wxALL | wxEXPAND, 5);
    }

    scrolledWindow->SetSizer(scrolledSizer);
    scrolledSizer->FitInside(scrolledWindow);

    panelSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 10);

    wxButton* addButton = new wxButton(currentPanel, wxID_ANY, "Add");
    wxButton* removeButton = new wxButton(currentPanel, wxID_ANY, "Remove");
    wxButton* backButton = new wxButton(currentPanel, wxID_ANY, "Back");

    panelSizer->Add(addButton, 0, wxALL | wxALIGN_CENTER, 5);
    panelSizer->Add(removeButton, 0, wxALL | wxALIGN_CENTER, 5);
    panelSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowEmployeeSystem();
        });

    currentPanel->SetSizer(panelSizer);
    Layout();
}

void MainFrame::ShowOrderMenu() {
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);

    wxGridSizer* gridSizer = new wxGridSizer(0, 2, 10, 10);
    buttons.clear();

    for (int i = 0; i < numTables; i++) {
        wxString label = wxString::Format("Table : %d", i + 1);
        wxButton* button = new wxButton(currentPanel, wxID_ANY, label, wxDefaultPosition, wxSize(300, 100));
        buttons.push_back(button);
        gridSizer->Add(button, 0, wxEXPAND | wxALL, 5);

        button->Bind(wxEVT_BUTTON, [this, i](wxCommandEvent&) {
            ShowOrderFood();
            });
    }

    wxButton* backButton = new wxButton(currentPanel, wxID_ANY, "Back");
    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowEmployeeSystem();
        });

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 5);

    currentPanel->SetSizer(mainSizer);

    Layout();
}

void MainFrame::ShowOrderFood() {
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(currentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxHSCROLL | wxVSCROLL);

    scrolledWindow->SetScrollRate(10, 10);

    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);

    for (int i = 0; i < 20; ++i) {
        wxButton* foodButton = new wxButton(scrolledWindow, wxID_ANY, wxString::Format("Food Item %d", i + 1));
        scrolledSizer->Add(foodButton, 0, wxALL | wxEXPAND, 5);
    }

    scrolledWindow->SetSizer(scrolledSizer);
    scrolledSizer->FitInside(scrolledWindow);

    panelSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 10);

    wxButton* backButton = new wxButton(currentPanel, wxID_ANY, "Back");
    wxButton* calculateButton = new wxButton(currentPanel, wxID_ANY, "Calculate");
    panelSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);
    panelSizer->Add(calculateButton, 0, wxALL | wxALIGN_CENTER, 5);

    calculateButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        CalculateTotal();
        });

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowOrderMenu();
        });

    currentPanel->SetSizer(panelSizer);
    Layout();
}

void MainFrame::CalculateTotal() {
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    wxString receiptText =
        "=========== RECEIPT ============\n"
        "Item 1:       $2.00\n"
        "Item 2:       $1.50\n"
        "Item 3:       $3.00\n"
        "--------------------------------\n"
        "Total:              \n"
        "===============================\n"
        "----Thank you for visiting!!----";

    wxStaticText* orderSummary = new wxStaticText(currentPanel, wxID_ANY, receiptText, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

    wxButton* backButton = new wxButton(currentPanel, wxID_ANY, "Back");

    panelSizer->Add(orderSummary, 0, wxALL | wxEXPAND, 10);
    panelSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowOrderFood();
        });

    currentPanel->SetSizer(panelSizer);
    Layout();
}