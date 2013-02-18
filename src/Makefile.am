componentdir = $(datadir)/ibus/component

AM_CPPFLAGS = \
	-DLOCALEDIR=\"$(localedir)\" \
	-DCOMPONENTDIR=\"$(componentdir)\" \
	-DPKGDATADIR=\"$(pkgdatadir)\" \
	$(NULL)

libexec_PROGRAMS = ibus-engine-libthai

ibus_engine_libthai_SOURCES = \
	intl.h \
	engine.h \
	engine.c \
	main.c \
	thaikb.h \
	thaikb.c \
	utils.h \
	utils.c \
	$(NULL)

noinst_HEADERS = \
	intl.h \
	engine.h \
	thaikb.h \
	ibus_config.h \
	engine_const.h \
	utils.h \
	$(NULL)

ibus_engine_libthai_CFLAGS = \
	$(IBUS_CFLAGS)  \
	$(GLIB_CFLAGS) \
	$(LIBTHAI_CFLAGS) \
	$(NULL)

ibus_engine_libthai_LDADD = \
	$(IBUS_LIBS) \
	$(GLIB_LIBS) \
	$(LIBTHAI_LIBS) \
	libibus-libthai-config.a \
	$(NULL)

noinst_LIBRARIES = libibus-libthai-config.a

libibus_libthai_config_a_SOURCES = \
	ibus_config.c \
	$(NULL)

libibus_libthai_config_a_CFLAGS = \
	$(IBUS_CFLAGS)  \
	$(GLIB_CFLAGS) \
	$(LIBTHAI_CFLAGS) \
	$(NULL)

component_DATA = libthai.xml

EXTRA_DIST = libthai.xml.in

CLEANFILES = libthai.xml

libthai.xml: libthai.xml.in

SUFFIXES = .xml.in .xml
.xml.in.xml:
	( \
		libexecdir=${libexecdir}; \
		datadir=${datadir}; \
		pkgdatadir=${pkgdatadir}; \
		s=`cat $<`; \
		eval "echo \"$${s}\""; \
	) > $@

