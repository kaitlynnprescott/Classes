#include "my_select.h"

/* move cursor down */

void down()
{
	no_underline_refresh(gl_env.pos);

	if (++gl_env.pos > gl_env.nbelems - 1)
	{
		gl_env.pos = 0;
	}

	underline_refresh();
}