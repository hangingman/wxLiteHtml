bin_PROGRAMS		= litebrowser
litebrowser_SOURCES	= \
main.cpp litebrowser.cpp litebrowser.h
#BrowserWnd.cpp   cairo_container.cpp  wxDC_container.cpp     litebrowser.h \
#BrowserWnd.h     cairo_container.h    wxDC_container.h       		   \
#HtmlViewWnd.cpp  dib.cpp              globals.h                 targetver.h   \
#HtmlViewWnd.h    dib.h                                                        \
#ToolbarWnd.cpp   downloader.cpp       litebrowser.cpp           memdc.cpp     \
#ToolbarWnd.h     downloader.h         memdc.h			wxTxDIB.cpp   \
#wxTxDIB.h

ACLOCAL_AMFLAGS		= -I m4
AM_CXXFLAGS		= @WX_CXXFLAGS_ONLY@ -I$(top_builddir)/litehtml -I$(top_builddir)/include -I$(top_builddir)/containers $(cairo_CFLAGS) -DNO_TOOLBAR
litebrowser_LDADD	= @WX_LIBS@ $(top_builddir)/litehtml/libwxlitehtml.la  $(top_builddir)/containers/libwxcontainer.la $(cairo_LIBS)

if USE_WINDRES
litebrowser_LDADD	+= litebrowser_rc.o
endif

litebrowser_rc.o : $(top_builddir)/litebrowser/litebrowser.rc
	@WX_RESCOMP@ -i $^ -O coff -o $@