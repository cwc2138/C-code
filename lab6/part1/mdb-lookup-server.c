
/*
 * mdb-lookup-server.c
 */

#include "mdb.h"
#include "mylist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>


#define KeyMax 5

static void die(const char *message)
{
    perror(message);
    exit(1); 
}

int main(int argc, char **argv)
{
	//ignore SIGPIPE so that we don't terminate when we call
	//send() on a disconnected socket.
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		die("signal() failed");

	//requires three command line arguments
	if (argc != 3) {
		fprintf(stderr, "%s\n", "usage: mdb-lookup-server <database_file> <portNum>");
		exit(1);
    	}

	int servSock; /*Socket descriptor for server*/
	int clntSock; /*Socket descriptor for client*/
	struct sockaddr_in echoServAddr; /*Local address*/
	struct sockaddr_in echoClntAddr; /*Client address*/
	unsigned short echoServPort; /* Server port*/
	unsigned int clntLen; /*Length of client address data structure*/
	char *dbName; /*database name*/

	dbName = argv[1]; /*Second arg: database*/
	echoServPort = atoi(argv[2]); /*Third arg: local port*/

	/* Create a socket for incoming connections */
	if((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		die("socket() failed");

	/*Construct local address structure */
	memset(&echoServAddr, 0, sizeof(echoServAddr)); /*Zero out structure*/
	echoServAddr.sin_family = AF_INET; /*Internet address family*/
	echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /*Any incoming interface*/
	echoServAddr.sin_port = htons(echoServPort); /*Local port*/

	/*Bind to the local address*/
	if(bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
		die("bind() failed");

	/*Mark the socket so it will listen for incoming connections*/
	if(listen(servSock, KeyMax) < 0)
		die("listen() failed");

	for(;;)/*Run forever*/
	{
		/*Set the size of the in-out parameter*/
		clntLen = sizeof(echoClntAddr);
		
		/*Wait for a client to connect*/
		if((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
		{
			die("accept failed");
		}
		
		/*clntSock is connected to a client */
		printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));		

	
		FILE *db = fopen(dbName, "rb"); //open the database
		if(db == NULL)
			die("db error");
	
		FILE *inputSock = fdopen(clntSock, "r"); // open in read, binary mode
		if (inputSock == NULL) 
			die("inputSock can't be opened");
		
		// read all records into memory
     		struct List list;
		initList(&list);
	
		struct MdbRec *r = NULL;
		struct Node *node = NULL;

		char name[16];
		char message[24];	
		
		while (fread(name, 16, 1, db) && fread(message, 24, 1, db)) {
			// allocate memory for a new record and copy into it the one
			r = malloc(sizeof(struct MdbRec));
			strncpy(r->name, name, 16);
			strncpy(r->msg, message, 24);	
			node = addAfter(&list, node, r);
			if(node == NULL)
			{
				perror("node was null");
				exit(1);
			}
		}		

		//see if fread() produced error
		if (ferror(inputSock)) 
			die("fgets produced error");


		// lookup loop
     		char line[1000];
    		char key[KeyMax + 1];
		char c;		
		while ( fgets(line, sizeof(line), inputSock) != NULL) {
			// must null-terminate the string manually after strncpy().
			strncpy(key, line, sizeof(key) - 1);
			key[sizeof(key) - 1] = '\0';

			// if newline is there, remove it.
			size_t last = strlen(key) - 1;
			if (key[last] == '\n')
				key[last] = '\0';

			// traverse the list, printing out the matching records
			struct Node *node = list.head;
			int recNo = 1;
			while (node) {
	    			struct MdbRec *rec = (struct MdbRec *)node->data;
	    			if (strstr(rec->name, key) || strstr(rec->msg, key)) {
					sprintf(line, "%4d: {%s} said {%s}\n", recNo, rec->name, rec->msg);
	   				send(clntSock, line, strlen(line), 0);
				}		
	    			node = node->next;
	    			recNo++;
			}
			//send an empty line
			char *emptyLine = "\r\n";
        		send( clntSock, emptyLine, strlen(emptyLine), 0 );	
			//close database file
		}
	
    		// see if fgets() produced error
    		if (ferror(inputSock)) {
			fclose(inputSock);
			die("socket error");
		}

    		//clean up and quit
     		// free all the records
    		traverseList(&list, &free);
		removeAllNodes(&list);
		fclose(db);
    		fclose(inputSock);
	}
    return 0;
}
