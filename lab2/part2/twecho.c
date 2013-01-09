/*
 * twecho
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char **duplicateArgs(int argc, char **argv)
{
	//creat an overall array and allocate memory to it
	char **overallArray = (char **)malloc((argc+1) * sizeof(char*));//took away argc+1
	if(overallArray == NULL)
	{
		perror("malloc returned NULL");
		exit(1);
	}
	
	//create subarrays for each argument/string in the command line 
	int i,j;
	for(i = 0; i < argc; i++)
	{
		 *(overallArray + i) = (char *)malloc((strlen(argv[i])+1)*(sizeof(char)));
		if(*(overallArray + i) == NULL )
		{
			perror("malloc returned NULL");
			exit(1);
		}	
	}

	//this doesn't worry about the command ./twecho and only takes the strings after it and makes them uppercase
	for(i = 1; i < argc; i++)
	{
		char *subArray = *(overallArray + i);
		for(j = 0; j <= strlen(argv[i]); j++)
		{
			if(j < strlen(argv[i]))
			{		
				subArray[j] = toupper((argv[i])[j]);
			}
			if(j == strlen(argv[i]))//assign NULL character to indicate end of subArray
			{
				subArray[strlen(argv[i])] = 0;
			}
		}
	
	}
	overallArray[argc] = 0;//assign NULL character to indicate end of overallyArray

	return overallArray;
}

static void freeDuplicatedArgs(char **copy)
{
	//assigned copy to  dummy variable so as not to lose what copy points by just freeing copy alone
	char **p = copy;
	while(*p)
	{
		free(*p);
		p++;	
	}

	free(copy);
}

/*
 * DO NOT MODIFY main().
 */
int main(int argc, char **argv)
{
    if (argc <= 1)
        return 1;

    char **copy = duplicateArgs(argc, argv);
    char **p = copy;

    argv++;
    p++;
    while (*argv) {
        printf("%s %s\n", *argv++, *p++);
    }

    freeDuplicatedArgs(copy);

    return 0;
}
