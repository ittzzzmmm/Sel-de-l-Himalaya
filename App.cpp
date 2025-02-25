#include "App.h"
#include "MenuFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MenuFrame* mainFrame = new MenuFrame("Chan-O-Char");
	mainFrame->SetClientSize(1200, 900);
	mainFrame->Center();
	mainFrame->Show();
    return true;
}
