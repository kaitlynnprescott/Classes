/*
Kaitlynn Prescott
my_aplha.c
Prints all the letters A to Z, in upper case. 
This function should have no variables larger than a byte. 
Should be 3~ lines.
*/

#include "my.h"

void my_alpha()
{
	char letter;
	for(letter='A'; letter<='Z'; letter++)
	{
		my_char(letter);
	}
}
