#include "my_select.h"

/* move cursor left */

void left()
{
	no_underline_refresh(gl_env.pos);
	gl_env.pos -= gl_env.win.ws_row;

	if (gl_env.pos < 0)
	{
		gl_env.pos = 0;
	}

	underline_refresh();
}