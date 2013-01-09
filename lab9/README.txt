Joseph Corbisiero
jc3790
Lab 9

a)
BASIC4TRACE: (0xbffff9a0)->MyString(const char *)-creation of s1("one")
BASIC4TRACE: (0xbffff998)->MyString(const char *)-creation of s2("two")
BASIC4TRACE: (0xbffff9b0)->MyString(const MyString&)-copy constructor called because passing s1 by value, not reference to add()
BASIC4TRACE: (0xbffff9b8)->MyString(const MyString&)-copy constructor called because passing s2 by value, not reference to add()
BASIC4TRACE: (0xbffff948)->MyString(const char *)-creation of temp(" and ")
BASIC4TRACE: op+(const MyString&, const MyString&)-from adding s1+temp
BASIC4TRACE: (0xbffff8f8)->MyString()-from MyString temp in op+()
BASIC4TRACE: (0xbffff958)->MyString(const MyString&)-returning temp as a copy and not a reference from op+(), first time
BASIC4TRACE: (0xbffff8f8)->~MyString()-deallocating temp from op+()
BASIC4TRACE: op+(const MyString&, const MyString&)-add result of (s1+temp) to s2
BASIC4TRACE: (0xbffff8f8)->MyString()-from MyString temp in op+()
BASIC4TRACE: (0xbffff950)->MyString(const MyString&)-returning temp as a copy and not a reference from op+(), second time
BASIC4TRACE: (0xbffff8f8)->~MyString()-deallocating temp from op+()
BASIC4TRACE: (0xbffff9a8)->MyString(const MyString&)-returning a copy from add() to main
BASIC4TRACE: (0xbffff950)->~MyString()-deallocating memory that temp held in second call to op+()
BASIC4TRACE: (0xbffff958)->~MyString()-deallocating memory that temp held in first call to op+()
BASIC4TRACE: (0xbffff948)->~MyString()-temp deallocated
BASIC4TRACE: (0xbffff990)->MyString(const MyString&)-assigning return value of add to s3
BASIC4TRACE: (0xbffff9a8)->~MyString()
BASIC4TRACE: (0xbffff9b8)->~MyString()--deallocating memory from the copy of s2 that was passed by value
BASIC4TRACE: (0xbffff9b0)->~MyString()-deallocating memory from the copy of s1 that was passed by value
one and two-from cout line in main
BASIC4TRACE: (0xbffff990)->~MyString()-s3 deallocated
BASIC4TRACE: (0xbffff998)->~MyString()-s2 deallocated
BASIC4TRACE: (0xbffff9a0)->~MyString()-s1 deallocated

b)The change in the output of BASIC4TRACE was that there were 2 less calls to the copy constructor since s1 and s2 were being passed by reference and not by value and as a result 2 less calls to the destructor.

c) Specifying this option disables the program to omit creating a temporary which is only used to initialize another object of that type. This forces g++ to call the copy constructor in all cases. Comparing part b and part c, the output from part c) has 2 less call to the copy constructor and as a rsult 2 less call to the destructor.

Valgrind output:
==31356== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==31356== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==31356== Command: ./testdriver
==31356==
This should work without any memory leak.
==31356==
==31356== HEAP SUMMARY:
==31356==     in use at exit: 0 bytes in 0 blocks
==31356==   total heap usage: 57 allocs, 57 frees, 443 bytes allocated
==31356==
==31356== All heap blocks were freed -- no leaks are possible
==31356==
==31356== For counts of detected and suppressed errors, rerun with: -v
==31356== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)
