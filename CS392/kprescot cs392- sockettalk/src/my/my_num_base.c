/*
Kaitlynn Prescott
my_num_base.c
Prints a number using the length of the string as the base 
and the contents as the alphabet. For example, 
if you called my_num_base(9, "RTFM"), 
then R = 0, T = 1, F = 2, M = 3. 9 in base 4 is 21 and 
so the result is printed out as "FT".
BE PARANOID.
If char* is NULL or empty, print an error message and return.
If given unary, repeat alphabet letter the specified number of times.
For negatives print a '-' and then the number.
*/

#include "my.h"

void my_num_base(int num, char* str)
{
	int base = 0;
	int count = 0;
	int storage[100];
	int i;

	if (str == NULL)
	{
		my_str("Error: NULL base");
		return;
	}
	if (str[0] == '\0')
	{
		my_str("Error: empty set");
		return;
	}
	if (num == 0)
	{
		my_char(str[0]);
		return;
	}
	if (num < 0)
	{
		my_char('-');
		num *= -1;
	}
	for (; str[base] != 0; base++);
	if (base == 1)
	{
		for (i = 0; i < num; i++)
		{
			my_char(str[0]);
		}
		my_char('\0');
		return;
	}
	while (num > 0)
	{
		storage[count] = (num % base);
		num = num/base;
		count++;
	}
	count--;

	for (i = count; i >= 0; i--)
	{
		my_char(str[storage[i]]);
	}
}
