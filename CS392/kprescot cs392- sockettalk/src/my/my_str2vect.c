#include "my.h"

char** my_str2vect(char* str)
{
	/*
 	 Takes a string 
 	 Allocates a new vector (array of string ended by a NULL), 
 	 Splits apart the input string x at each space character 
 	 Returns the newly allocated array of strings
 	 Any number of ' ','\t', and '\n's can separate words.
 	 I.e. "hello \t\t\n class,\nhow are you?" -> 
 	 {"hello", "class,", "how", "are","you?", NULL}
	*/
	char** vector;
	int numOfStrs;
	int i, j;
	int skip;

	numOfStrs = 1;

	for (; *(str) == '\t' || *(str) == ' ' || *(str) == '\n'; str++);
	for (i = 0, skip = 1; str[i] != '\0'; i++)
	{
		if (str[i] == '\t' || str[i] == ' ' || str[i] == '\n')
		{
			if (skip == 1)
			{
				skip = 0;
			}
		}
		else if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
		{
			if (skip == 0)
			{
				skip = 1;
				numOfStrs++;
			}
		}
	}
	vector = (char**)malloc((numOfStrs + 1)*sizeof(char*));

	for (i = 0, j = 0, numOfStrs = 0; str[i] != '\0'; numOfStrs++, i = j)
	{
		for (; str[i] != '\0' && (str[i] == '\t' || str[i] == ' ' || str[i] == '\n'); i++);

		if (str[i] == '\0')
		{
			break;
		}
		j = i + 1;

		for (; str[j] != '\0' && str[j] != ' ' && str[j] != '\t' && str[j] != '\n'; j++);

		vector[numOfStrs] = (char*)malloc((sizeof(char)*((j - i) + 1)));
		my_strncpy(vector[numOfStrs], &str[i], j-i);
	}
	vector[numOfStrs] = NULL;

	return vector;
}