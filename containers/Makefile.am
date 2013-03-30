# build libwxlitehtml
ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS	= -I$(top_builddir)/litehtml -I$(top_builddir)/include
lib_LTLIBRARIES = libwin32container.la
libwin32container_la_SOURCES	= win32_container.cpp win32_container.h
libwin32container_la_LIBADD   	= $(top_builddir)/litehtml/libwxlitehtml.la
libwin32container_la_LDFLAGS	= -no-undefined -version-info 1:0:0 -lgdi32