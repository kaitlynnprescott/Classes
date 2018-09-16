/* Kaitlynn Prescott*/
#include "my.h"
#include <stdlib.h>

char* my_strconcat(char *dst, char *src)
{
	/*
	Allocates new memory 
 	Copies concatenated strings in that new memory 
 	Returns pointer to it
 	If both NULL return NULL
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
 	if (src != NULL)
 	{
 		lenS = my_strlen(src);
 	}
 	ptr = malloc(lenD + lenS + 1);
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