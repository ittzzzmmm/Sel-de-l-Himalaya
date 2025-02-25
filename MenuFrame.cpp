#include "MenuFrame.h"
#include <wx/wx.h>
#include <string>
#include <vector>
#include "List.h"
#include <wx/scrolwin.h>
//, wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER
MenuFrame::MenuFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	currentPanel = nullptr;

	wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(frameSizer);

	ShowMain();

}

void MenuFrame::ShowMain()
{
	if (currentPanel) {
		GetSizer()->Detach(currentPanel);
		currentPanel->Destroy();
	}
	currentPanel = new wxPanel(this);
	GetSizer()->Add(currentPanel, 1, wxEXPAND);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxButton* resMenuBtn = new wxButton(currentPanel, wxID_ANY, "Restaurant Menu");

	sizer->Add(resMenuBtn, 0, wxALIGN_CENTER| wxTOP, 400);

	currentPanel->SetSizer(sizer);

	resMenuBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {ShowManageMenu();});

	Layout();
}

void MenuFrame::ShowManageMenu() {
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);
    currentPanel->SetBackgroundColour(wxColour(255,255,255));

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(currentPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxHSCROLL | wxVSCROLL);

    scrolledWindow->SetScrollRate(10, 10);

    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);


    std::vector<List> menuList = loadListFromFile("menuList.txt");
    
    wxFont menuFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

for (int i = 0; i < menuList.size(); i++) {
    wxPanel* itemPanel = new wxPanel(scrolledWindow);
    itemPanel->SetBackgroundColour((i % 2 == 0) ? wxColour(220, 200, 200) : wxColour(220, 220, 220));

    wxBoxSizer* tempBoxSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create individual fields for alignment
    wxStaticText* tagText = new wxStaticText(itemPanel, wxID_ANY, std::to_string(menuList[i].tag), wxDefaultPosition, wxSize(50, -1));
    tagText->SetFont(menuFont);
    tagText->SetForegroundColour(*wxBLACK);

    wxStaticText* nameText = new wxStaticText(itemPanel, wxID_ANY, menuList[i].name, wxDefaultPosition, wxSize(200, -1));
    nameText->SetFont(menuFont);
    nameText->SetForegroundColour(*wxBLACK);

    wxStaticText* priceText = new wxStaticText(itemPanel, wxID_ANY, std::to_string(menuList[i].price) + " THB", wxDefaultPosition, wxSize(100, -1));
    priceText->SetFont(menuFont);
    priceText->SetForegroundColour(*wxBLACK);

    // Add each field to the horizontal sizer
    tempBoxSizer->Add(tagText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
    tempBoxSizer->Add(nameText, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
    tempBoxSizer->Add(priceText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

    itemPanel->SetSizer(tempBoxSizer);
    scrolledSizer->Add(itemPanel, 0, wxEXPAND | wxALL, 5);
}

    scrolledWindow->SetSizer(scrolledSizer);
    scrolledSizer->FitInside(scrolledWindow);

    panelSizer->Add(scrolledWindow, 1, wxEXPAND | wxALL, 10);

    wxButton* addButton = new wxButton(currentPanel, wxID_ANY, "Add");
    wxButton* removeButton = new wxButton(currentPanel, wxID_ANY, "Remove");
    wxButton* backButton = new wxButton(currentPanel, wxID_ANY, "Back");

    panelSizer->Add(addButton, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    panelSizer->Add(removeButton, 0, wxALIGN_CENTER | wxBOTTOM , 5);
    panelSizer->Add(backButton, 0,  wxALIGN_CENTER | wxBOTTOM, 10);


    //Binding 
    addButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowAddPanel();
        });

    removeButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowRemovePanel();
        });

    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowMain();
        });

    currentPanel->SetSizer(panelSizer);
    Layout();
}

