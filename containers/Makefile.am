# build libwin32container
ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS	= -I$(top_builddir)/litehtml -I$(top_builddir)/include
lib_LTLIBRARIES = libwxcontainer.la

libwxcontainer_la_SOURCES	= wx_container.cpp wx_container.h
libwxcontainer_la_LIBADD   	= $(top_builddir)/litehtml/libwxlitehtml.la

if USE_WINDRES
   libwxcontainer_la_LDFLAGS	= -no-undefined -version-info 1:0:0 -lgdi32
else
   libwxcontainer_la_LDFLAGS	= -no-undefined -version-info 1:0:0
endif
