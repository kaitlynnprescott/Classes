/* Kaitlynn Prescott*/
#include "my.h"

char* my_strcat(char* dst, char* src)
{
	/*
	Copies src onto the end of dst and returns dst
 	Does not allocate memory
 	Assumes there is enough memory allocated in dst to hold both strings
 	Overwrites src's original '\0' and places a new '\0' onto the end
 	*/
 	
	int i;
	int lenD = my_strlen(dst);
	int lenS = my_strlen(src);
	if (dst != NULL && src != NULL)
	{
		for (i = lenD; i < lenS + lenD; i++)
		{
			dst[i] = *(src++);
		}
		dst[i] = '\0';
	}
	if (dst == NULL)
	{
		my_str("Null Destination.");
		return NULL;
	}
	if (src == NULL)
	{
		return dst;
	}

	if (dst != NULL)
	{
		return dst;
	}
	return NULL;

}