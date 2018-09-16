#include "my_select.h"

/* quit terminal */

void quit_term(char* input)
{
	int count;
	if (input != NULL)
	{
		if (!my_strcmp(input, "\n"))
		{
			restore_term();

			for (count = 0; count < gl_env.nbelems; count++)
			{
				if (gl_env.elements[count].mode)
				{
					my_str(gl_env.elements[count].elem);
					my_str(" ");
				}
			}
			my_char('\n');
			exit(0);
		}
		else if (!my_strcmp(input, "\E"))
		{
			restore_term();
			exit(0);
		}
	}
}