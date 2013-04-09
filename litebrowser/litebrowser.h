#ifndef _LITEBROWER_H_
#define _LITEBROWER_H_

#include <wx/wx.h>

class wxLiteBrowser : public wxFrame {

 public:
  wxLiteBrowser(wxWindow* parent, int id, const wxString& title,
		const wxPoint& pos = wxDefaultPosition, const wxSize& size =
		wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE);
  ~wxLiteBrowser();
};

#endif /** _LITEBROWER_H_ */
