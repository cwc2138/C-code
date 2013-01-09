Joseph Corbisiero
jc3790
Lab10

Part1: In this part I wrapped the legacy code from lab3 in a new C++ class so that the user sees a C++ implementation but under the hood, the class realy relies on C code. For the functions I wanted to call from the old code I used :: since the function names were the same, I needed to make sure the old functions were called. This linked list implementation only worked with MyString objects.

Part2: In this part I rewrote part1 using a template class which can take any object and did not rely on C code from lab3. This new implementation allows for any object to be used with the list cointer class from C++ std library. I did not reimplement the basic 4 since they were supplied by the list class. Everything else I reimplemented using a combination of list functions.

Part3: I felt like the class would be reimplemented better as a vector because it acts in a similar way to an array class. A vector's elements are ordered in a linear sequence very similar to a list. With vectors, you can have elements stored in a locations and be able to access it not only with iterators but also by using offsets on regular pointers to elements.

Part 1 Valgrind:
==2596== Memcheck, a memory error detector
==2596== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==2596== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==2596== Command: ./strlist-test
==2596==
{ 0 1 2 3 4 5 6 7 8 9 }
==2596==
==2596== HEAP SUMMARY:
==2596==     in use at exit: 0 bytes in 0 blocks
==2596==   total heap usage: 1,098 allocs, 1,098 frees, 11,067 bytes allocated
==2596==
==2596== All heap blocks were freed -- no leaks are possible
==2596==
==2596== For counts of detected and suppressed errors, rerun with: -v
==2596== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)

Part 2 Valgrind:
==2474== Memcheck, a memory error detector
==2474== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==2474== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==2474== Command: ./strlist-test
==2474==
{ 0 1 2 3 4 5 6 7 8 9 }
==2474==
==2474== HEAP SUMMARY:
==2474==     in use at exit: 0 bytes in 0 blocks
==2474==   total heap usage: 450 allocs, 450 frees, 11,457 bytes allocated
==2474==
==2474== All heap blocks were freed -- no leaks are possible
==2474==
==2474== For counts of detected and suppressed errors, rerun with: -v
==2474== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)

Part 3 Valgrind:
==2379== Memcheck, a memory error detector
==2379== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==2379== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==2379== Command: ./strlist-test
==2379==
[ 0 1 2 3 4 5 6 7 8 9 ]
==2379==
==2379== HEAP SUMMARY:
==2379==     in use at exit: 0 bytes in 0 blocks
==2379==   total heap usage: 186 allocs, 186 frees, 9,321 bytes allocated
==2379==
==2379== All heap blocks were freed -- no leaks are possible
==2379==
==2379== For counts of detected and suppressed errors, rerun with: -v
==2379== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)






