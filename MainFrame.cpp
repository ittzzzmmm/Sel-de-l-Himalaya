#include "MainFrame.h"
#include "List.h"
#include "TableCount.h"

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Restaurant Management System", wxDefaultPosition, wxSize(500, 400))
{
    currentPanel = nullptr;

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(frameSizer);

    ShowRole();

    Layout();
}

void MainFrame::SwitchPanel(wxPanel* newPanel)
{
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }
    currentPanel = newPanel;
    GetSizer()->Add(currentPanel, 1, wxEXPAND);
    Layout();
}

void MainFrame::ShowRole() {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(77, 56, 44));

    wxImage::AddHandler(new wxPNGHandler());
    wxBitmap bitmap(wxT("image.png"), wxBITMAP_TYPE_PNG);
    wxStaticBitmap* bgimg = new wxStaticBitmap(panel, wxID_ANY, bitmap);

    wxFont buttonFont(20, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxButton* customerButton = new wxButton(panel, wxID_ANY, "Customer", wxDefaultPosition, wxSize(200, 50));
    customerButton->SetBackgroundColour(wxColour(168, 157, 117));
    customerButton->SetFont(buttonFont);
    customerButton->Refresh();
    wxButton* employeeButton = new wxButton(panel, wxID_ANY, "Staff" , wxDefaultPosition, wxSize(200, 50));
    employeeButton->SetBackgroundColour(wxColour(168, 157, 117));
    employeeButton->SetFont(buttonFont);
    employeeButton->Refresh();


    sizer->AddStretchSpacer(2);
    sizer->Add(bgimg, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->AddStretchSpacer();
    sizer->Add(customerButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(employeeButton, 0, wxTOP | wxALIGN_CENTER, 30);
    sizer->AddStretchSpacer();
    panel->SetSizer(sizer);

    customerButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        BookTable(); // กดว่าเป็นลูกค้าแล้วไปหน้าจองโต๊ะ
        });
    employeeButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowLogin(); // กดว่าเป็นลูกจ้างแล้วไปหน้า login
        });

    SwitchPanel(panel);
}

void MainFrame::BookTable() {
    LoadTableData();

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(77, 56, 44));
    wxGridSizer* gridSizer = new wxGridSizer(0, 2, 10, 10);
    buttons.clear();
    wxFont buttonFont(20,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false);
    for (int i = 0; i < tableCount; i++) {
        wxString label = wxString::Format("Table : %d", i + 1);
        wxButton* button = new wxButton(panel, wxID_ANY, label, wxDefaultPosition, wxSize(300, 100));
        button->SetBackgroundColour(wxColour(168, 157, 117));
        button->SetFont(buttonFont);
        button->Refresh();
        buttons.push_back(button);
        gridSizer->Add(button, 0, wxEXPAND | wxALL, 5);

        button->Bind(wxEVT_BUTTON, [this, i, button](wxCommandEvent&) {
            if (tableBooked[i]) {
                wxString bookingHistory = "ประวัติการจองทั้งหมดของโต๊ะนี้:\n";
                for (const auto& booking : tableDetails[i]) {
                    bookingHistory += wxString::Format("เวลา: %s \n",
                        wxString::FromUTF8(std::get<1>(booking).c_str())
                    );
                }

                wxMessageBox(bookingHistory, "โต๊ะนี้ถูกจองแล้ว", wxOK | wxICON_INFORMATION, this);
            }

            wxDialog dialog(this, wxID_ANY, "Table Booking");
            dialog.SetBackgroundColour(wxColour(168, 157, 117));
            wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

            wxStaticText* nameLabel = new wxStaticText(&dialog, wxID_ANY, "Enter your name:");
            wxTextCtrl* nameCtrl = new wxTextCtrl(&dialog, wxID_ANY, "");
            wxStaticText* timeLabel = new wxStaticText(&dialog, wxID_ANY, "Time:");
            wxTextCtrl* timeCtrl = new wxTextCtrl(&dialog, wxID_ANY, "");
            wxStaticText* detailLabel = new wxStaticText(&dialog, wxID_ANY, "Enter additional details (Phone Number):");
            wxTextCtrl* detailCtrl = new wxTextCtrl(&dialog, wxID_ANY, "");
            wxButton* okButton = new wxButton(&dialog, wxID_OK, "OK");
            wxButton* cancelButton = new wxButton(&dialog, wxID_CANCEL, "Cancel");

            dialogSizer->AddStretchSpacer();
            dialogSizer->Add(nameLabel, 0, wxALL | wxEXPAND, 5);
            dialogSizer->Add(nameCtrl, 0, wxALL | wxEXPAND, 5);
            dialogSizer->Add(timeLabel, 0, wxALL | wxEXPAND, 5);
            dialogSizer->Add(timeCtrl, 0, wxALL | wxEXPAND, 5);
            dialogSizer->Add(detailLabel, 0, wxALL | wxEXPAND, 5);
            dialogSizer->Add(detailCtrl, 0, wxALL | wxEXPAND, 5);

            wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

            buttonSizer->Add(okButton, 0, wxALL, 5);
            buttonSizer->Add(cancelButton, 0, wxALL, 5);

            dialogSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);
            dialogSizer->AddStretchSpacer();
            dialog.SetSizer(dialogSizer);
            dialog.SetSize(500, 350);
            dialog.CenterOnParent();

            if (dialog.ShowModal() == wxID_OK) {
                wxString name = nameCtrl->GetValue();
                wxString time = timeCtrl->GetValue();
                wxString detail = detailCtrl->GetValue();

                tableDetails[i].emplace_back(name.ToStdString(), time.ToStdString(), detail.ToStdString());
                tableBooked[i] = true;



                button->Refresh();
                wxString bookingHistory = "ประวัติการจองทั้งหมดของโต๊ะนี้:\n";
                for (const auto& booking : tableDetails[i]) {
                    bookingHistory += wxString::Format("ชื่อ: %s | เวลา: %s | รายละเอียด: %s\n",
                        wxString::FromUTF8(std::get<0>(booking).c_str()),
                        wxString::FromUTF8(std::get<1>(booking).c_str()),
                        wxString::FromUTF8(std::get<2>(booking).c_str()));
                }

                wxMessageBox(wxString::Format("Table %d booked for %s\nTime: %s\nDetails: %s", i + 1, name, time, detail), "Confirmation", wxOK | wxICON_INFORMATION, this);
            }
            });
    }

    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back",wxDefaultPosition,wxSize(200,40));
    backButton->SetBackgroundColour(wxColour(168, 157, 117));
    backButton->SetFont(buttonFont);
    backButton->Refresh();
    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowRole();
        });

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(mainSizer);
    SwitchPanel(panel);
}

