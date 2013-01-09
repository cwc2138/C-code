#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mylist.h"

static void printString(void *p)
{
    printf("%s\n", (char *)p);
}


int main(int argc, char *argv[])
{
	
	struct List list;
	struct Node *node;
	initList(&list);
	int i;

	for(i = 1; i < argc; i++)
	{
		addFront(&list,(void*)argv[i]);
	}

	traverseList(&list, &printString);

	char c[5] = "dude";
   	node = findNode(&list, &c[0],(int (*)(const void*, const void*))&strcmp);
    	if(node != NULL && !(strcmp((char *)node->data, c)))
	{
		printf("\ndude found\n");
	}else
	{
		printf("\ndude not found\n");
	}	
	
	removeAllNodes((struct List *)&list);

return 0;
}
