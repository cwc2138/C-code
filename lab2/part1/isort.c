#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void copyArray(int *orig, int size);
void q_sort(int *unsorted, int *begin, int *end);
int compAsc(const void *p_begin, const void *p_end);
int compDes(const void *p_begin, const void *p_end);
void sort_integer_array(int *begin, int *end, int ascending);

int main()
{
	srandom(time(NULL));
	int size = 0;

	printf("What size array would you like: ");
	scanf("%d", &size);

	//assign memory to array
	int* randArray = (int*)malloc(size * sizeof(int));
	if(randArray == NULL)
	{
		perror("malloc failed");
		exit(1);
	}

	//assigns a random integer to each array index
	int i;
	for(i = 0; i < size; i++ )
	{
		randArray[i] = random(); 
	}

	//print original array
	printf("Printing original array:\n");
	for(i = 0; i < size; i++ )
	{
		printf("randArray[%d] = %d\n", i , randArray[i]); 
	}

	copyArray(randArray, size);

	free(randArray);
	return 0;
}

void copyArray(int *orig, int size)
{
	//create space for first copy
	int *duplicArray1 = (int*)malloc(size * sizeof(int));
	if(duplicArray1 == NULL)
	{
		perror("malloc failed");
		exit(1);
	}

	//create space for second copy
	int *duplicArray2 = (int*)malloc(size * sizeof(int));
	if(duplicArray2 == NULL)
	{
		perror("malloc failed");
		exit(1);
	}

	//first copy of original array
	int i;
	for(i = 0; i < size; i++)
	{
		duplicArray1[i] = orig[i];
		//printf("duplicArray1[%d] = %d\n", i, duplicArray1[i]);
	}

	//second copy of original array
	for(i = 0; i < size; i++)
	{
		duplicArray2[i] = orig[i];
		//printf("duplicArray1[%d] = %d\n", i, duplicArray1[i]);
	}

	sort_integer_array(&duplicArray1[0], &duplicArray1[size+1], 1);
	sort_integer_array(&duplicArray2[0], &duplicArray2[size+1], 0);

	//array after ascending order
	printf("\nArray in ascending order:\n");
	int j;
	for(j = 0; j < size; j++)
	{
		printf("duplicArray1[%d] = %d\n", j, duplicArray1[j]);
	}

	//array after descending order
	printf("\nArray in descending order:\n");
	for(j = 0; j < size; j++)
	{
		printf("duplicArray2[%d] = %d\n", j, duplicArray2[j]);
	}

	free(duplicArray1);
	free(duplicArray2);
}

int compAsc(const void *p_begin, const void *p_end)
{
	const int *p_b = (const int *)p_begin;
	const int *p_e = (const int *)p_end;
	return *p_b - *p_e;
}

int compDes(const void *p_begin, const void *p_end)
{
	const int *p_b = (const int *)p_begin;
	const int *p_e = (const int *)p_end;
	return *p_e - *p_b;
}

void sort_integer_array(int *begin, int *end, int ascending)
{
	if(ascending == 1)
	{
		qsort(begin, end-begin-1, sizeof(int), compAsc);
	}else if(ascending == 0)
	{
		qsort(begin, end-begin-1, sizeof(int), compDes);
	}
}
