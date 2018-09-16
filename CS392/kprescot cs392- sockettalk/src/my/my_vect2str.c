#include "my.h"

char *my_vect2str(char **x)
{ 
	/* 
	Takes a vector (array of string ended by a NULL)
	Allocates a new string and copies each string from the array 
	into new string separated by a single space, until NULL pointer 
	to string is found
	Returns new string
	{"hello","world",NULL} -> "hello world";
	*/

	if (x != NULL && *x != NULL)
	{
		char* str = NULL;
		int i, j;
		int size = 0;
		for (i = 0; x[i] != NULL; i++)
		{
			size += my_strlen(x[i]);
		}
		str = (char* ) malloc(size*sizeof(char));
		size = 0;
		for (i = 0; x[i] != NULL; i++)
		{
			for (j = 0; x[i][j] != '\0'; j++, size++)
			{
				str[size] = x[i][j];
			}
			str[size++] = ' ';
		}
		str[--size] = '\0';
		return str;
	}
	return NULL;
}