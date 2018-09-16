#include "my_select.h"

/* return termcap as char */

char* get_cap(char* cap)
{
	static char area[2048];
	char* result;

	if (!(result = tgetstr(cap, (char**) &area)))
	{
		if (!my_strcmp(cap, CURSOROFF) || !my_strcmp(cap, CURSORON))
		{
			if (!my_strcmp(cap, CURSOROFF))
			{
				result = VICAP;
			}
			else
			{
				result = VECAP;
			}
		}
		else
		{
			my_str("Cap ");
			my_str(cap);
			my_str(" not found! \n");
			restore_term();
			exit(1);
		}
	}
	return result;
}