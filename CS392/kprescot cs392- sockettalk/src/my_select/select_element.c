#include "my_select.h"

/* selecting an element */

void select_element()
{
	gl_env.elements[gl_env.pos].mode = !gl_env.elements[gl_env.pos].mode;

	if (gl_env.elements[gl_env.pos].mode)
	{
		down();
	}
	else
	{
		underline_refresh();
	}
}