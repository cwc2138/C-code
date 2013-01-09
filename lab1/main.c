#include <stdio.h>
#include "prime.h" 
#include "gcd.h"

//function declaration for avg
void avg(int, int);

int main()
{
	int x, y;//two numbers to be entered by user
	
	printf("Enter an integer:\n");
	scanf("%d", &x);

	printf("Enter a second integer:\n");
	scanf("%d", &y);

	avg(x,y);	

	//tests if numbers enetered are prime or not 
	if(IsPrime(x))
	{
		printf("The first number is prime.\n");
	}else
	{
		printf("The first number is not prime.\n");
	}
	
	if(IsPrime(y))
	{
		printf("The second number is prime.\n");
	}else
	{
		printf("The second number is not prime.\n");
	}	

	//tests whether the numbers entered are co-prime or not
	if(gcd(x,y) == 1)
	{
		printf("The numbers entered are coprime.\n");
	}else
	{
		printf("The numbers entered are not coprime.\n");
	}	

	return 0;
}

//function definition for average
void avg(int n1, int n2)
{
	float avg = (n1+n2)/2.0f;
	printf("The average of your two numbers is: %f\n", avg);
}


