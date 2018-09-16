/* Kaitlynn Prescott*/
#include "my.h"

char* my_strncpy(char* dst, char* src, int n)
{
	/*
	Same as my_strcpy except
 	Only copies n chars or until the end of src
	*/
	int i, len;
	if (n < 0)
	{
		my_str("Negative.");
		return NULL;
	}
	if (src != NULL && dst != NULL)
	{
		len = my_strlen(src);
		if (len > n)
		{
			len = n;
		}
		for (i = 0; i < len; i++)
		{
			*(dst + i) = *(src + i);
		}
		dst[i] = '\0';
	}
	if (n == 0)
	{
		my_str("0 Copied.");
		return NULL;
	}
	if (dst != NULL)
	{
		return dst;
	}
	return NULL;
}