void MainFrame::ShowLogin() {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(168, 157, 117));
    wxFont textFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* userLabel = new wxStaticText(panel, wxID_ANY, "Username:");
    wxTextCtrl* usernameCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30));
    wxStaticText* passLabel = new wxStaticText(panel, wxID_ANY, "Password:");
    wxTextCtrl* passwordCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30), wxTE_PASSWORD);
    wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login", wxDefaultPosition, wxSize(150, -1));
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back", wxDefaultPosition, wxSize(150, -1));
    userLabel->SetFont(textFont);
    usernameCtrl->SetFont(textFont);
    passLabel->SetFont(textFont);
    passwordCtrl->SetFont(textFont);
    usernameCtrl->SetFocus();

    loginButton->SetBackgroundColour(wxColour(212, 203, 169));
    loginButton->SetFont(textFont);
    backButton->SetBackgroundColour(wxColour(212, 203, 169));
    backButton->SetFont(textFont);

    sizer->AddStretchSpacer();
    sizer->Add(userLabel, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(usernameCtrl, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(passLabel, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(passwordCtrl, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(loginButton, 0, wxALL | wxALIGN_CENTER, 15);
    sizer->AddStretchSpacer();
    sizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);
    panel->SetSizer(sizer);

    loginButton->Bind(wxEVT_BUTTON, [this, usernameCtrl, passwordCtrl](wxCommandEvent&) {
        wxString username = usernameCtrl->GetValue();
        wxString password = passwordCtrl->GetValue();
        if (username == "Senku" && password == "Stone") {
            ShowEmployeeSystem();
        }
        else {
            wxMessageBox("Invalid username or password", "Error", wxOK | wxICON_ERROR);
        }
        });

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowRole();
        });

    SwitchPanel(panel);
}

