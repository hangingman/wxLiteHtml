/*
 * Copyright (C) 2011-2015 Hiroyuki Nagata
 *
 * Contributor:
 *	Hiroyuki Nagata <newserver002@gmail.com>
 */

#include "litebrowser.h"

class wxMain: public wxApp {

public:
  virtual bool OnInit();
  virtual int OnExit();
  wxLiteBrowser* liteBrowser;
};

IMPLEMENT_APP(wxMain)

bool wxMain::OnInit() {

    if (!wxApp::OnInit())
	 return false;
     
    liteBrowser = new wxLiteBrowser(NULL, wxID_ANY, wxEmptyString);
    SetTopWindow(liteBrowser);
    liteBrowser->Show();
    return true;
}

int wxMain::OnExit() {
     return 0;
}
