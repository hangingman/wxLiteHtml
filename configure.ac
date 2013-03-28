#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([libwxlitehtml], [1.0.0], [newserver002@gmail.com])
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR([containers/win32_container.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([select])

AC_CONFIG_FILES([Makefile
                 containers/Makefile
                 litehtml/Makefile
		 litebrowser/Makefile])
AC_OUTPUT
