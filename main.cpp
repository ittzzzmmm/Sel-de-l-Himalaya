#include "LoginFrame.h"

class RestaurantApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(RestaurantApp);

bool RestaurantApp::OnInit() {
    LoginFrame* frame = new LoginFrame("Restaurant Management Login");
    frame->Show(true);
    return true;
}
