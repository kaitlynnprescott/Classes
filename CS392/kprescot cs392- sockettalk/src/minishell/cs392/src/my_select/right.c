#include "my_select.h"

/* move cursor right */

void right()
{
	no_underline_refresh(gl_env.pos);
	gl_env.pos += gl_env.win.ws_row;

	if (gl_env.pos >= gl_env.nbelems)
	{
		gl_env.pos = gl_env.nbelems - 1;
	}

	underline_refresh();
}