void MenuFrame::ShowAddPanel()
{
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);
    currentPanel->SetBackgroundColour(wxColour(200, 255, 255));

    // FlexGridSizer: 2 columns, 10px spacing between elements
    wxFlexGridSizer* panelSizer = new wxFlexGridSizer(2, 10, 10);

    // Create labels and text controls
    wxStaticText* tagLabel = new wxStaticText(currentPanel, wxID_ANY, "Tag :");
    wxTextCtrl* tagInput = new wxTextCtrl(currentPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

    wxStaticText* nameLabel = new wxStaticText(currentPanel, wxID_ANY, "Name :");
    wxTextCtrl* nameInput = new wxTextCtrl(currentPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

    wxStaticText* priceLabel = new wxStaticText(currentPanel, wxID_ANY, "Price :");
    wxTextCtrl* priceInput = new wxTextCtrl(currentPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

    wxButton* addConfirm = new wxButton(currentPanel, wxID_ANY, "Confirm");
    wxButton* backButton = new wxButton(currentPanel, wxID_ANY, "Back");

    // Align labels to the right, text inputs to the center
    panelSizer->Add(tagLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(tagInput, 0, wxALIGN_CENTER | wxALL, 10);

    panelSizer->Add(nameLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(nameInput, 0, wxALIGN_CENTER | wxALL, 10);

    panelSizer->Add(priceLabel, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(priceInput, 0, wxALIGN_CENTER | wxALL, 10);

    // Main vertical sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->AddStretchSpacer(1);                // Push everything down
    mainSizer->Add(panelSizer, 0, wxALIGN_CENTER | wxALL, 20);
    mainSizer->Add(addConfirm, 0, wxALIGN_CENTER | wxALL, 5); // Confirm button above
    mainSizer->AddStretchSpacer(1);                // Spacer between Confirm and Back
    mainSizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 5); // Back button below
    mainSizer->AddStretchSpacer(1);                // Push everything up

    // Binding
    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowManageMenu();
        });

    addConfirm->Bind(wxEVT_BUTTON, [this,tagInput,nameInput,priceInput](wxCommandEvent&) {     // รับข้อมูล -> เขียนลงไฟล์เลย
        // push the data(new menu) into menuList vector
       
        List temp;

        temp.tag = wxAtoi(tagInput->GetValue());
        temp.name = nameInput->GetValue();
        temp.price = wxAtoi(priceInput->GetValue());

        std::vector<List> menuList = loadListFromFile("menuList.txt");

        menuList.push_back(temp);

        saveListToFile(menuList, "menuList.txt");

        // Create a non-resizable mini window
        wxFrame* miniWindow = new wxFrame(this, wxID_ANY, "Announcement", wxDefaultPosition, wxSize(300, 200),
            wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
        miniWindow->SetBackgroundColour(*wxWHITE);
        miniWindow->CentreOnScreen();

        // Create a panel inside the mini window
        wxPanel* miniPanel = new wxPanel(miniWindow);

        // Create centered "NEW MENU ADDED!" text
        wxStaticText* successText = new wxStaticText(miniPanel, wxID_ANY, "NEW MENU ADDED !", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

        // Center the text using a vertical sizer
        wxBoxSizer* miniSizer = new wxBoxSizer(wxVERTICAL);
        miniSizer->AddStretchSpacer(1);               // Push content down
        miniSizer->Add(successText, 0, wxALIGN_CENTER | wxALL, 10);
        miniSizer->AddStretchSpacer(1);               // Push content up
        miniPanel->SetSizer(miniSizer);

        // Handle the exit event to return to ShowManageMenu
        miniWindow->Bind(wxEVT_CLOSE_WINDOW, [this, miniWindow](wxCloseEvent&) {
            miniWindow->Destroy();
            ShowManageMenu();
            });

        miniWindow->Show();
        });


    currentPanel->SetSizer(mainSizer);
    Layout();
}

void MenuFrame::ShowRemovePanel()
{
    if (currentPanel) {
        GetSizer()->Detach(currentPanel);
        currentPanel->Destroy();
    }

    currentPanel = new wxPanel(this);
    GetSizer()->Add(currentPanel, 1, wxEXPAND);
    currentPanel->SetBackgroundColour(wxColour(200, 255, 255));
    
    // Create BoxSiser for this panel
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // create controll for currentPanel
    wxTextCtrl* tagInput = new wxTextCtrl(currentPanel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    wxButton* removeConfirm = new wxButton(currentPanel, wxID_ANY, "Confirm");
    wxButton* backButton = new wxButton(currentPanel, wxID_ANY, "Back");

    // Add controls to the sizer
    mainSizer->Add(tagInput, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 400);
    mainSizer->Add(removeConfirm, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    mainSizer->AddStretchSpacer();  // Pushes the back button to the bottom
    mainSizer->Add(backButton, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);

    //Binding
    backButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
        ShowManageMenu();
        });

    removeConfirm->Bind(wxEVT_BUTTON, [this,tagInput](wxCommandEvent&) { // input from textCtrl

        int temptag = wxAtoi(tagInput->GetValue());
        std::vector<List> menuList = loadListFromFile("menuList.txt");
        for (int i = 0;i < menuList.size();i++) {
            if (menuList[i].tag == temptag) { menuList.erase(menuList.begin() + i); }
        }
        saveListToFile(menuList, "menuList.txt");

        // Create a non-resizable mini window
        wxFrame* miniWindow = new wxFrame(this, wxID_ANY, "Announcement", wxDefaultPosition, wxSize(300, 200),
            wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);
        miniWindow->SetBackgroundColour(*wxWHITE);
        miniWindow->CentreOnScreen();

        // Create a panel inside the mini window
        wxPanel* miniPanel = new wxPanel(miniWindow);

        // Create centered "NEW MENU ADDED!" text
        wxStaticText* successText = new wxStaticText(miniPanel, wxID_ANY, "MENU REMOVED !", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

        // Center the text using a vertical sizer
        wxBoxSizer* miniSizer = new wxBoxSizer(wxVERTICAL);
        miniSizer->AddStretchSpacer(1);               // Push content down
        miniSizer->Add(successText, 0, wxALIGN_CENTER | wxALL, 10);
        miniSizer->AddStretchSpacer(1);               // Push content up
        miniPanel->SetSizer(miniSizer);

        // Handle the exit event to return to ShowManageMenu
        miniWindow->Bind(wxEVT_CLOSE_WINDOW, [this, miniWindow](wxCloseEvent&) {
            miniWindow->Destroy();
            ShowManageMenu();
            });

        miniWindow->Show();
        });


    //Update layout
    currentPanel->SetSizer(mainSizer);

    Layout();
}






