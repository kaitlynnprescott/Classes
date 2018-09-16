/* Kaitlynn Prescott*/
#include "my.h"
#include <stdlib.h>

char* my_strdup(char* str)
{
	/*
	Allocates new memory 
 	Copies str into that new memory 
 	returns pointer to new string
	*/
 	char* cpy = NULL;
	if(str != NULL)
	{
		cpy = malloc(my_strlen(str));
		my_strcpy(cpy, str);
	}
	return cpy;
}