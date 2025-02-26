#include "MainFrame.h"
#include "List.h"
#include "TableCount.h"

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Restaurant Management System", wxDefaultPosition, wxSize(500, 400))
{
    currentPanel = nullptr;

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(frameSizer);

    CreateStatusBar();

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

    //wxImage::AddHandler(new wxPNGHandler());
    //wxBitmap bitmap(wxT("image.png"), wxBITMAP_TYPE_PNG);
    //wxStaticBitmap* bgimg = new wxStaticBitmap(panel, wxID_ANY, bitmap);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxButton* customerButton = new wxButton(panel, wxID_ANY, "Customer");
    wxButton* employeeButton = new wxButton(panel, wxID_ANY, "Employee");

    sizer->AddStretchSpacer();
    //sizer->Add(bgimg, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(customerButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(employeeButton, 0, wxALL | wxALIGN_CENTER, 5);
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
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);

    wxGridSizer* gridSizer = new wxGridSizer(0, 2, 10, 10);
    buttons.clear();

    for (int i = 0; i < tableCount; i++) {
        wxString label = wxString::Format("Table : %d", i + 1);
        wxButton* button = new wxButton(currentPanel, wxID_ANY, label, wxDefaultPosition, wxSize(300, 100));
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
            wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);

            wxStaticText* nameLabel = new wxStaticText(&dialog, wxID_ANY, "Enter your name:");
            wxTextCtrl* nameCtrl = new wxTextCtrl(&dialog, wxID_ANY, "");
            wxStaticText* timeLabel = new wxStaticText(&dialog, wxID_ANY, "Time:");
            wxTextCtrl* timeCtrl = new wxTextCtrl(&dialog, wxID_ANY, "");
            wxStaticText* detailLabel = new wxStaticText(&dialog, wxID_ANY, "Enter additional details (Phone Number):");
            wxTextCtrl* detailCtrl = new wxTextCtrl(&dialog, wxID_ANY, "");
            wxButton* okButton = new wxButton(&dialog, wxID_OK, "OK");
            wxButton* cancelButton = new wxButton(&dialog, wxID_CANCEL, "Cancel");

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

    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* userLabel = new wxStaticText(panel, wxID_ANY, "Username:");
    wxTextCtrl* usernameCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30));
    wxStaticText* passLabel = new wxStaticText(panel, wxID_ANY, "Password:");
    wxTextCtrl* passwordCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 30), wxTE_PASSWORD);
    wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login");
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");

    sizer->AddStretchSpacer();
    sizer->Add(userLabel, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(usernameCtrl, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(passLabel, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(passwordCtrl, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(loginButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->AddStretchSpacer();
    sizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);
    panel->SetSizer(sizer);

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

    SwitchPanel(panel);
}

void MainFrame::ShowEmployeeSystem() {

    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxButton* tableOrderButton = new wxButton(panel, wxID_ANY, "Table");
    wxButton* manageMenuButton = new wxButton(panel, wxID_ANY, "Manage Menu");
    wxButton* manageTablesButton = new wxButton(panel, wxID_ANY, "Manage Tables");
    wxButton* resDetailButton = new wxButton(panel, wxID_ANY, "Reservation Detail");
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");


    sizer->AddStretchSpacer();
    sizer->Add(tableOrderButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(manageMenuButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(manageTablesButton, 0, wxALL | wxALIGN_CENTER, 5);
    sizer->Add(resDetailButton, 0, wxALL | wxALIGN_CENTER, 5);
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

void MainFrame::ShowManageTables()
{
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);


    tableCount = LoadTableCount("tableCount.txt");  // Load number of table to tableCount variable

    // Display the current table count.
    wxStaticText* infoText = new wxStaticText(panel, wxID_ANY,
        wxString::Format("Current Number of Tables: %d", tableCount));
    mainSizer->AddStretchSpacer();
    mainSizer->Add(infoText, 0, wxALL | wxALIGN_CENTER, 10);

    // Buttons for adding and removing tables.
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* addTableButton = new wxButton(panel, wxID_ANY, "Add Table");
    wxButton* removeTableButton = new wxButton(panel, wxID_ANY, "Remove Table");
    btnSizer->Add(addTableButton, 0, wxALL, 5);
    btnSizer->Add(removeTableButton, 0, wxALL, 5);
    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER, 10);
    mainSizer->AddStretchSpacer();

    // Back button to return to the Employee Main Menu.
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");
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

void MainFrame::ShowManageMenu() {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(255, 255, 255));
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxHSCROLL | wxVSCROLL);
    scrolledWindow->SetScrollRate(10, 10);
    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);

    std::vector<List> menuList = loadListFromFile("menuList.txt");
    wxFont menuFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    for (int i = 0; i < menuList.size(); i++) {
        wxPanel* itemPanel = new wxPanel(scrolledWindow);
        itemPanel->SetBackgroundColour((i % 2 == 0) ? wxColour(220, 200, 200) : wxColour(220, 220, 220));

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

        tempBoxSizer->Add(tagText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        tempBoxSizer->Add(nameText, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        tempBoxSizer->Add(priceText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

        itemPanel->SetSizer(tempBoxSizer);
        scrolledSizer->Add(itemPanel, 0, wxEXPAND | wxALL, 5);
    }

    scrolledWindow->SetSizer(scrolledSizer);
    scrolledSizer->FitInside(scrolledWindow);

    panelSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 10);

    wxButton* addButton = new wxButton(panel, wxID_ANY, "Add");
    wxButton* removeButton = new wxButton(panel, wxID_ANY, "Remove");
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");

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
    panel->SetBackgroundColour(wxColour(200, 255, 255));

    wxFlexGridSizer* panelSizer = new wxFlexGridSizer(2, 10, 10);

    wxStaticText* tagLabel = new wxStaticText(panel, wxID_ANY, "Tag :");
    wxTextCtrl* tagInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

    wxStaticText* nameLabel = new wxStaticText(panel, wxID_ANY, "Name :");
    wxTextCtrl* nameInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

    wxStaticText* priceLabel = new wxStaticText(panel, wxID_ANY, "Price :");
    wxTextCtrl* priceInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

    wxButton* addConfirm = new wxButton(panel, wxID_ANY, "Confirm");
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");

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

        std::vector<List> menuList = loadListFromFile("menuList.txt");
        menuList.push_back(temp);
        saveListToFile(menuList, "menuList.txt");

        wxFrame* miniWindow = new wxFrame(this, wxID_ANY, "Announcement", wxDefaultPosition, wxSize(300, 200),
            wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
        miniWindow->SetBackgroundColour(*wxWHITE);
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

        miniWindow->Show();
        });

    panel->SetSizer(mainSizer);
    SwitchPanel(panel);
}

void MainFrame::ShowRemovePanel() {

    wxPanel* panel = new wxPanel(this);
    panel->SetBackgroundColour(wxColour(200, 255, 255));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxTextCtrl* tagInput = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    wxButton* removeConfirm = new wxButton(panel, wxID_ANY, "Confirm");
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");

    mainSizer->AddStretchSpacer();
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
        for (int i = 0; i < menuList.size(); i++) {
            if (menuList[i].tag == temptag) {
                menuList.erase(menuList.begin() + i);
                break;
            }
        }
        saveListToFile(menuList, "menuList.txt");

        wxFrame* miniWindow = new wxFrame(this, wxID_ANY, "Announcement", wxDefaultPosition, wxSize(300, 200),
            wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
        miniWindow->SetBackgroundColour(*wxWHITE);
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
        });

    panel->SetSizer(mainSizer);
    SwitchPanel(panel);
}

void MainFrame::ShowTableToOrderMenu() {

    wxPanel* panel = new wxPanel(this);
    wxGridSizer* gridSizer = new wxGridSizer(0, 2, 10, 10);
    buttons.clear();
    tableCount = LoadTableCount("tableCount.txt");
    for (int i = 0; i < tableCount; i++) {
        int tableNumber = i + 1;
        wxString label = wxString::Format("Table : %d", tableNumber);
        wxButton* button = new wxButton(panel, wxID_ANY, label, wxDefaultPosition, wxSize(300, 100));
        buttons.push_back(button);
        gridSizer->Add(button, 0, wxEXPAND | wxALL, 5);

        // Pass tableNumber to the order screen.
        button->Bind(wxEVT_BUTTON, [this, tableNumber](wxCommandEvent&) {
            ShowOrderFood(tableNumber);
            });
    }

    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");
    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowEmployeeSystem();
        });

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(mainSizer);
    SwitchPanel(panel);
}


