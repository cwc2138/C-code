
/*
 * mdb-lookup-server-nc-2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

static void die(const char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char **argv)
{
	//store the port number as a string		
	char portNum[6];
	char c;
	int num;
	//keep going until user hits CTRL-C
	while(1)
	{
		num = 0;
		//loop until user enters a valid port number
		while(num == 0 || portNum[0] == '\n')
		{
			//child id that gets terminated
			pid_t cid; 
			//check for dead children
			while((cid = waitpid((pid_t) -1, NULL, WNOHANG)) > 0)
			{
				printf("[child id=%d] mdb-lookup-server terminated\n", cid);
			}



			printf("port number: ");
			num = 0;
			

			//if user hits enter loop again to get port number
			while((c = getchar()) != '\n')
			{
				portNum[num++] = c;
			}
			portNum[num] = '\0';

		
			pid_t pid = fork();
    			if (pid < 0) {
				die("fork failed");
    			} else if (pid == 0) {
				// child process
				execl("./mdb-lookup-server-nc.sh", "mdb-lookup-server-nc.sh", portNum, (char *)0);
				die("execl failed");
    			} else {
				printf("[pid=%d] mdb-lookup-server started on port number %s\n", pid, portNum);
			}
		}			
	}
    return 0;
}

