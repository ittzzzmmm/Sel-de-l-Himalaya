#include <wx/wx.h>
#include <wx/listbox.h>
#include <fstream>
#include <map>

class MyFrame : public wxFrame {
private:
    wxListBox* menuList;
    wxStaticText* statText;
    std::map<std::string, int> salesData;

    void LoadMenu() {
        std::ifstream file("menu.txt");
        std::string item;
        while (getline(file, item)) {
            menuList->Append(item);
            salesData[item] = 0; // เริ่มต้นค่าสถิติเป็น 0
        }
        file.close();
    }

    void LoadSales() {
        std::ifstream file("sales.txt");
        std::string item;
        int count;
        while (file >> item >> count) {
            salesData[item] = count;
        }
        file.close();
    }

    void SaveSales() {
        std::ofstream file("sales.txt");
        for (const auto& pair : salesData) {
            file << pair.first << " " << pair.second << "\n";
        }
        file.close();
    }

    void OnSelect(wxCommandEvent& event) {
        wxString selected = menuList->GetStringSelection();
        if (!selected.IsEmpty()) {
            salesData[std::string(selected.mb_str())]++;
            SaveSales();
            UpdateStats();
        }
    }

    void UpdateStats() {
        wxString stats;
        for (const auto& pair : salesData) {
            stats += wxString::Format("%s: %d\n", pair.first, pair.second);
        }
        statText->SetLabel(stats);
    }

public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "ระบบร้านอาหาร", wxDefaultPosition, wxSize(400, 300)) {
        wxPanel* panel = new wxPanel(this);
        wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

        menuList = new wxListBox(panel, wxID_ANY);
        vbox->Add(menuList, 1, wxEXPAND | wxALL, 10);

        wxButton* selectBtn = new wxButton(panel, wxID_ANY, "ขายเมนูนี้");
        vbox->Add(selectBtn, 0, wxALIGN_CENTER | wxALL, 10);

        statText = new wxStaticText(panel, wxID_ANY, "สถิติการขาย", wxDefaultPosition, wxSize(300, 100));
        vbox->Add(statText, 0, wxALIGN_LEFT | wxALL, 10);

        panel->SetSizer(vbox);

        LoadMenu();
        LoadSales();
        UpdateStats();

        selectBtn->Bind(wxEVT_BUTTON, &MyFrame::OnSelect, this);
    }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MyFrame* frame = new MyFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);