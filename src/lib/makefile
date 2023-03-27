# History of changes:
#
# 27 Mar 2023              created

# Get global definitions makefile.
MKPATH                     := $(shell dirname\
                                 $(realpath $(lastword $(MAKEFILE_LIST)))\
                              )/
include $(MKPATH)../../makefile.def

# Project root path
PRJROOTDIR                 := $(MKPATH)

# All library directories
LIBDTDIR                  := $(PRJROOTDIR)$(LIBCAT_DEVTOOLS)/
LIBALLDIR                  := $(LIBDTDIR)

# All make files
LOGGERMAKE                 := $(LIBDTDIR)$(LIBLOG_LOGGER)/makefile
ALLMAKE                    := $(LOGGERMAKE)

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

