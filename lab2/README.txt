Joseph Corbisiero
jc3790
Lab 2

isort: This program creates an array size from the user. Random integers are assigned to the array and two copies are made. One copy is then sorted in ascending order and the second copy is in descending order.

output from valgrind:
==26922== Memcheck, a memory error detector
==26922== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==26922== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==26922== Command: ./isort
==26922==
What size array would you like: 5
Printing original array:
randArray[0] = 1217039665
randArray[1] = 1030716086
randArray[2] = 1720732224
randArray[3] = 1614283264
randArray[4] = 141811244

Array in ascending order:
duplicArray1[0] = 141811244
duplicArray1[1] = 1030716086
duplicArray1[2] = 1217039665
duplicArray1[3] = 1614283264
duplicArray1[4] = 1720732224

Array in descending order:
duplicArray2[0] = 1720732224
duplicArray2[1] = 1614283264
duplicArray2[2] = 1217039665
duplicArray2[3] = 1030716086
duplicArray2[4] = 141811244
==26922== 
==26922== HEAP SUMMARY:
==26922==     in use at exit: 0 bytes in 0 blocks
==26922==   total heap usage: 3 allocs, 3 frees, 60 bytes allocated
==26922== 
==26922== All heap blocks were freed -- no leaks are possible
==26922== 
==26922== For counts of detected and suppressed errors, rerun with: -v
==26922== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)


twecho: This program takes in command line arguments and prints out the original argument followed by a space and then the same argument except in all caps. The actual command to execute the program "./twecho" is ignored.

output of valgrind:
==27137== Memcheck, a memory error detector
==27137== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==27137== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==27137== Command: ./twecho hello world dude
==27137== 
hello HELLO
world WORLD
dude DUDE
==27137== 
==27137== HEAP SUMMARY:
==27137==     in use at exit: 0 bytes in 0 blocks
==27137==   total heap usage: 5 allocs, 5 frees, 66 bytes allocated
==27137== 
==27137== All heap blocks were freed -- no leaks are possible
==27137== 
==27137== For counts of detected and suppressed errors, rerun with: -v
==27137== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)


My solution is working. I originally had problems with valgrind because it did not like what I had in the twecho program. It complained that I still had reachable memory and that not everything was allocated and that there were unitialized values. After some thinking, I realized I never put in any end of characters for the arrays. Once I did that it fixed the memory issues.
