/*
Kaitlynn Prescott
my_strindex.c
Returns the first index at which the character is 
found in the string or -1 if there is none.
*/

#include "my.h"

int my_strindex(char* arr, char c)
{
	int i = 0;
	int len = my_strlen(arr) - 1;
	if (arr == NULL)
	{
		return -1;
	}
	while (i <= len)
	{
		if ((arr[i]) == c)
		{
			return i;
		}
		i++;
	}
	return -1;
}
