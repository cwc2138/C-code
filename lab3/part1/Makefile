# Makefile

CC  = gcc
CXX = g++

INCLUDES =

# Compilation options:
# -g for debugging info and -Wall enables all warnings

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

#Linking options:
# -g for debugging info

LDFLAGS = -g

LDLIBS =  

mylist-test: mylist-test.o libmylist.a

mylist-test.o: mylist-test.c

libmylist.a: mylist-test.o
	ar rc libmylist.a mylist-test.o
	ranlib libmylist.a
	rm -f libmylist.o
	
#mylist-test.o

# mylist-test.o depends on mylis-test.c and mylist.h
#mylist-test.o: mylist-test.c mylist.h

# And the "clean" target is not a file name, so we tell make that
# it's a "phony" target.

.PHONY: clean
clean:
	rm -f *.o *~ a.out core mylist-test

# "all" target is useful if your Makefile builds multiple programs.
# Here we'll have it first do "clean", and rebuild the main target.

.PHONY: all
all: clean mylist-test
