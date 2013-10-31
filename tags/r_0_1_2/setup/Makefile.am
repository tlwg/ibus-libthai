AM_CPPFLAGS = \
	-DLOCALEDIR=\"$(localedir)\" \
	-DCOMPONENTDIR=\"$(componentdir)\" \
	-DPKGDATADIR=\"$(pkgdatadir)\" \
	$(NULL)

libexec_PROGRAMS = ibus-setup-libthai

ibus_setup_libthai_SOURCES = \
	setup.c \
	dlg_setup.c \
	$(NULL)

noinst_HEADERS = \
	dlg_setup.h \
	$(NULL)

ibus_setup_libthai_CFLAGS = \
	$(IBUS_CFLAGS)  \
	$(GTK_CFLAGS) \
	-I$(top_srcdir)/src \
	$(NULL)

ibus_setup_libthai_LDADD = \
	$(IBUS_LIBS) \
	$(GTK_LIBS) \
	$(top_builddir)/src/libibus-libthai-config.a \
	$(NULL)

