#include "TableCount.h"

int LoadTableCount(const wxString& filename)
{
    if (wxFileExists(filename)) {
        wxTextFile file;
        if (file.Open(filename)) {
            wxString line = file.GetFirstLine();
            int count = wxAtoi(line);
            file.Close();
            return count;
        }
    }
    return 6;// Default to 6 tables if file not found or error
}

void SaveTableCount(const wxString& filename, int count)
{
    wxTextFile file;
    if (wxFileExists(filename)) {
        file.Open(filename);
        file.Clear();
    }
    else {
        file.Create(filename);
    }
    file.AddLine(wxString::Format("%d", count));
    file.Write();
    file.Close();
}
