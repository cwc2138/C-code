#include "gcd.h"

//returns gcd of numbers entered
int gcd(int n1, int n2)
{
	int remainder;
	while(remainder != 0)
	{
		remainder = n1 % n2;
		n1 = n2;
		n2 = remainder;
	}

	return n1;
}
