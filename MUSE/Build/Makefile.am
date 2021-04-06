SUFFIXES = .c .h .y .l
ACLOCAL_AMFLAGS = -I m4
AM_YFLAGS = -d
bin_PROGRAMS = MUSE

MUSE_SOURCES = ../Sources/muse.c muse_bison.y muse_flex.l
BUILD_SOURCES = muse_bison.h
noinst_HEADERS = ../Sources/muse.h
MUSE_LDFLAGS = 
MUSE_CFLAGS = -lm
MUSE_LDADD = 

EXTRA_DIST = Makefile.dist configure.ac
CLEANFILES = *~

MAINTAINERCLEANFILES = aclocal.* config.* configure install* ltmain.sh mkinstalldirs libtool \
    *.cache *.h *.c *.m4 depcomp ylwrap compile *.log *.status compile Makefile missing *.o \
    *.in stamp-h1 .libs m4 ../Sources/stamp-h1 ../Sources/*config.h*

.PHONY: maintainer-clean-local
.PHONY: clean

maintainer-clean-local:
	-rm -rf m4

clean: maintainer-clean-local
	rm -rf $(MAINTAINERCLEANFILES)
