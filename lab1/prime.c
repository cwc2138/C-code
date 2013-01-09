#include "prime.h" 

//tests for prime number
int IsPrime(int n)
{
	int i;

	for(i = 2; i <= (n/2); i++)
	{
		if((n % i) == 0)
		{
			return 0;
		}
	}	 
	
	return 1;
}
