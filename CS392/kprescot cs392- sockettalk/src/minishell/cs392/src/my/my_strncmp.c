/* Kaitlynn Prescott*/
#include "my.h"

int my_strncmp(char* a, char* b, int n)
{
	/*
	Same as my_strcmp except
 	Only compares n chars or until the end of a string
	*/

 	int lenA = my_strlen(a);
 	int lenB = my_strlen(b);
 	int i, len;
 	
 	if (n < 0)
 	{
 		n = 0;
 	}
	if(a == NULL && b == NULL)
	{
		return 0;
	}
	else if(a == NULL && b != NULL)
	{
		return -1;
	}
	else if(b == NULL && a != NULL)
	{
		return 1;
	}
	else 
	{
		if (lenA < lenB)
		{
			len = lenA;
		}
		else
		{
			len = lenB;
		}
		
		if (len > n)
		{
			len = n;
		}

		for (i = 0; i < len; i++)
		{
			if (a[i] < b[i])
			{
				return -1;
			}
			if (a[i] > b[i])
			{
				return 1;
			}
		}
		if (n == 0)
		{
			return 0;
		}
		if (lenA < lenB)
		{
			return -1;
		}
		else if (lenB < lenA)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}