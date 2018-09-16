#include "my_select.h"

/* resho with underline */

void underline_refresh()
{
	move_next(gl_env.pos);
	underline_on();

	if (gl_env.elements[gl_env.pos].mode)
	{
		highlight_on();
	}
	my_str(gl_env.elements[gl_env.pos].elem);
	highlight_off();
	highlight_on();
}