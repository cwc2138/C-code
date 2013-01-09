# Makefile

CC  = gcc
CXX = g++

INCLUDES = -I ../../lab3/part1/

# Compilation options:
# -g for debugging info and -Wall enables all warnings

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

#Linking options:
# -g for debugging info

LDFLAGS = -g 

LDLIBS =

#create two executables, mdb-lookup-server-nc-1 and mdb-lookup-server-nc-2
.PHONY: default
default: mdb-lookup-server-nc-1 mdb-lookup-server-nc-2

#mdb-lookup-server-nc-1 depends on mdb-lookup-server-nc-1.c 
mdb-lookup-server-nc-1: mdb-lookup-server-nc-1.c

#mdb-lookup-server-nc-2 depends on mdb-lookup-server-nc-2.c
mdb-lookup-server-nc-2: mdb-lookup-server-nc-2.c

.PHONY: clean
clean:
	rm -f *.o *~ a.out core main mdb-lookup-server-nc-1 mdb-lookup-server-nc-2 mypipe*

# "all" target is useful if your Makefile builds multiple programs.
# Here we'll have it first do "clean", and rebuild the main target.
.PHONY: all
all: clean default
