/*
Kaitlynn Prescott
my_int.c
Prints an integer to the console. Do not write recursively. 
Do not use arrays. Must accept negatives. 
Can be written in <= 10 lines*
*/

#include "my.h"

void my_int(int n)
{
	unsigned int exp = 1;
	unsigned int num;
	
	if(n < 0)
	{
		my_char('-');
		num = n*-1;
	}
	else
	{
		num = n;
	}
	while(exp<=(num/10))
	{
		exp = exp*10;
	}
	while (exp > 0)
	{
		my_char('0' + (num/exp));
		num = num%exp;
		exp = exp/10;
	} 
}
