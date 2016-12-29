#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([ibus-libthai],
        m4_esyscmd([build-aux/git-version-gen]),
        [theppitak@gmail.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR(build-aux)
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([dist-xz no-dist-gzip])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_RANLIB

GETTEXT_PACKAGE="$PACKAGE_NAME"
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE",[The gettext domain])

AM_GNU_GETTEXT_VERSION([0.18.1])
AM_GNU_GETTEXT([external])


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([memmove memset setlocale])

PKG_CHECK_MODULES(IBUS, [ibus-1.0 >= 1.2.99])
PKG_CHECK_MODULES(GLIB, [glib-2.0])
PKG_CHECK_MODULES(GTK, [gtk+-3.0 >= 3.16])
PKG_CHECK_MODULES(LIBTHAI, [libthai >= 0.1.19])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/libthai.xml.in
                 setup/Makefile
                 icons/Makefile
                 po/Makefile.in])
AC_OUTPUT