void MainFrame::ShowEmployeeSystem() {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(168, 157, 117));
    wxFont textFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxButton* tableOrderButton = new wxButton(panel, wxID_ANY, "Table",wxDefaultPosition,wxSize(190,45));
    wxButton* manageMenuButton = new wxButton(panel, wxID_ANY, "Manage Menu", wxDefaultPosition, wxSize(190, 45));
    wxButton* manageTablesButton = new wxButton(panel, wxID_ANY, "Manage Tables", wxDefaultPosition, wxSize(190, 45));
    wxButton* resDetailButton = new wxButton(panel, wxID_ANY, "Reservation Detail", wxDefaultPosition, wxSize(190, 45));
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Log out");
    tableOrderButton->SetFont(textFont);
    tableOrderButton->SetBackgroundColour(wxColour(217, 199, 167));
    manageMenuButton->SetFont(textFont);
    manageMenuButton->SetBackgroundColour(wxColour(217, 199, 167));
    manageTablesButton->SetFont(textFont);
    manageTablesButton->SetBackgroundColour(wxColour(217, 199, 167));
    resDetailButton->SetFont(textFont);
    resDetailButton->SetBackgroundColour(wxColour(217, 199, 167));
    backButton->SetFont(textFont);
    backButton->SetBackgroundColour(wxColour(217, 199, 167));

    sizer->AddStretchSpacer();
    sizer->Add(tableOrderButton, 0, wxALL | wxALIGN_CENTER, 15);
    sizer->Add(manageMenuButton, 0, wxALL | wxALIGN_CENTER, 15);
    sizer->Add(manageTablesButton, 0, wxALL | wxALIGN_CENTER, 15);
    sizer->Add(resDetailButton, 0, wxALL | wxALIGN_CENTER, 15);
    sizer->AddStretchSpacer();
    sizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);
    panel->SetSizer(sizer);

    tableOrderButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowTableToOrderMenu();
        });
    manageMenuButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowManageMenu();
        });
    manageTablesButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowManageTables();
        });
    resDetailButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowDataTable();
        });
    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowRole();
        });

    SwitchPanel(panel);
}

void MainFrame::ShowTableToOrderMenu() {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(77, 56, 44));
    wxFont textFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxGridSizer* gridSizer = new wxGridSizer(0, 2, 10, 10);
    buttons.clear();
    tableCount = LoadTableCount("tableCount.txt");
    for (int i = 0; i < tableCount; i++) {
        int tableNumber = i + 1;
        wxString label = wxString::Format("Table : %d", tableNumber);
        wxButton* button = new wxButton(panel, wxID_ANY, label, wxDefaultPosition, wxSize(300, 100));
        button->SetFont(textFont);
        button->SetBackgroundColour(wxColour(168, 157, 117));
        buttons.push_back(button);
        gridSizer->Add(button, 0, wxEXPAND | wxALL, 5);

        // Pass tableNumber to the order screen.
        button->Bind(wxEVT_BUTTON, [this, tableNumber](wxCommandEvent&) {
            ShowOrderFood(tableNumber);
            });
    }

    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back",wxDefaultPosition,wxSize(140,-1));
    backButton->SetFont(textFont);
    backButton->SetBackgroundColour(wxColour(168, 157, 117));
    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowEmployeeSystem();
        });

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(mainSizer);
    SwitchPanel(panel);
}

void MainFrame::ShowManageMenu() {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(77, 56, 44));
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxFont btnFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL); 

    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxHSCROLL | wxVSCROLL);
    scrolledWindow->SetScrollRate(10, 10);
    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);

    std::vector<List> menuList = loadListFromFile("menuList.txt");
    wxFont menuFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    for (int i = 0; i < menuList.size(); i++) {
        wxPanel* itemPanel = new wxPanel(scrolledWindow);
        itemPanel->SetBackgroundColour((i % 2 == 0) ? wxColour(168, 157, 117) : wxColour(168, 157, 117));

        wxBoxSizer* tempBoxSizer = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText* tagText = new wxStaticText(itemPanel, wxID_ANY, std::to_string(menuList[i].tag), wxDefaultPosition, wxSize(50, -1));
        tagText->SetFont(menuFont);
        tagText->SetForegroundColour(*wxBLACK);

        wxStaticText* nameText = new wxStaticText(itemPanel, wxID_ANY, menuList[i].name, wxDefaultPosition, wxSize(200, -1));
        nameText->SetFont(menuFont);
        nameText->SetForegroundColour(*wxBLACK);

        wxStaticText* priceText = new wxStaticText(itemPanel, wxID_ANY, std::to_string(menuList[i].price) + " THB", wxDefaultPosition, wxSize(100, -1));
        priceText->SetFont(menuFont);
        priceText->SetForegroundColour(*wxBLACK);

        tempBoxSizer->Add(tagText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 800);
        tempBoxSizer->Add(nameText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 50);
        tempBoxSizer->Add(priceText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

        itemPanel->SetSizer(tempBoxSizer);
        scrolledSizer->Add(itemPanel, 0, wxEXPAND | wxALL, 5);
    }

    scrolledWindow->SetSizer(scrolledSizer);
    scrolledSizer->FitInside(scrolledWindow);

    panelSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 10);

    wxButton* addButton = new wxButton(panel, wxID_ANY, "Add" , wxDefaultPosition , wxSize(150,35));
    wxButton* removeButton = new wxButton(panel, wxID_ANY, "Remove", wxDefaultPosition, wxSize(150, 35));
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back", wxDefaultPosition, wxSize(150, 35));

    addButton->SetBackgroundColour(wxColour(168, 157, 117));
    removeButton->SetBackgroundColour(wxColour(168, 157, 117));
    backButton->SetBackgroundColour(wxColour(168, 157, 117));

    addButton->SetFont(btnFont);
    removeButton->SetFont(btnFont);
    backButton->SetFont(btnFont);

    panelSizer->Add(addButton, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    panelSizer->Add(removeButton, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    panelSizer->Add(backButton, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    addButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowAddPanel();
        });

    removeButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowRemovePanel();
        });

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowEmployeeSystem();
        });

    panel->SetSizer(panelSizer);
    SwitchPanel(panel);
}

