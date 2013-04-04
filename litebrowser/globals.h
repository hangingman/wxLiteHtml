#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define ISOLATION_AWARE_ENABLED		1

#define GDIPVER	0x0110

#include <wx/wx.h>

#ifdef __WXMSW__
  #include <commctrl.h>
  #include <gdiplus.h>
  #include <shlwapi.h>
  #include <Wininet.h>
#endif

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "litehtml.h"

#define TLB_USE_TXDIB
#define TLB_USE_CAIRO
#define TLB_NO_TLBPDK
#define TLB_USE_HTTPREADER

#endif /** _GLOBALS_H_ */
