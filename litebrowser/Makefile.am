bin_PROGRAMS		= litebrowser
litebrowser_SOURCES	= \
BrowserWnd.cpp   cairo_container.cpp  gdiplus_container.cpp     litebrowser.h \
BrowserWnd.h     cairo_container.h    gdiplus_container.h       			  \
HtmlViewWnd.cpp  dib.cpp              globals.h                 targetver.h   \
HtmlViewWnd.h    dib.h                                                        \
ToolbarWnd.cpp   downloader.cpp       litebrowser.cpp           memdc.cpp     \
ToolbarWnd.h     downloader.h         memdc.h			        wxTxDIB.cpp   \
wxTxDIB.h

ACLOCAL_AMFLAGS		= -I m4
AM_CXXFLAGS		= @WX_CXXFLAGS_ONLY@ -I$(top_builddir)/litehtml -I$(top_builddir)/include -I$(top_builddir)/containers $(cairo_CFLAGS) -DNO_TOOLBAR
litebrowser_LDADD	= @WX_LIBS@ $(top_builddir)/litehtml/libwxlitehtml.la  $(top_builddir)/containers/libwxcontainer.la $(cairo_LIBS)

#litebrowser_rc.o : $(top_builddir)/libtebrowser/litebrowser.rc
#	@WX_RESCOMP@ -i $^ -O coff -o $@