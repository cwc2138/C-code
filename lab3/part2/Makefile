# Makefile

CC  = gcc
CXX = g++

INCLUDES = -I ../part1/

# Compilation options:
# -g for debugging info and -Wall enables all warnings

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

#Linking options:
# -g for debugging info

LDFLAGS = -g -L ../part1/

LDLIBS = -l mylist

revecho: revecho.o 

revecho.c: revecho.c

# And the "clean" target is not a file name, so we tell make that
# it's a "phony" target.

.PHONY: clean
clean:
	rm -f *.o *~ a.out core revecho

# "all" target is useful if your Makefile builds multiple programs.
# Here we'll have it first do "clean", and rebuild the main target.

.PHONY: all
all: clean revecho
