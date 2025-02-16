#ifndef LOGIN_FRAME_H
#define LOGIN_FRAME_H

#include <wx/wx.h>
#include <fstream>
#include <sstream>

class LoginFrame : public wxFrame {
public:
    LoginFrame(const wxString& title);

private:
    wxTextCtrl* usernameCtrl;
    wxTextCtrl* passwordCtrl;
    wxButton* loginButton;
    wxButton* registerButton;

    void OnLogin(wxCommandEvent& event);
    void OnRegister(wxCommandEvent& event);
    bool ValidateLogin(const wxString& username, const wxString& password);
    void RegisterUser(const wxString& username, const wxString& password);
};

#endif
