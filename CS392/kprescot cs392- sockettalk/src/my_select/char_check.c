#include "my_select.h"
/* process input */
void char_check(char* input)
{
	int count;

	if (input != NULL)
	{
		if (!my_strcmp(input, KU))
		{
			up();
		}
		else if (!my_strcmp(input, KD))
		{
			down();
		}
		else if (!my_strcmp(input, KL))
		{
			left();
		}
		else if (!my_strcmp(input, KR))
		{
			right();
		}
		else if (!my_strcmp(input, " "))
		{
			select_element();
		}
		else 
		{
			quit_term(input);
		}
	}
}