// กำหนดขนาดของ vector tableDetails, tableBooked
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

// Modified ShowOrderFood that accepts tableNumber
void MainFrame::ShowOrderFood(int tableNumber) {

    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    // Display which table is being ordered
    wxStaticText* tableLabel = new wxStaticText(panel, wxID_ANY,
        wxString::Format("Order for Table: %d", tableNumber), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    panelSizer->Add(tableLabel, 0, wxALL | wxALIGN_CENTER, 5);

    // Create a scrollable window to show available menu items
    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxHSCROLL | wxVSCROLL);
    scrolledWindow->SetScrollRate(10, 10);
    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);

    std::vector<List> menuList = loadListFromFile("menuList.txt");
    for (const auto& item : menuList) {
        wxStaticText* foodItem = new wxStaticText(scrolledWindow, wxID_ANY,
            wxString::Format("%d %s %d THB", item.tag, item.name, item.price));
        scrolledSizer->Add(foodItem, 0, wxALL | wxALIGN_CENTER, 5);
    }
    scrolledWindow->SetSizer(scrolledSizer);
    scrolledSizer->FitInside(scrolledWindow);

    panelSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 10);

    // Buttons for adding an order item, calculating total, etc.
    wxButton* addOrderButton = new wxButton(panel, wxID_ANY, "Add Order Item");
    wxButton* calculateButton = new wxButton(panel, wxID_ANY, "Calculate");
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");

    panelSizer->Add(addOrderButton, 0, wxALL | wxALIGN_CENTER, 5);
    panelSizer->Add(calculateButton, 0, wxALL | wxALIGN_CENTER, 5);
    panelSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);

    // Bind the Add Order button to prompt for a menu item tag and add the item
    addOrderButton->Bind(wxEVT_BUTTON, [this, tableNumber](wxCommandEvent&) {
        wxTextEntryDialog orderDialog(this, "Enter menu item tag to order:", "Add Order Item");
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

// Modified CalculateTotal that accepts tableNumber
void MainFrame::CalculateTotal(int tableNumber) {

    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    double total = 0;
    wxString receiptText = wxString::Format("=========== RECEIPT for Table %d ===========\n", tableNumber);

    // Iterate over each order item for this table
    for (const auto& item : tableOrders[tableNumber]) {
        receiptText += wxString::Format("%s - %d THB\n", item.name, item.price);
        total += item.price;
    }
    tableOrders.erase(tableNumber);
    receiptText += "--------------------------------\n";
    receiptText += wxString::Format("Total: %.2f THB\n", total);
    receiptText += "===============================\n";
    receiptText += "----Thank you for visiting!!----";

    wxStaticText* orderSummary = new wxStaticText(panel, wxID_ANY, receiptText, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");

    panelSizer->Add(orderSummary, 0, wxALL | wxEXPAND, 10);
    panelSizer->Add(backButton, 0, wxALL | wxALIGN_CENTER, 5);

    backButton->Bind(wxEVT_BUTTON, [this, tableNumber](wxCommandEvent&) {
        ShowOrderFood(tableNumber);
        });

    panel->SetSizer(panelSizer);
    SwitchPanel(panel);
}

void MainFrame::ShowDataTable()
{
    wxPanel* panel = new wxPanel(this);
    wxGridSizer* gridSizer = new wxGridSizer(0, 2, 10, 10);
    buttons.clear();

    LoadTableData();

    wxCheckListBox* ListDataCustomer = new wxCheckListBox(panel, wxID_ANY);

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

    wxButton* deleteButton = new wxButton(panel, wxID_ANY, "Delete");
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

    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");
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



