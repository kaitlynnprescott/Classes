/* Kaitlynn Prescott*/
#include "my.h"


int my_atoi(char* str)
{
	/*
	Returns the int represented by the ascii string
 	Handles negatives.
 	Ignores preceding characters and trailing numbers and chars
 	Examples
 	"5" => 5
 	"-5" => -5
 	"--5" => 5
 	"a-b54sc7-d" => -54
 	"abcd" => 0
 	*/


	int res = 0;
 	int sign = 1;

 	if (str == NULL)
 	{
 		my_str("NULL. ");
 		return 0;
 	}

 	if (str != NULL)
 	{
 		while (*str == ' ')
 		{
 			str++;
 		}
 		while (*str < 48 || *str > 57)
 		{
 			if (*str == 45)
 			{
 				sign = sign * -1;
 			}
 			str++;
 		}
 		while (*str >= 48 && *str <= 57)
 		{
 			res = (res * 10) + (*str - '0');
 			str++;
 		}
 		return sign * res;
 	} 	
 	return 0;
}	