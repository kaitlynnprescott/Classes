/* Kaitlynn Prescott*/
#include "my.h"

char* my_strcpy(char* dst, char* src)
{
	/* 
	Copies the characters from src into dst overwriting what's already in there.
 	Always copies a '\0'
 	Assumes dst has enough memory allocated for the new string if it is longer.
 	Does not allocate memory
	*/
	int i;
	int len;
	
	if(src != NULL && dst != NULL)
	{
		len = my_strlen(src);
		for (i = 0; i < len; i++)
		{
			*(dst + i) = *(src + i);
		}
		*(dst + i) = '\0';
	}
	if (dst != NULL)
	{
		return dst;
	}
	return NULL;
}