#pragma once
#include<wx/wx.h>
class MenuFrame : public wxFrame
{
public:
	MenuFrame(const wxString& title);
	void ShowMain();
	void ShowManageMenu();
	void ShowAddPanel();
	void ShowRemovePanel();
private:
	wxPanel* currentPanel;
};
