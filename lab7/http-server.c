#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>

#define KEYMAX 5

void die(char *message)
{
	perror(message);
	exit(1);
}

void displaySiteError(int errorCode, char *errorMes, char *clntAddr, char *req, int clntSock)
{
	//keep track of request
	printf("%s \"%s\" %d %s\n", clntAddr, req, errorCode, errorMes);
	//optimal thing
	char BUFFER[4096];
	//display error page
	sprintf(BUFFER,"HTTP/1.0 %d %s \r\n\r\n <html><body><h1>%d %s</h1></body></html>", errorCode, errorMes, errorCode, errorMes);
	send(clntSock, BUFFER, strlen(BUFFER), 0);
}

void displayMDBResults(int clntSock, int mdbSock, int flag, char *requestURI, FILE *mdbFile){
	char *form = 
		"<html><body><h1>mdb-lookup</h1>\n"
          	"<p>\n"
          	"<form method=GET action=/mdb-lookup>\n"
          	"lookup: <input type=text name=key>\n"
          	"<input type=submit>\n"
          	"</form>\n"
          	"<p>\n</body></html>"
          	;

	const char *header = "HTTP/1.0 200 OK \r\n\r\n";
       	int headerLen = strlen(header);
     	//send the header
	if(send(clntSock, header, strlen(header), 0) != headerLen){
        	printf("send() error with header");
               	return;
       	}

       	int formLen = strlen(form);
       	int sendSockLen;
       	if((sendSockLen = send(clntSock, form, formLen, 0)) != formLen){
        	printf("send() error with form on search page");
		return;
       	}

       	//flag used with displaying the right site error with /mdb-lookup or when the actual term is being searched
	if(flag == 0){
        	return;
	}

       	//locate term as been entered whether empty of full of charactersr * If searchterm is present */
       	char *locateTerm = strrchr(requestURI, '=');
       	if(locateTerm == NULL){
               return;
       	}
	
       	locateTerm++;

       	int termLen = strlen(locateTerm);
       	if(send(mdbSock, locateTerm, termLen, 0) != termLen){
        	printf("send() error wirh search term");
       		return;
       	}

       	send(mdbSock, "\n", 1, 0);

	//html code for the table to display the search results
       	const char *htmlTableOpened = "<html><body><table border=''>";
       	const char *htmlTableClosed = "</table></body></html>";
        //begin to send the html code
	send(clntSock, htmlTableOpened, strlen(htmlTableOpened), 0);

	//give buffer array a large enough amount of memory just in case
       	char BUFFER[100];
	//this is the max length of characters that will be in the row 
       	char rowMaxLen[100];
       	int num = 1;
	//alternate the colors for each row containg a match to the search term
       	while(fgets(BUFFER, sizeof(BUFFER), mdbFile) != NULL){
        	if((BUFFER[0] == '\r' && BUFFER[1] =='\n') || BUFFER[0] == '\n'){
                	break;
		}
		//This is to make it alternate yellow and white
               	if(num % 2 == 0){
                	sprintf(rowMaxLen, "<tr><td bgcolor='yellow'>%s</tr></td>", BUFFER);
                }else{
                	sprintf(rowMaxLen, "<tr><td>%s</tr></td>", BUFFER);
               	}
		
		send(clntSock, rowMaxLen, strlen(rowMaxLen), 0);
             	num++;
       	}
	//make sure html code for the table is closed so it will display
       	send(clntSock, htmlTableClosed, strlen(htmlTableClosed), 0);
	close(clntSock);
}

