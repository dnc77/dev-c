# History of changes:
#
# 27 Mar 2023              created
# 28 Mar 2023              added VECTORMAKE and LIBDATDIR

# Get global definitions makefile.
MKPATH                     := $(shell dirname\
                                 $(realpath $(lastword $(MAKEFILE_LIST)))\
                              )/
include $(MKPATH)../../makefile.def

# Project root path
PRJROOTDIR                 := $(MKPATH)

# All library directories
LIBDVTDIR                  := $(PRJROOTDIR)$(LIBCAT_DEVTOOLS)/
LIBDATDIR                  := $(PRJROOTDIR)$(LIBCAT_DATASTRUCT)/
LIBALLDIR                  := $(LIBDVTDIR)

# All make files
LOGGERMAKE                 := $(LIBDVTDIR)$(LIBDVT_LOGGER)/makefile
TESTFAZEMAKE               := $(LIBDVTDIR)$(LIBDVT_TESTFAZE)/makefile
VECTORMAKE                 := $(LIBDATDIR)$(LIBDAT_VECTOR)/makefile
ALLMAKE                    := $(LOGGERMAKE) $(TESTFAZEMAKE) $(VECTORMAKE)

# Compilers and tools (uncomment to override makefile.def)
# CD                         := cd
# MV                         := mv
# MKDIR                      := mkdir -p
# RMDIR                      := rm -Rf
# AR                         := ar
# GCC                        := gcc
# TOUCH                      := touch
# ECHO                       := echo

#
# First rule (parameters)
#

rules :
	@$(ECHO) '   all:    all projects (debug and release)'
	@$(ECHO) '   dbg:    all the debug projects'
	@$(ECHO) '   rel:    all the release projects'
	@$(ECHO) '   clean:  remove all'
	@$(ECHO) ""

# All builds
all : clean dbg rel

clean dbg rel :
	@for mk in $(ALLMAKE); do\
		$(ECHO) "Making " $$mk;\
		$(MAKE) -s -f $$mk $@;\
	done
	@if [ $@ = clean ];\
	then\
		$(RMDIR) $(TOPLIBDIR);\
	fi\

