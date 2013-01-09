Joseph Corbisiero
jc3790
Lab 4

This program takes in the database file as the command line argument. The database contains records of people's names and their messages. This program allows you to enter any string up to 1000, but it will be reduced t a max of the first 5 chars and that will be used to search any name or message containing a match. If you hit enter it will shows all the records in the database. If you hit CTRL-D then the program will terminate.

My record that I entered was name: Mama, msg: knock you out.

output:
==4137== Memcheck, a memory error detector
==4137== Copyright (C) 2002-2009, and GNU GPL'd, by Julian Seward et al.
==4137== Using Valgrind-3.6.0.SVN-Debian and LibVEX; rerun with -h for copyright info
==4137== Command: ./mdb-lookup my-md
==4137==

lookup: hey
 1: {joe} said {hello}
 2: {hal} said {heyyy}

lookup: hey
 2: {hal} said {heyyy}

lookup: he
 1: {joe} said {hello}
 2: {hal} said {heyyy}

lookup: 
 1: {joe} said {hello}
 2: {hal} said {heyyy}

lookup: ==4137== 
==4137== HEAP SUMMARY:
==4137==     in use at exit: 0 bytes in 0 blocks
==4137==   total heap usage: 9 allocs, 9 frees, 689 bytes allocated
==4137== 
==4137== All heap blocks were freed -- no leaks are possible
==4137== 
==4137== For counts of detected and suppressed errors, rerun with: -v
==4137== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)

