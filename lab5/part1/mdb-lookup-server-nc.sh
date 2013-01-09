#!/bin/sh
#take port number an argument, if there is no argument then it exits
if [ $# -eq 0 ] 
then
echo "Port number needed: ./mdb-lookup-server-nc.sh <port>"
exit 1;
fi

#makes the pipe
mkfifo mypipe-$$

#to get the server going
cat mypipe-$$ | nc -l $1 | /home/jae/cs3157-pub/bin/mdb-lookup-cs3157 > mypipe-$$

#this will remove all file named mypipe
rm -f mypipe-*


