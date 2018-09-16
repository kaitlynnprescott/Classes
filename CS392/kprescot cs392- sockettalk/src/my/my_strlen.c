/*
Kaitlynn Prescott
my_strlen.c
Calculates the length of a string (not including the null terminator). 
Length of NULL is -1.
*/

#include "my.h"

int my_strlen(char* arr)
{
	if (arr == 0)
	{
		return -1;
	}
	else
	{
		int index = 0;
		while (arr[0] != '\0')
		{
			index++;
			arr++;
		}
		return index;
	}
}
