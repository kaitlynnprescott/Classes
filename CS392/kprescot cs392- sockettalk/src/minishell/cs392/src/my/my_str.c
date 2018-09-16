/*
Kaitlynn Prescott
my_str.c
Prints a NULL terminated C string to the console. 
Do nothing if given NULL.
*/

#include "my.h"
void my_str(char * s)
{
	int i = 0;

	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			my_char(s[i]);
			i++;
		}
	}
}
