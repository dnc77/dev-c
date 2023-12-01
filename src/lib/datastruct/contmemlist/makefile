# History of changes:
#
# 28 Nov 2023              created

# Get global definitions makefile.
MKPATH                     := $(shell dirname\
                                 $(realpath $(lastword $(MAKEFILE_LIST)))\
                              )
include                    $(MKPATH)/../../../../makefile.def

LIBCATEGORY                := $(LIBCAT_DATASTRUCT)
PRJMAIN                    := $(LIBDAT_CONTMEMLIST)

# Project root path
PRJROOTDIR                 := $(TOPSRCDIR)$(TOPLIB)/$(LIBCATEGORY)/$(PRJMAIN)/

# Main build directories
INCDIR                     := $(TOPINCDIR)
BINDIR                     := $(TOPBINDIR)
LIBDIR                     := $(TOPLIBDIR)
SRCDIR                     := $(PRJROOTDIR)
OBJDIR                     := $(TOPOBJDIR)

# Main output directories
BINDIR_DBG64               := $(BINDIR)$(X64DEBUG)/
BINDIR_REL64               := $(BINDIR)$(X64REL)/
LIBDIR_DBG64               := $(LIBDIR)$(X64DEBUG)/
LIBDIR_REL64               := $(LIBDIR)$(X64REL)/
OBJDIR_DBG64               := $(OBJDIR)$(X64DEBUG)/$(PRJMAIN)/
OBJDIR_REL64               := $(OBJDIR)$(X64REL)/$(PRJMAIN)/

# Compilers and tools (uncomment to override makefile.def)
# CD                         := cd
# MV                         := mv
# MKDIR                      := mkdir -p
# RMDIR                      := rm -Rf
# AR                         := ar
# GCC                        := gcc
# TOUCH                      := touch
# ECHO                       := echo
# VALGRIND                   := valgrind
# VALGRINDOPTFULL            := --leak-check=full --track-origins=yes \
#                               --track-fds=yes
# VALGRINDOUTPUT             :=

# External libraries include locations

# External libraries library dirs

# External libraries

# Individual project include locations
DEVTOOLS_INCDIR            := $(INCDIR)$(LIBCAT_DEVTOOLS)/
DATASTRUCT_INCDIR          := $(INCDIR)$(LIBCAT_DATASTRUCT)/
TESTFAZE_INCDIR            := $(DEVTOOLS_INCDIR)
CONTMEMLIST_INCDIR         := $(DATASTRUCT_INCDIR)

# Individual project source locations
CONTMEMLIST_SRCDIR         := $(SRCDIR)

# Individual project include files
CONTMEMLISTINC             := $(CONTMEMLIST_INCDIR)contmemlist.h\
                              $(DEVTOOLS_INCDIR)commons.h

# Individual project source files
CONTMEMLISTSRC             := $(CONTMEMLIST_SRCDIR)contmemlist.c
TESTSSRC                   := $(CONTMEMLIST_SRCDIR)test.c

# Project object files
CONTMEMLIST_OBJ_DBG64      := $(OBJDIR_DBG64)$(PRJMAIN).o
CONTMEMLIST_OBJ_REL64      := $(OBJDIR_REL64)$(PRJMAIN).o

# Project library link options
# Libraries:
# m - math library
# dl - dynamic loading library
CONTMEMLIST_LNKLIB_DBG64   := $(LIBDIR_DBG64)$(LIBDVT_TESTFAZE)
CONTMEMLIST_LNKLIB_REL64   := $(LIBDIR_REL64)$(LIBDVT_TESTFAZE)

# Project output files
CONTMEMLIST_DBG64          := $(LIBDIR_DBG64)$(PRJMAIN).a
CONTMEMLIST_REL64          := $(LIBDIR_REL64)$(PRJMAIN).a
TESTS_DBG64                := $(LIBDIR_DBG64)$(TESTPREFIX)$(PRJMAIN).01
TESTS_REL64                := $(LIBDIR_REL64)$(TESTPREFIX)$(PRJMAIN).01

# Project dependencies
CONTMEMLISTDEP_DBG64       := 
CONTMEMLISTDEP_REL64       := 
TESTSDEP_DBG64             := $(LIBDIR_DBG64)/$(LIBDVT_TESTFAZE).a \
                              $(CONTMEMLIST_DBG64)
TESTSDEP_REL64             := $(LIBDIR_REL64)/$(LIBDVT_TESTFAZE).a \
                              $(CONTMEMLIST_REL64)

# Individual project type compiler options
OBJGCCOPT_DBG64            := $(GCCDEBUG) $(GCCCOMPILEONLY) $(GCCWARNALL) \
                              $(GCCX64) $(GCCPIC)\
                              $(GCCINCDIR)$(CONTMEMLIST_INCDIR) \
                              $(GCCINCDIR)$(TESTFAZE_INCDIR)
