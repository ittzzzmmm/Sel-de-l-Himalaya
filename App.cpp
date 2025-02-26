#include "App.h"


wxIMPLEMENT_APP(RestaurantApp);

bool RestaurantApp::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Show(true);
    return true;
}