/* Kaitlynn Prescott*/
#include "my.h"

char* my_strrfind(char* arr, char c)
{
	/* 
	Returns a pointer to the last char in the string which matches.
	Return NULL if the letter is not found.
	*/
	char *ptr = NULL;
	if(arr != NULL)
	{
		for(; *arr != '\0'; arr++)
		{
			if(*arr == c)
			{
				ptr = arr;
			}
		}
	}
    return ptr;
}