void webBrowserRequest(int clntSock, char *clntAddr, char *webRoot, int mdbSock, FILE *mdbFile){
		//open from clntSock
		FILE *clntFile = fdopen(clntSock, "r");
		char BUFFER[1000];
		char BUFFERcpy[1000];
		
		//get from the clntFile
		fgets(BUFFER, sizeof(BUFFER), clntFile);
		strncpy(BUFFERcpy, BUFFER, sizeof(BUFFER));
		
		//locate last occurence of '\r'
		char *str = strrchr(BUFFER,'\r');
		//make sure terminating char is at the end
		if(str != NULL){
			*str = '\0';
		}

		char *token_separators = "\t \r\n";
       		char *method = strtok(BUFFERcpy, token_separators);
       		char *requestURI = strtok(NULL, token_separators);
       		char *httpVersion = strtok(NULL, token_separators);
		
		//testing different cases of bad requests
		//if something goes wrong close the clntFile
		if(method == NULL || requestURI == NULL || httpVersion == NULL){
              		fclose(clntFile);
               		return;
       		}	
		
		//checking for GET string
       		if(strncmp(method, "GET", 3) != 0){
               		displaySiteError(501, "Not Implemented", clntAddr, BUFFER, clntSock);
               		fclose(clntFile);
               		return;
       		}
		
		//checking for last '/'
      		if((strchr(requestURI, '/')) != requestURI){
               		displaySiteError( 400, "Bad request", clntAddr, BUFFER, clntSock);
              		fclose(clntFile);
               		return;
       		}	
		
		//check HTTP version
       		if((strncmp(httpVersion, "HTTP/1.0", 8) != 0) && (strncmp(httpVersion, "HTTP/1.1", 8) !=0)){
               		displaySiteError( 501, "Not Implemented", clntAddr, BUFFER, clntSock);
               		fclose(clntFile);
               		return;
       		}
		
		//mdb-case error checking
		//search query test
		if(strncmp(requestURI, "/mdb-lookup?key=", 16) == 0){
               		displayMDBResults(clntSock, mdbSock, 1, requestURI, mdbFile);
               		fclose(clntFile);
			printf("%s \"%s\" %d %s\n", clntAddr, "OK", 200, BUFFER);
               		return;
       		}
		
		//mdb-lookup page test
		if(strncmp(requestURI, "/mdb-lookup", 11) == 0){
        	       	displayMDBResults(clntSock, mdbSock, 0, "", mdbFile);
               		fclose(clntFile);
			printf("%s \"%s\" %d %s\n", clntAddr, "OK", 200, BUFFER);
               		return;
      	 	}
		
		/////////////////
		char *string = strrchr(requestURI, '\0');
       		char *missingTerm = "\0";
		//used to add index.html to the end of the request from the web browser as if it was there although the user did not enter it
		int extraLen = 1;      
		//check for last '/', treat it as if index.html were at the end
		if(strrchr(requestURI, '/') == (string-1)){
        		missingTerm = "index.html\0";
               		extraLen = strlen(missingTerm) + 1;
       		}
		
		//allocate memory for th newURI
       		char *newURI = (char*)malloc((strlen(requestURI) + extraLen)*sizeof(char));
     		if(newURI == NULL){
               		printf("malloc failed");
			fclose(clntFile);
               		return;
       		}
       		
		sprintf(newURI, "%s%s", requestURI, missingTerm);
 		
		//allocate memory for the filepath
		char *filePath = (char*)malloc(strlen(newURI)+strlen(webRoot)+1 * sizeof(char));
       		if(filePath == NULL){
               		printf("malloc failed");
               		fclose(clntFile);
               		return;
       		}

		sprintf(filePath, "%s%s", webRoot, newURI);
 
		//open the requested file
		FILE *requestedFile = fopen(filePath, "rb");
		if(requestedFile == NULL){
			displaySiteError(404, "Not Found", clntAddr, BUFFER, clntSock);
			free(newURI);
			free(filePath);
			fclose(clntFile);
			return;
		}
		
		//free allocated memory
		free(newURI);
		free(filePath);
		
		//optimal thing
		char streamBuff[4096];
		//set the header
		const char *header = "HTTP/1.0 200 OK \r\n\r\n";
		int headerLen = strlen(header);
		//track errors
		int errCounter = 0;
		if(send(clntSock, header, strlen(header), 0) != headerLen){
			printf("send() error with header");
			errCounter++;
		}

		int fileStreamLen;
       		int dataLen;
       		while((fileStreamLen = fread(streamBuff,1,sizeof(streamBuff),requestedFile)) > 0 ){
               		if((dataLen = send(clntSock, streamBuff, fileStreamLen, 0)) != fileStreamLen){
                       		printf("send() error with file");
                		errCounter++;
               		}
       		}
		
		//if there are no errors print 200 OK status
		if(errCounter == 0){
               		printf("%s \"%s\" %d %s\n", clntAddr, BUFFER, 200, "OK");
		}
		
		//close files
       		fclose(requestedFile);
       		fclose(clntFile);
}

int main(int argc, char** argv)
{
	// ignore SIGPIPE so that we don't terminate when we call
	// send() on a disconnected socket.
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR){
		die("signal() failed");
	}

	if(argc != 5){
		printf("Usage: ./http-server <server_port> <web_root> <mdb-lookup-host> <mdb-lookup-port>");
		exit(1);
	}
 	
	int servSock;
	int clntSock;
	int mdbSock;
	struct sockaddr_in clntAddr;
	struct sockaddr_in servAddr;
	struct sockaddr_in mdbAddr;
	unsigned short servPort = atoi(argv[1]);/*server port is arg[1]*/
	unsigned short mdbPort = atoi(argv[4]);/*lookup port */
	unsigned int clntLen;
	char *webRoot = argv[2];/*web root is arg[2]*/
        char *mdbHost = argv[3];/*lookup host is arg[3]*/
	char *hostIP;

	//Create the socket
	if((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		die("socket() failed");
	}

	//Construct local address structure
   	memset(&servAddr, 0, sizeof(servAddr));
   	servAddr.sin_family = AF_INET;
   	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   	servAddr.sin_port = htons(servPort);

	//Bind to the local address
   	if((bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr))) < 0){
		die("bind() failed");
	}

   	//Listen for incoming connections
   	if (listen(servSock, KEYMAX) < 0){
       		die("listen() failed");
	}

	//Create mdb socket
	struct hostent *he;
	if((he = gethostbyname(mdbHost)) == NULL){
               die("gethostbyname() failed");
       	}

	hostIP = inet_ntoa(*(struct in_addr*)(he->h_addr));

	if((mdbSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		die("socket() failed");
	}

	//Construct local address structure
   	memset(&mdbAddr, 0, sizeof(mdbAddr));
   	mdbAddr.sin_family = AF_INET;
  	mdbAddr.sin_addr.s_addr = inet_addr(hostIP);
   	mdbAddr.sin_port = htons(mdbPort);
	
	//Connect to mdbSock
	if(connect(mdbSock, (struct sockaddr *)&mdbAddr, sizeof(mdbAddr))<0){
		die("connect() failed");
	}

	//Create the mdb file for lookup
        FILE *mdbFile = fdopen(mdbSock,"rb");
        if(mdbFile == NULL){
                die("error with mdbFile");
        }
	
	for(;;)//Run forever
	{
		//Set the size of the in-out parameter
		clntLen = sizeof(clntAddr);

		//Waiting for a client to connect
		if((clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntLen)) < 0){
			printf("accept() failed");
		}	
	
		//Check the request, whether it is for an html file or mdb-lookup
		webBrowserRequest(clntSock, inet_ntoa(clntAddr.sin_addr), webRoot, mdbSock, mdbFile);
	
		//Close the clntSock
		close(clntSock);
	}
	
	//This is never reached
	return 0;
}