void MainFrame::ShowAddPanel() {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(168, 157, 117));
    wxFont textFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    wxFlexGridSizer* panelSizer = new wxFlexGridSizer(2, 10, 10);

    wxStaticText* tagLabel = new wxStaticText(panel, wxID_ANY, "Tag :");
    wxTextCtrl* tagInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    tagLabel->SetFont(textFont);
    tagInput->SetFont(textFont);
    tagInput->SetFocus();

    wxStaticText* nameLabel = new wxStaticText(panel, wxID_ANY, "Name :");
    wxTextCtrl* nameInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    nameLabel->SetFont(textFont);
    nameInput->SetFont(textFont);

    wxStaticText* priceLabel = new wxStaticText(panel, wxID_ANY, "Price :");
    wxTextCtrl* priceInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    priceLabel->SetFont(textFont);
    priceInput->SetFont(textFont);

    wxButton* addConfirm = new wxButton(panel, wxID_ANY, "Confirm",wxDefaultPosition,wxSize(150,30));
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back",wxDefaultPosition, wxSize(150, 30));
    addConfirm->SetBackgroundColour(wxColour(212, 203, 169));
    backButton->SetBackgroundColour(wxColour(212, 203, 169));
    addConfirm->SetFont(textFont);
    backButton->SetFont(textFont);

    panelSizer->Add(tagLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(tagInput, 0, wxALIGN_CENTER | wxALL, 10);

    panelSizer->Add(nameLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(nameInput, 0, wxALIGN_CENTER | wxALL, 10);

    panelSizer->Add(priceLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(priceInput, 0, wxALIGN_CENTER | wxALL, 10);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->AddStretchSpacer();
    mainSizer->Add(panelSizer, 0, wxALIGN_CENTER | wxALL, 20);
    mainSizer->Add(addConfirm, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->AddStretchSpacer();
    mainSizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 5);


    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowManageMenu();
        });

    addConfirm->Bind(wxEVT_BUTTON, [this, tagInput, nameInput, priceInput](wxCommandEvent&) {
        List temp;
        temp.tag = wxAtoi(tagInput->GetValue());
        temp.name = nameInput->GetValue();
        temp.price = wxAtoi(priceInput->GetValue());
        bool foundFlag = 0;

        std::vector<List> menuList = loadListFromFile("menuList.txt");
        for (int i = 0;i < menuList.size();i++) {
            if (temp.tag == menuList[i].tag) {
                wxFrame* miniWindow = new wxFrame(this, wxID_ANY, "Announcement", wxDefaultPosition, wxSize(400, 200),
                    wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
                miniWindow->SetBackgroundColour(wxColour(200, 255, 255));
                miniWindow->CentreOnScreen();

                wxPanel* miniPanel = new wxPanel(miniWindow);
                wxStaticText* successText = new wxStaticText(miniPanel, wxID_ANY, "YOU  ALREADY  HAVE  THIS  TAG  IN  YOUR  MENU !!\n\nPLEASE  ENTER  A  NEW  TAG.", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
                wxBoxSizer* miniSizer = new wxBoxSizer(wxVERTICAL);
                miniSizer->AddStretchSpacer(1);
                miniSizer->Add(successText, 0, wxALIGN_CENTER | wxALL, 10);
                miniSizer->AddStretchSpacer(1);
                miniPanel->SetSizer(miniSizer);

                miniWindow->Bind(wxEVT_CLOSE_WINDOW, [this, miniWindow](wxCloseEvent&) {
                    miniWindow->Destroy();
                    
                    });
                miniWindow->Show();
                foundFlag = 1;
                break;
            }
        }
        if (!foundFlag) {

            menuList.push_back(temp);
            std::sort(menuList.begin(), menuList.end(), [](const List& a, const List& b) {return a.tag < b.tag;});
            saveListToFile(menuList, "menuList.txt");

            wxFrame* miniWindow = new wxFrame(this, wxID_ANY, "Announcement", wxDefaultPosition, wxSize(300, 200),
                wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
            miniWindow->SetBackgroundColour(wxColour(200, 255, 255));
            miniWindow->CentreOnScreen();

            wxPanel* miniPanel = new wxPanel(miniWindow);
            wxStaticText* successText = new wxStaticText(miniPanel, wxID_ANY, "NEW MENU ADDED !", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
            wxBoxSizer* miniSizer = new wxBoxSizer(wxVERTICAL);
            miniSizer->AddStretchSpacer(1);
            miniSizer->Add(successText, 0, wxALIGN_CENTER | wxALL, 10);
            miniSizer->AddStretchSpacer(1);
            miniPanel->SetSizer(miniSizer);

            miniWindow->Bind(wxEVT_CLOSE_WINDOW, [this, miniWindow](wxCloseEvent&) {
                miniWindow->Destroy();
                ShowManageMenu();
                });
            miniWindow->Show();}
        });

    panel->SetSizer(mainSizer);
    SwitchPanel(panel);
}

void MainFrame::ShowRemovePanel() {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(168, 157, 117));
    wxFont textFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* tagText = new wxStaticText(panel,wxID_ANY,"Enter menu tag to remove :");
    wxTextCtrl* tagInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    wxButton* removeConfirm = new wxButton(panel, wxID_ANY, "Confirm", wxDefaultPosition, wxSize(140, -1));
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back", wxDefaultPosition, wxSize(140, -1));
    tagText->SetFont(textFont);
    tagInput->SetFont(textFont);
    tagInput->SetFocus();
    removeConfirm->SetFont(textFont);
    removeConfirm->SetBackgroundColour(wxColour(212, 203, 169));
    backButton->SetFont(textFont);
    backButton->SetBackgroundColour(wxColour(212, 203, 169));

    mainSizer->AddStretchSpacer();
    mainSizer->Add(tagText, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    mainSizer->Add(tagInput, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    mainSizer->Add(removeConfirm, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    mainSizer->AddStretchSpacer();
    mainSizer->Add(backButton, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowManageMenu();
        });

    removeConfirm->Bind(wxEVT_BUTTON, [this, tagInput](wxCommandEvent&) {
        int temptag = wxAtoi(tagInput->GetValue());
        std::vector<List> menuList = loadListFromFile("menuList.txt");
        bool foundFlag = 0;
        for (int i = 0; i < menuList.size(); i++) {
            if (menuList[i].tag == temptag) {
                menuList.erase(menuList.begin() + i);
                wxFrame* miniWindow = new wxFrame(this, wxID_ANY, "Announcement", wxDefaultPosition, wxSize(300, 200),
                    wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
                miniWindow->SetBackgroundColour(wxColour(200, 255, 255));
                miniWindow->CentreOnScreen();

                wxPanel* miniPanel = new wxPanel(miniWindow);
                wxStaticText* successText = new wxStaticText(miniPanel, wxID_ANY, "MENU REMOVED !", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
                wxBoxSizer* miniSizer = new wxBoxSizer(wxVERTICAL);
                miniSizer->AddStretchSpacer(1);
                miniSizer->Add(successText, 0, wxALIGN_CENTER | wxALL, 10);
                miniSizer->AddStretchSpacer(1);
                miniPanel->SetSizer(miniSizer);

                miniWindow->Bind(wxEVT_CLOSE_WINDOW, [this, miniWindow](wxCloseEvent&) {
                    miniWindow->Destroy();
                    ShowManageMenu();
                    });
                miniWindow->Show();
                foundFlag = 1;
                break;
            }  
        }
        if (!foundFlag) {
            wxFrame* miniWindow = new wxFrame(this, wxID_ANY, "Announcement", wxDefaultPosition, wxSize(300, 200),
                wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
            miniWindow->SetBackgroundColour(wxColour(200, 255, 255));
            miniWindow->CentreOnScreen();

            wxPanel* miniPanel = new wxPanel(miniWindow);
            wxStaticText* successText = new wxStaticText(miniPanel, wxID_ANY, "MENU  NOT  FOUND !\n\nPLEASE  ENTER  MENU  TAG  AGAIN.", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
            wxBoxSizer* miniSizer = new wxBoxSizer(wxVERTICAL);
            miniSizer->AddStretchSpacer(1);
            miniSizer->Add(successText, 0, wxALIGN_CENTER | wxALL, 10);
            miniSizer->AddStretchSpacer(1);
            miniPanel->SetSizer(miniSizer);

            miniWindow->Bind(wxEVT_CLOSE_WINDOW, [this, miniWindow](wxCloseEvent&) {
                miniWindow->Destroy();
                ShowManageMenu();
                });
            miniWindow->Show();
        }
        saveListToFile(menuList, "menuList.txt");

        
        });

    panel->SetSizer(mainSizer);
    SwitchPanel(panel);
}

void MainFrame::ShowManageTables()
{
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(77, 56, 44));
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxFont textFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxFont btnFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    tableCount = LoadTableCount("tableCount.txt");  // Load number of table to tableCount variable

    // Display the current table count.
    wxStaticText* infoText = new wxStaticText(panel, wxID_ANY,
        wxString::Format("Current Number of Tables: %d", tableCount));
    infoText->SetFont(textFont);
    infoText->SetForegroundColour(wxColour(255, 255, 255));
    mainSizer->AddStretchSpacer();
    mainSizer->Add(infoText, 0, wxALL | wxALIGN_CENTER, 10);

    // Buttons for adding and removing tables.
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* addTableButton = new wxButton(panel, wxID_ANY, "Add Table",wxDefaultPosition,wxSize(200,40));
    wxButton* removeTableButton = new wxButton(panel, wxID_ANY, "Remove Table", wxDefaultPosition, wxSize(200, 40));
    addTableButton->SetBackgroundColour(wxColour(168, 157, 117));
    removeTableButton->SetBackgroundColour(wxColour(168, 157, 117));
    addTableButton->SetFont(btnFont);
    removeTableButton->SetFont(btnFont);
    btnSizer->Add(addTableButton, 0, wxALL, 5);
    btnSizer->Add(removeTableButton, 0, wxALL, 5);
    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER, 10);
    mainSizer->AddStretchSpacer();

    // Back button to return to the Employee Main Menu.
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back",wxDefaultPosition,wxSize(150,35));
    backButton->SetFont(btnFont);
    backButton->SetBackgroundColour(wxColour(168, 157, 117));
    mainSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 10);

    addTableButton->Bind(wxEVT_BUTTON, [this, infoText](wxCommandEvent&) {
        tableCount++; // Increase table count
        SaveTableCount("tableCount.txt", tableCount);
        infoText->SetLabel(wxString::Format("Current Number of Tables: %d", tableCount));
        });
    removeTableButton->Bind(wxEVT_BUTTON, [this, infoText](wxCommandEvent&) {
        if (tableCount > 1) {
            tableCount--; // Decrease table count
            SaveTableCount("tableCount.txt", tableCount);
            infoText->SetLabel(wxString::Format("Current Number of Tables: %d", tableCount));
        }
        else {
            wxMessageBox("At least one table must exist.", "Error", wxOK | wxICON_ERROR);
        }
        });
    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowEmployeeSystem();
        });

    panel->SetSizer(mainSizer);
    SwitchPanel(panel);
}

void MainFrame::LoadTableData()
{
    std::ifstream inputFile("tableCount.txt");
    if (!inputFile.is_open()) {
        wxMessageBox("Failed to open tableCount.txt", "Error", wxOK | wxICON_ERROR);
        return;
    }

    inputFile >> tableCount;
    tableBooked.resize(tableCount);  // Resize tableBooked vector
    tableDetails.resize(tableCount); // Resize tableDetails vector


    inputFile.close();
}

void MainFrame::ShowOrderFood(int tableNumber) {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(168, 157, 117));
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxFont textFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxFont btnFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    // Display which table is being ordered
    wxStaticText* tableLabel = new wxStaticText(panel, wxID_ANY,
        wxString::Format("Menu for Table: %d", tableNumber), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    panelSizer->Add(tableLabel, 0, wxALL | wxALIGN_CENTER, 15);
    tableLabel->SetFont(textFont);

    // Create a scrollable window to show available menu items
    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxHSCROLL | wxVSCROLL);
    scrolledWindow->SetScrollRate(10, 10);
    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);

    std::vector<List> menuList = loadListFromFile("menuList.txt");
    for (const auto& item : menuList) {
        wxStaticText* foodItem = new wxStaticText(scrolledWindow, wxID_ANY,
            wxString::Format("%d    %s    %d THB", item.tag, item.name, item.price));
        foodItem->SetFont(textFont);
        scrolledSizer->Add(foodItem, 0, wxALIGN_CENTER|wxLEFT, 5);
    }
    scrolledWindow->SetSizer(scrolledSizer);
    scrolledSizer->FitInside(scrolledWindow);

    panelSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 10);

    // Buttons for adding an order item, calculating total, etc.
    wxButton* addOrderButton = new wxButton(panel, wxID_ANY, "Order",wxDefaultPosition,wxSize(150,-1));
    wxButton* calculateButton = new wxButton(panel, wxID_ANY, "Calculate", wxDefaultPosition, wxSize(150, -1));
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back", wxDefaultPosition, wxSize(150, -1));
    addOrderButton->SetBackgroundColour(wxColour(212, 203, 169));
    calculateButton->SetBackgroundColour(wxColour(212, 203, 169));
    backButton->SetBackgroundColour(wxColour(212, 203, 169));
    addOrderButton->SetFont(btnFont);
    calculateButton->SetFont(btnFont);
    backButton->SetFont(btnFont);

    panelSizer->Add(addOrderButton, 0, wxALL | wxALIGN_CENTER, 5);
    panelSizer->Add(calculateButton, 0, wxALL | wxALIGN_CENTER, 5);
    panelSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);

    // Bind the Add Order button to prompt for a menu item tag and add the item
    addOrderButton->Bind(wxEVT_BUTTON, [this, tableNumber](wxCommandEvent&) {
        wxTextEntryDialog orderDialog(this, "Enter menu item tag to order:", "Add Order Item");
        orderDialog.SetBackgroundColour(wxColour(212, 203, 169));
        if (orderDialog.ShowModal() == wxID_OK) {
            wxString tagStr = orderDialog.GetValue();
            int tag = wxAtoi(tagStr);
            std::vector<List> menuList = loadListFromFile("menuList.txt");
            bool found = false;
            for (const auto& item : menuList) {
                if (item.tag == tag) {
                    // Add the found menu item to the order for the given table
                    tableOrders[tableNumber].push_back(item);
                    wxMessageBox(wxString::Format("Added %s to Table %d's order.", item.name, tableNumber),
                        "Order Added", wxOK | wxICON_INFORMATION);
                    found = true;
                    break;
                }
            }
            if (!found) {
                wxMessageBox("Menu item not found.", "Error", wxOK | wxICON_ERROR);
            }
        }
        });

    calculateButton->Bind(wxEVT_BUTTON, [this, tableNumber](wxCommandEvent&) {
        CalculateTotal(tableNumber);
        });

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowTableToOrderMenu();
        });

    panel->SetSizer(panelSizer);
    SwitchPanel(panel);
}

