#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mdb.h"
#include "mylist.h"

void search(struct List *list, char *array, int strLength);
void freeMemory(struct List *list);

int main(int argc, char** argv)
{
	//if no database is passed as an argument, exit
	if(argc <=1 )
	{
		printf("No databse used\n");
		return 1;
	}

	struct List list;
	struct MdbRec *record = NULL;
	struct Node *node = NULL;

	//pointer to the database file, use the pointer from the command line argument for the name of the file 	
	FILE *fp;
	fp = fopen(*++argv, "r");
	if(fp == NULL)
	{
		perror("Error something wrong with the file");
		exit(1);
	}

	//initialize list
	initList(&list);
	
	char pName[16];
	char pMsg[24];
	
	//read records into memory
	while(fread(pName, 16, 1, fp) && fread(pMsg, 24, 1, fp))
	{
		record = malloc(sizeof(struct MdbRec));
		if(record == NULL)
		{
			perror("Malloc assigned NULL");
			exit(1);
		}
	
		//copy the data read into the arrays for name and msg only up to the specified number	
		strncpy(record->name, pName, 16);
		strncpy(record->msg, pMsg, 24);

		//add the data into a linked list
		node = addAfter(&list, node, record);
	}		


	char c;
	char inputLine[1000];
	int i = 0;
	//keep going until user hits CTRL-D
	while(1)
	{
		printf("\nlookup: ");
		while((c = getchar()) != '\n')
		{
			//if EOF is read, free all the memory, close the database file, and exit
			if(c == EOF)
			{
				freeMemory(&list);
				fclose(fp);
				exit(0);				
			}
			//keep incrementing after inserting each individual character
			inputLine[i++] = c;
		}
		//make the last element of the array as NULL
		inputLine[i] = '\0';

		//if input is larger than 5, reduce it to five else keep it at whatever number 
		int inputFix = 0;
		if(i > 5)
		{
			inputFix = 5;
		}else
		{
			inputFix = i;
		}
		
		//search whatever
		search(&list, inputLine, inputFix);
		i = 0;//resets the inputLine array back to the first element this way you can hit eneter and all the records will appear and you can constantly search
	}	

return 0;
}

void search(struct List *list, char *array, int strLength)
{
	char *string = (char*)malloc((strLength+1));
	//copy whatever the user entered as input for the lookup into string
	strncpy(string, array, strLength);
	string[strLength] = '\0';
	struct Node *node = list->head;
	//used to print records number
	int recCounter = 1; 
	while(node != NULL)
	{
		struct MdbRec *record = node->data;
		if((strstr(record->name, string) != NULL) || (strstr(record->msg, string) != NULL))

		{
			printf(" %d: {%s} said {%s}\n", recCounter, record->name, record->msg);
		} 
		recCounter++;
		node = node->next; 
	}

	free(string);	
}

void freeMemory(struct List *list)
{
	//free the data/record pointed to by the node
	struct Node *node = list->head;
	while(node != NULL)
	{
		free(node->data);
		node = node->next;
	}

	//remove all nodes from the list
	removeAllNodes(list);
}
