/* Kaitlynn Prescott*/
#include "my.h"

int my_strcmp(char* a, char* b)
{
	/*
	Compares strings by ascii value
	 If a and b are identical, return 0. 
	 if a < b, return negative number 
	 if a > b, return positive number
	 Two NULL are equal.
	 NULL is always less than a normal string
 	*/

	
	if(a == '\0' && b == '\0')
	{
		return 0;
	}
	else if(a == '\0')
	{
		return -1;
	}
	else if(b == '\0')
	{
		return 1;
	}
	else
	{
		while ((*a == *b) && ((*a != '\0') && (*b != '\0')))
		{
			a++;
			b++;
		}
		if ((*a == '\0') && (*b == '\0'))
		{
			return 0;
		}
		return (int)(*a - *b);
	}


/*
	int i;
	int min;
	if(my_strlen(a) < my_strlen(b))
	{
		min = my_strlen(a);
	}
	else
	{
		min = my_strlen(b);
	}
	for(i=0; i<min; i++)
	{
		if(a[i]>b[i])
		{
			return 1;
		}
		if(a[i]<b[i])
		{
			return -1;
		}
	}
	return 0;*/
}