# History of changes:
#
# 27 Mar 2023              created
# 28 Mar 2023              unstrip release library
# 30 Mar 2023              testfaze now depends on commons.h

# Get global definitions makefile.
MKPATH                     := $(shell dirname\
                                 $(realpath $(lastword $(MAKEFILE_LIST)))\
                              )
include                    $(MKPATH)/../../../../makefile.def

LIBCATEGORY                := $(LIBCAT_DEVTOOLS)
PRJMAIN                    := $(LIBDVT_TESTFAZE)

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
TESTFAZE_INCDIR            := $(INCDIR)$(LIBCATEGORY)/
VECTOR_INCDIR              := $(DATASTRUCT_INCDIR)

# Individual project source locations
TESTFAZE_SRCDIR            := $(SRCDIR)

# Individual project include files
TESTFAZEINC                := $(TESTFAZE_INCDIR)testfaze.h \
                              $(DEVTOOLS_INCDIR)commons.h

# Individual project source files
TESTFAZESRC                := $(TESTFAZE_SRCDIR)testfaze.c

# Project object files
TESTFAZE_OBJ_DBG64         := $(OBJDIR_DBG64)$(PRJMAIN).o
TESTFAZE_OBJ_REL64         := $(OBJDIR_REL64)$(PRJMAIN).o

# Project library link options
# Libraries:
# m - math library
# dl - dynamic loading library
TESTFAZE_LNKLIB_DBG64      :=
TESTFAZE_LNKLIB_REL64      :=

# Project output files
TESTFAZE_DBG64             := $(LIBDIR_DBG64)$(PRJMAIN).a
TESTFAZE_REL64             := $(LIBDIR_REL64)$(PRJMAIN).a

# Project dependencies
TESTFAZEDEP_DBG64          := 
TESTFAZEDEP_REL64          := 

# Individual project type compiler options
OBJGCCOPT_DBG64            := $(GCCDEBUG) $(GCCCOMPILEONLY) $(GCCWARNALL) \
                              $(GCCX64) $(GCCINCDIR)$(TESTFAZE_INCDIR)
OBJGCCOPT_REL64            := $(GCCCOMPILEONLY) $(GCCWARNALL) \
                              $(GCCX64) $(GCCINCDIR)$(TESTFAZE_INCDIR)
BINGCCOPT_DBG64            := $(GCCDEBUG) $(GCCWARNALL) $(GCCX64) \
                              $(GCCINCDIR)$(TESTFAZE_INCDIR)
BINGCCOPT_REL64            := $(GCCWARNALL) $(GCCX64) \
                              $(GCCINCDIR)$(TESTFAZE_INCDIR)

rules : roottest
	@$(ECHO) '   all:    all projects (debug and release)'
	@$(ECHO) '   dbg:    all the debug projects'
	@$(ECHO) '   rel:    all the release projects'
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

dbg : mkdbgdirs $(TESTFAZE_DBG64)

rel : mkreldirs $(TESTFAZE_REL64)

clean : roottest
	@$(RMDIR) $(TESTFAZE_DBG64)
	@$(RMDIR) $(TESTFAZE_REL64)
	@$(RMDIR) $(OBJDIR)

memchk :
	$(VALGRIND) $(VALGRINDOPTFULL) $(TESTFAZE_DBG64)

# testfaze debug build
$(TESTFAZE_DBG64) : $(TESTFAZEDEP_DBG64) $(TESTFAZEINC) $(TESTFAZESRC)
	@$(ECHO) "dbg: Compiling and linking to $@"
	@$(GC) $(OBJGCCOPT_DBG64) $(TESTFAZESRC) $(TESTFAZEDEP_DBG64)
	@$(MV) *.o $(OBJDIR_DBG64)
	@$(AR) rc $(TESTFAZE_DBG64) $(OBJDIR_DBG64)*.o

# testfaze release build
$(TESTFAZE_REL64) : $(TESTFAZEDEP_REL64) $(TESTFAZEINC) $(TESTFAZESRC)
	@$(ECHO) "rel: Compiling and linking to $@"
	@$(GC) $(OBJGCCOPT_REL64) $(TESTFAZESRC) $(TESTFAZEDEP_REL64)
	@$(MV) *.o $(OBJDIR_REL64)
	@$(AR) rc $(TESTFAZE_REL64) $(OBJDIR_REL64)*.o

