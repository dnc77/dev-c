# History of changes:
#
# 27 Mar 2023              created

# Get global definitions makefile.
MKPATH                     := $(shell dirname\
                                 $(realpath $(lastword $(MAKEFILE_LIST)))\
                              )
include                    $(MKPATH)/../../../../makefile.def

LIBCATEGORY                := $(LIBCAT_DEVTOOLS)
PRJMAIN                    := $(LIBLOG_LOGGER)

# Project root path
PRJROOTDIR                 := $(TOPSRCDIR)$(TOPLIB)/$(LIBCATEGORY)/$(PRJMAIN)/

# Main build directories
INCDIR                     := $(TOPINCDIR)
BINDIR                     := $(TOPBINDIR)
LIBDIR                     := $(TOPLIBDIR)
SRCDIR                     := $(PRJROOTDIR)
OBJDIR                     := $(PRJROOTDIR)$(TOPOBJ)/

# Main output directories
BINDIR_DBG64               := $(BINDIR)$(X64DEBUG)/
BINDIR_REL64               := $(BINDIR)$(X64REL)/
LIBDIR_DBG64               := $(LIBDIR)$(X64DEBUG)/
LIBDIR_REL64               := $(LIBDIR)$(X64REL)/
OBJDIR_DBG64               := $(OBJDIR)$(X64DEBUG)/
OBJDIR_REL64               := $(OBJDIR)$(X64REL)/

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
LOGGER_INCDIR              := $(INCDIR)$(LIBCATEGORY)/

# Individual project source locations
LOGGER_SRCDIR              := $(SRCDIR)

# Individual project include files
LOGGERINC                  := $(LOGGER_INCDIR)logger.h

# Individual project source files
LOGGERSRC                  := $(LOGGER_SRCDIR)logger.c

# Project object files
LOGGER_OBJ_DBG64           := $(OBJDIR_DBG64)$(LOGGER).o
LOGGER_OBJ_REL64           := $(OBJDIR_REL64)$(LOGGER).o

# Project library link options
# Libraries:
# m - math library
# dl - dynamic loading library
LOGGER_LNKLIB_DBG64        :=
LOGGER_LNKLIB_REL64        :=

# Project output files
LOGGER_DBG64               := $(LIBDIR_DBG64)$(PRJMAIN).a
LOGGER_REL64               := $(LIBDIR_REL64)$(PRJMAIN).a

# Project dependencies
LOGGERDEP_DBG64            := 
LOGGERDEP_REL64            := 

# Individual project type compiler options
OBJGCCOPT_DBG64            := $(GCCDEBUG) $(GCCCOMPILEONLY) $(GCCWARNALL) \
                              $(GCCX64) $(GCCINCDIR)$(LOGGER_INCDIR)
OBJGCCOPT_REL64            := $(GCCCOMPILEONLY) $(GCCWARNALL) \
                              $(GCCX64) $(GCCINCDIR)$(LOGGER_INCDIR)
BINGCCOPT_DBG64            := $(GCCDEBUG) $(GCCWARNALL) $(GCCX64) \
                              $(GCCINCDIR)$(LOGGER_INCDIR)
BINGCCOPT_REL64            := $(GCCWARNALL) $(GCCX64) \
                              $(GCCINCDIR)$(LOGGER_INCDIR)

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

dbg : mkdbgdirs $(LOGGER_DBG64)

rel : mkreldirs $(LOGGER_REL64)

clean : roottest
	@$(RMDIR) $(LOGGER_DBG64)
	@$(RMDIR) $(LOGGER_REL64)
	@$(RMDIR) $(OBJDIR)

memchk :
	$(VALGRIND) $(VALGRINDOPTFULL) $(LOGGER_DBG64)

# logger debug build
$(LOGGER_DBG64) : $(LOGGERDEP_DBG64) $(LOGGERINC) $(LOGGERSRC)
	@$(ECHO) "dbg: Compiling and linking to $@"
	@$(GC) $(OBJGCCOPT_DBG64) $(LOGGERSRC) $(LOGGERDEP_DBG64)
	@$(MV) *.o $(OBJDIR_DBG64)
	@$(AR) rc $(LOGGER_DBG64) $(OBJDIR_DBG64)*.o

# logger release build
$(LOGGER_REL64) : $(LOGGERDEP_REL64) $(LOGGERINC) $(LOGGERSRC)
	@$(ECHO) "rel: Compiling and linking to $@"
	@$(GC) $(OBJGCCOPT_REL64) $(LOGGERSRC) $(LOGGERDEP_REL64)
	@$(MV) *.o $(OBJDIR_REL64)
	@$(AR) rc $(LOGGER_REL64) $(OBJDIR_REL64)*.o