OBJGCCOPT_REL64            := $(GCCCOMPILEONLY) $(GCCWARNALL) \
                              $(GCCX64) $(GCCPIC) $(GCCINCDIR)$(CONTMEMLIST_INCDIR) \
                              $(GCCINCDIR)$(TESTFAZE_INCDIR)
BINGCCOPT_DBG64            := $(GCCDEBUG) $(GCCWARNALL) $(GCCX64) $(GCCPIC)\
                              $(GCCINCDIR)$(CONTMEMLIST_INCDIR) \
                              $(GCCINCDIR)$(TESTFAZE_INCDIR)
BINGCCOPT_REL64            := $(GCCWARNALL) $(GCCX64) $(GCCPIC)\
                              $(GCCINCDIR)$(CONTMEMLIST_INCDIR) \
                              $(GCCINCDIR)$(TESTFAZE_INCDIR)

rules : roottest
	@$(ECHO) '   all:    all projects (debug and release)'
	@$(ECHO) '   dbg:    all the debug projects'
	@$(ECHO) '   rel:    all the release projects'
	@$(ECHO) '   memchk: run a memory leak test on the tests'
	@$(ECHO) '   clean:  remove all'
	@$(ECHO) ""

roottest :
	@$(ECHO) 'Checking for ' $(GLOBALROOTDIR)
	@[ -d $(GLOBALROOTDIR) ]
	@$(ECHO) 'Checking for ' $(GLOBALROOTDIR)makefile.def
	@[ -f $(GLOBALROOTDIR)makefile.def ]
	@$(ECHO) 'Checking for ' $(PRJROOTDIR)makefile
	@[ -f $(PRJROOTDIR)makefile ]
	@$(ECHO) ""

# Create required directories
mkdbgdirs : roottest
	@$(MKDIR) $(LIBDIR_DBG64)
	@$(MKDIR) $(OBJDIR_DBG64)

mkreldirs : roottest
	@$(MKDIR) $(LIBDIR_REL64)
	@$(MKDIR) $(OBJDIR_REL64)

# All builds
all : dbg rel

dbg : mkdbgdirs $(CONTMEMLIST_DBG64) $(TESTS_DBG64)

rel : mkreldirs $(CONTMEMLIST_REL64) $(TESTS_REL64)

clean : roottest
	@$(RMDIR) $(CONTMEMLIST_DBG64)
	@$(RMDIR) $(CONTMEMLIST_REL64)
	@$(RMDIR) $(TESTS_DBG64)
	@$(RMDIR) $(TESTS_REL64)
	@$(RMDIR) $(OBJDIR)

memchk :
	$(VALGRIND) $(VALGRINDOPTFULL) $(TESTS_DBG64)

# contmemlist debug build
$(CONTMEMLIST_DBG64) : \
   $(CONTMEMLISTDEP_DBG64) $(CONTMEMLISTINC) $(CONTMEMLISTSRC)
	@$(ECHO) "dbg: Compiling and linking to $@"
	@$(GC) $(OBJGCCOPT_DBG64) $(CONTMEMLISTSRC) $(CONTMEMLISTDEP_DBG64)
	@$(MV) *.o $(OBJDIR_DBG64)
	@$(AR) rc $(CONTMEMLIST_DBG64) $(OBJDIR_DBG64)*.o

# contmemlist release build
$(CONTMEMLIST_REL64) : \
   $(CONTMEMLISTDEP_REL64) $(CONTMEMLISTINC) $(CONTMEMLISTSRC)
	@$(ECHO) "rel: Compiling and linking to $@"
	@$(GC) $(OBJGCCOPT_REL64) $(CONTMEMLISTSRC) $(CONTMEMLISTDEP_REL64)
	@$(MV) *.o $(OBJDIR_REL64)
	@$(AR) rc $(CONTMEMLIST_REL64) $(OBJDIR_REL64)*.o

# tests debug build
$(TESTS_DBG64) : $(TESTSDEP_DBG64) $(CONTMEMLISTINC) $(CONTMEMLISTSRC)
	@$(ECHO) "dbg: Compiling and linking to $@"
	@$(GC) $(BINGCCOPT_DBG64) $(TESTSSRC) $(TESTSDEP_DBG64) $(GCCOUTFILE)$@

# tests release build
$(TESTS_REL64) : $(TESTSDEP_REL64) $(CONTMEMLISTINC) $(CONTMEMLISTSRC)
	@$(ECHO) "rel: Compiling and linking to $@"
	@$(GC) $(BINGCCOPT_REL64) $(TESTSSRC) $(TESTSDEP_REL64) $(GCCOUTFILE)$@
	@$(STRIP) $@
