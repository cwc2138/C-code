Joseph Corbisiero
jc3790
Lab 5

Part a)I wrote shell script that takes an argument which is the port number and is used to help execute mdb-lookup-server-nc-1.c

Part b)These are the two files /bin/sh ./mdb-lookup-server-nc.sh 3894 that I found when I entered the command ps ajxfww. Of course there were a bunch of other files, but these were in the process tree that contained the ancestors and the children program.

Part c)I wrote an improved version of mdb-lookup-server-nc-1.c which asked the user for a port number and displayed the child's process ID and the port number on which it's listening. It checks on every iteration if a child process has terminated.

