#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void die(char *message)
{
	printf("%s\n", message);
	exit(1);
}

int main(int argc, char** argv)
{
	if(argc != 4){
		printf("Usage: ./http-client <host> <portNum> <file_patch>");
		exit(1);
	}
	//set the strings for the request	
	char *get = "GET ";
	char *http_v = " HTTP/1.0";
	char *host = "Host: ";
	
	char *hostName = argv[1];/*host name is arg[1]*/
	char *port = argv[2];/*port number is arg[2]*/
	char *filePath = argv[3];/*file path name is arg[3]*/ 
	int portNum = atoi(port);/*convert port from string into an int*/
	char *html_file = strrchr(filePath, '/');/*find the last slash so we can give our file the right file name.html*/	
	
	struct hostent *he;
	int sock;
	char *hostIP;
	struct sockaddr_in servAddr;
		
	//get server ip from server name
	if ((he = gethostbyname(hostName)) == NULL){
		die("gethostbyname failed");
	}

	hostIP = inet_ntoa(*(struct in_addr *)(he->h_addr));
		
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		die("socket failed");
	}
	/*Create the server address structure */
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(hostIP);	
	servAddr.sin_port = htons(portNum);

	if(connect(sock,(struct sockaddr*)&servAddr, sizeof(servAddr)) < 0){
		die("connect failed");
	}
	//inital request, concatenate strings together to form the request
	char *initReq = (char*)malloc((strlen(get)+strlen(filePath)+strlen(http_v)+4)*sizeof(char));
	strncpy(initReq, get, strlen(get)+1);
	strncat(initReq, filePath, strlen(filePath)+1);
	strncat(initReq, http_v, strlen(http_v)+1);
	strncat(initReq, "\n", sizeof(char)+1);
	//same as above, but concatenate strings together fot the host port
	char *hp = (char*)malloc((strlen(host)+strlen(hostName)+strlen(port)+5)*sizeof(char));
	strncpy(hp, host, strlen(host)+1);
	strncat(hp, hostName, strlen(hostName)+1);
	strncat(hp, ":", sizeof(char)+1);
	strncat(hp, port, strlen(port)+1);
	strncat(hp, "\n", sizeof(char)+1);

	int initReqLen = strlen(initReq);//initial request's length
	if(send(sock, initReq, initReqLen,0) != initReqLen){
		die("send is sending different # of bytes");
	}

	int hpLen = strlen(hp); //host port's length
	if(send(sock, hp, hpLen, 0) != hpLen){
		die("send is sending different # of bytes");
	}	
	//send a blank line
	send(sock, "\r\n", 2, 0);

	FILE *socketFile = fdopen(sock, "rb");
	if(socketFile == NULL){
		die("error with socketFile");
	}

	char BUFFER[4096];
	fgets(BUFFER, sizeof(BUFFER), socketFile);
	
	//detects if there is the 200 response
	if(!strstr(BUFFER, "200")){
		printf("%s", BUFFER);
		die("");
	}

	while(fgets(BUFFER, sizeof(BUFFER), socketFile) != NULL){
		if(BUFFER[0] == '\r' && BUFFER[1] == '\n')
			break;
	}

	//write to the html file below
	FILE *outputFile = fopen(++html_file, "w+");
	if(outputFile == NULL){
		die("error with output file");
	}

	size_t num;
	while((num = fread(BUFFER, 1, sizeof(BUFFER), socketFile)) > 0)	{
		if(fwrite(BUFFER, 1, num, outputFile) != num)
			die("error fwrite");
	}

	if(ferror(outputFile)){
		die("fread failed");
	}

	//close and free everything
	free(initReq);
	free(hp);
	fclose(socketFile);
	fclose(outputFile);	

return 0;
}
