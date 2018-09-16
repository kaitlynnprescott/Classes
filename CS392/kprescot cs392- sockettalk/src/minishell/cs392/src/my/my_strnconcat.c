/* Kaitlynn Prescott*/
#include "my.h"
#include <stdlib.h>

char* my_strnconcat(char *dst, char *src, int n)
{
	/*
	Same as my_strconcat except
	Copies all of a and then n chars or length of b
 	*/
	int count;
 	char* ptr;
 	int lenD = 0;
 	int lenS = 0;

 	if (dst == NULL && src == NULL)
 	{
 		return NULL;
 	}
 	if (dst != NULL)
 	{
 		lenD = my_strlen(dst);
 	}
 	if(src != NULL)
 	{
 		lenS = my_strlen(src);
 	}

 	ptr = (char*) malloc(lenD + lenS +1);
	 	
	for (count = 0; count < lenD; count++)
	{
		*(ptr + count) = *(dst + count);
	}
	for (; count < lenD + lenS; count++)
	{
		*(ptr + count) = *(src + count - lenD);
	}

	*(ptr + count) = '\0';
	return ptr;

}