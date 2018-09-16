/*
Kaitlynn Prescott
my_revstr.c
Reverse the string, directly in the actual string, 
without creating a new string. 
Return the length of the string.
*/

#include "my.h"

int my_revstr(char* str)
{
	int l = my_strlen(str) - 1;
	int i = 0;
	char c;
	
	if(str==NULL)
	{
		return -1;
	}
	
	while(i<((l+1)/2))
	{
		c=str[i];
		str[i]=str[l-i];
		str[l-i]=c;
		i++;
	}
	
	return l + 1;
}
