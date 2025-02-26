#pragma once
#include <wx/wx.h>
#include <wx/textfile.h>
#include <vector>
#include <map>

class TableCount
{
public:

};
int LoadTableCount(const wxString& filename);
void SaveTableCount(const wxString& filename, int count);

