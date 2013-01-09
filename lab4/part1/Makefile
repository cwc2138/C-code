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

LDFLAGS = -g -L ../../lab3/part1/

LDLIBS = -l mylist

#mdb-lookup depends on mdb-lookup.o
mdb-lookup: mdb-lookup.o 

# And the "clean" target is not a file name, so we tell make that
# it's a "phony" target.

.PHONY: clean
clean:
	rm -f *.o *~ a.out core mdb-lookup

# "all" target is useful if your Makefile builds multiple programs.
# Here we'll have it first do "clean", and rebuild the main target.

.PHONY: all
all: clean mdb-lookup
