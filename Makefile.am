SUBDIRS = src setup icons po

EXTRA_DIST =	\
	build-aux/git-version-gen	\
	$(NULL)

dist-hook:
	echo $(VERSION) > $(distdir)/VERSION
