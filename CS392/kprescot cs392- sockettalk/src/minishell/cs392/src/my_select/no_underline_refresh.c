#include "my_select.h"

/* reshow without underline */

void no_underline_refresh(int pos)
{
	move_next(pos);

	if (gl_env.elements[pos].mode)
	{
		highlight_on();
	}
	my_str(gl_env.elements[pos].elem);
	highlight_off();
}