void MainFrame::CalculateTotal(int tableNumber) {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(168, 157, 117));
    wxFont textFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    double total = 0;
    wxString receiptText = wxString::Format("=========== RECEIPT for Table %d ===========\n", tableNumber);

    // Iterate over each order item for this table
    for (const auto& item : tableOrders[tableNumber]) {
        receiptText += wxString::Format("%s - %d THB\n", item.name, item.price);
        total += item.price;
    }
    //tableOrders.erase(tableNumber);
    receiptText += "--------------------------------\n";
    receiptText += wxString::Format("Total: %.2f THB\n", total);
    receiptText += "======================================\n";
    receiptText += "----Thank you for visiting!!----";

    wxStaticText* orderSummary = new wxStaticText(panel, wxID_ANY, receiptText, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    orderSummary->SetFont(textFont);

    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back", wxDefaultPosition,wxSize(140,-1));
    backButton->SetFont(textFont);
    backButton->SetBackgroundColour(wxColour(212, 203, 169));

    wxButton* checkOut = new wxButton(panel, wxID_ANY, "Check Out", wxDefaultPosition, wxSize(140, -1));
    checkOut->SetFont(textFont);
    checkOut->SetBackgroundColour(wxColour(212, 203, 169));

    panelSizer->AddStretchSpacer(1);
    panelSizer->Add(orderSummary, 0, wxALIGN_CENTER, 10);
    panelSizer->AddStretchSpacer(4);
    panelSizer->Add(checkOut,0,wxALIGN_CENTER,10);
    panelSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);


    checkOut->Bind(wxEVT_BUTTON, [this, tableNumber](wxCommandEvent&) {
        tableOrders.erase(tableNumber);
        wxFrame* miniWindow = new wxFrame(this, wxID_ANY, "Announcement", wxDefaultPosition, wxSize(400, 200),
            wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
        miniWindow->SetBackgroundColour(wxColour(200, 255, 255));
        miniWindow->CentreOnScreen();

        wxPanel* miniPanel = new wxPanel(miniWindow);
        wxStaticText* successText = new wxStaticText(miniPanel, wxID_ANY, "THANK  YOU  FOR  VISITING", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        wxBoxSizer* miniSizer = new wxBoxSizer(wxVERTICAL);
        miniSizer->AddStretchSpacer(1);
        miniSizer->Add(successText, 0, wxALIGN_CENTER | wxALL, 10);
        miniSizer->AddStretchSpacer(1);
        miniPanel->SetSizer(miniSizer);

        miniWindow->Bind(wxEVT_CLOSE_WINDOW, [this, miniWindow](wxCloseEvent&) {
            miniWindow->Destroy();
            ShowTableToOrderMenu();

            });
        miniWindow->Show();
        });

    backButton->Bind(wxEVT_BUTTON, [this, tableNumber](wxCommandEvent&) {
        ShowOrderFood(tableNumber);
        });

    panel->SetSizer(panelSizer);
    SwitchPanel(panel);
}

void MainFrame::ShowDataTable()
{
    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(77, 56, 44));
    wxFont textFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxGridSizer* gridSizer = new wxGridSizer(0, 2, 10, 10);
    buttons.clear();

    LoadTableData();

    wxCheckListBox* ListDataCustomer = new wxCheckListBox(panel, wxID_ANY);
    ListDataCustomer->SetFont(textFont);
    ListDataCustomer->SetBackgroundColour(wxColour(212, 203, 169));

    for (size_t i = 0; i < tableDetails.size(); i++) {
        for (size_t j = 0; j < tableDetails[i].size(); j++) {
            const auto& booking = tableDetails[i][j];
            wxString bookingEntry = wxString::Format("Table %d | Name: %s | Time: %s | Details: %s",
                static_cast<int>(i + 1),
                wxString::FromUTF8(std::get<0>(booking).c_str()),
                wxString::FromUTF8(std::get<1>(booking).c_str()),
                wxString::FromUTF8(std::get<2>(booking).c_str()));
            ListDataCustomer->Append(bookingEntry);
        }
    }

    wxButton* deleteButton = new wxButton(panel, wxID_ANY, "Delete", wxDefaultPosition, wxSize(140, -1));
    deleteButton->SetBackgroundColour(wxColour(212, 203, 169));
    deleteButton->SetFont(textFont);
    deleteButton->Bind(wxEVT_BUTTON, [this, ListDataCustomer](wxCommandEvent&) {
        wxArrayInt selections;
        if (ListDataCustomer->GetSelections(selections) > 0) {
            // Delete selected entries in reverse order to avoid index shifting
            for (int i = selections.size() - 1; i >= 0; i--) {
                int selectedIndex = selections[i];

                // Find the corresponding row and index in tableDetails
                size_t tableIndex = 0;
                size_t entryIndex = 0;
                bool found = false;

                // Find the row and entry to remove
                for (size_t row = 0; row < tableDetails.size(); ++row) {
                    if (selectedIndex < tableDetails[row].size()) {
                        tableIndex = row;
                        entryIndex = selectedIndex;
                        found = true;
                        break;
                    }
                    selectedIndex -= tableDetails[row].size(); // Decrease index by the size of current row
                }

                if (found) {
                    // Remove the corresponding entry from tableDetails
                    tableDetails[tableIndex].erase(tableDetails[tableIndex].begin() + entryIndex);
                    // Also delete from the ListBox
                    ListDataCustomer->Delete(selections[i]);
                }
            }
        }
        });

    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back", wxDefaultPosition, wxSize(140, -1));
    backButton->SetBackgroundColour(wxColour(212, 203, 169));
    backButton->SetFont(textFont);

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowEmployeeSystem();
        });

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(ListDataCustomer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(deleteButton, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(mainSizer);
    SwitchPanel(panel);
}



