Joseph Corbisiero
jc3790
Lab 6

Part 1)I created a mdb-lookup-server which listened on a port. The client would connect through netcat and enter search terms from a separate terminal while connected to the same port and get the search results

Part 2)I created a program similar to wget. The program makes a socket connection to the host and port and then requests an html file using HTTP 1.o protocol. The server terminates the socket connection after sending the HTML file. After terminating the HTML file will be in the directory containing the website's code that was chosen from the command line.
