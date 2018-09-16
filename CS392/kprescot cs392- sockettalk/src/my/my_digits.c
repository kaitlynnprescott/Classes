/*
Kaitlynn Prescott
my_digits.c
Prints all the numbers 0 to 9. 
This function should have no variables larger than a byte.
*/

#include "my.h"

void my_digits()
{
	char num;
	for(num='0'; num<='9'; num++)
	{
		my_char(num);
	}
}
