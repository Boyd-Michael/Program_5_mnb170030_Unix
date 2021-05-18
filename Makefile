#!/usr/bin/make -f
#
#Filename:	Makefile
#Date: 		04/17/2020
#Author:	Michael Boyd
#Email:		mnb170030@utdallas.edu
#Version:	1.0
#Copyright:	2020, All Rights Reserved
#
#Description:
#
#	Builds program 5
#
#
#


# Flags for C++
CC = g++
CCFLAGS = program5.h -Wall -I ~/include
CPPFLAGS = -I ~/include

# Flags for Linker
LINKERFLAGS = -L ~/lib

# Libraries flags
LIBRARIES = -l:librudeconfig.so

#Project's name
PROJECTNAME = Program5

# Source Files
SRC = program5.cc daemonRun.cc configFile.cc logFunc.cc inotifyFunc.cc

# Executable file
EXECFILE = prog5

# Object Files
OBJS = program5.o daemonRun.o configFile.o logFunc.o inotifyFunc.o

EXPORT = LD_LIBRARY_PATH=~/lib

#
.PHONY: clean backup

%o:%c
	export $(EXPORT)
	$(CC) -M -MF $*P $<
	$(CC) -C $(CCFLAGS) $(CCPFLAGS) $< -o $@

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#* program5.h.gch

$(EXECFILE):	 $(OBJS)
	$(CC) $(OBJS) $(LINKERFLAGS) $(LIBRARIES) -o $@

$(OBJS): $(SRC)
	$(CC) -c $(SRC) $(CCFLAGS)

setup:
	@echo export LD_LIBRARY_PATH=~/lib

backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date + '%Y.%m.%d-%H:%M:%S').tar.gz)/
	@tar -zcvf $(MKBKUPNAME) ../$(CURIDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Backup Complete
