/*
Kaitlynn Prescott
my_strrindex.c
Returns the last index at which the character is found in 
the string or -1 if there is none.
*/

#include "my.h"

int my_strrindex(char* arr, char b)
{
	int l = my_strlen(arr) - 1;
	if (arr == NULL)
	{
		return -1;
	}
	while (l >= 0)
	{
		if ((arr[l]) == b)
		{
			return l;
		}
		l--;
	}
	return -1;
}
