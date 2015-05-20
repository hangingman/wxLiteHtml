#include "litebrowser.h"

#ifndef __WXMSW__
//  #include"litebrowser.xpm"
#endif

wxLiteBrowser::wxLiteBrowser(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
     wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE) {

     // icon setting
#ifdef __WXMSW__
     SetIcon(wxICON(litebrowser));
#else
//   SetIcon(wxICON(litebrowser));
#endif
     // set statusbar
     this->CreateStatusBar(2);
}

wxLiteBrowser::~wxLiteBrowser() {
}
