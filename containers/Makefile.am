# build libwxlitehtml
ACLOCAL_AMFLAGS = -I m4
lib_LTLIBRARIES = libwin32_container.la
libwin32_container_la_SOURCES	= win32_container.cpp win32_container.h
libwin32_container_LDADD   	= $(top_builddir)/litehtml/libwxlitehtml.la
libwin32_container_la_LDFLAGS	= -no-undefined -version-info 1:0:0 -lgdi32