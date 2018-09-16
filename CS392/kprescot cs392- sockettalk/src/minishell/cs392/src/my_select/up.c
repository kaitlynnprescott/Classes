#include "my_select.h"

/* move cursor up */

void up()
{
	no_underline_refresh(gl_env.pos);

	if (--gl_env.pos < 0)
	{
		gl_env.pos = gl_env.nbelems = 1;
	}

	underline_refresh();
}