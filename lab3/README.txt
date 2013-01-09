Joseph Corbisiero
jc3790
Lab 3

mylist-test: creates a singly linked list which has the capability of adding nodes to the beginning of the list, addiing nodes after nodes, reversing the list, flipping the sign of the number entered as data, and popping/removing nodes from the list one by one of clearing the entire list.

output:
==18998== Memcheck, a memory error detector
==18998== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==18998== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==18998== Command: ./mylist-test
==18998== 
testing addFront(): 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing flipSignDouble(): -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0 
testing flipSignDouble() again: 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing findNode(): OK
popped 9.0, the rest is: [ 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 8.0, the rest is: [ 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 7.0, the rest is: [ 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 6.0, the rest is: [ 5.0 4.0 3.0 2.0 1.0 ]
popped 5.0, the rest is: [ 4.0 3.0 2.0 1.0 ]
popped 4.0, the rest is: [ 3.0 2.0 1.0 ]
popped 3.0, the rest is: [ 2.0 1.0 ]
popped 2.0, the rest is: [ 1.0 ]
popped 1.0, the rest is: [ ]
testing addAfter(): 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 
popped 1.0, and reversed the rest: [ 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 ]
popped 9.0, and reversed the rest: [ 2.0 3.0 4.0 5.0 6.0 7.0 8.0 ]
popped 2.0, and reversed the rest: [ 8.0 7.0 6.0 5.0 4.0 3.0 ]
popped 8.0, and reversed the rest: [ 3.0 4.0 5.0 6.0 7.0 ]
popped 3.0, and reversed the rest: [ 7.0 6.0 5.0 4.0 ]
popped 7.0, and reversed the rest: [ 4.0 5.0 6.0 ]
popped 4.0, and reversed the rest: [ 6.0 5.0 ]
popped 6.0, and reversed the rest: [ 5.0 ]
popped 5.0, and reversed the rest: [ ]
==18998== 
==18998== HEAP SUMMARY:
==18998==     in use at exit: 0 bytes in 0 blocks
==18998==   total heap usage: 18 allocs, 18 frees, 288 bytes allocated
==18998== 
==18998== All heap blocks were freed -- no leaks are possible
==18998== 
==18998== For counts of detected and suppressed errors, rerun with: -v
==18998== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)

revecho: using the library created from part1, revecho takes in commmand line arguments, displays them in reverse order, and will tell you if the word "dude" is present or not in the list.

dude found output:
==21116== Memcheck, a memory error detector
==21116== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==21116== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==21116== Command: ./revecho hello world dude
==21116== 
dude
world
hello

dude found
==21116== 
==21116== HEAP SUMMARY:
==21116==     in use at exit: 0 bytes in 0 blocks
==21116==   total heap usage: 3 allocs, 3 frees, 48 bytes allocated
==21116== 
==21116== All heap blocks were freed -- no leaks are possible
==21116== 
==21116== For counts of detected and suppressed errors, rerun with: -v
==21116== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)

dude not found output:
==21131== Memcheck, a memory error detector
==21131== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==21131== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==21131== Command: ./revecho hello world friend
==21131== 
friend
world
hello

dude not found
==21131== 
==21131== HEAP SUMMARY:
==21131==     in use at exit: 0 bytes in 0 blocks
==21131==   total heap usage: 3 allocs, 3 frees, 48 bytes allocated
==21131== 
==21131== All heap blocks were freed -- no leaks are possible
==21131== 
==21131== For counts of detected and suppressed errors, rerun with: -v
==21131== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)
