#include "my_select.h"

/* print out elements */

void show_elements()
{
	int i, x, y, max;
	ioctl(0, TIOCGWINSZ, &(gl_env.win));
	gl_env.flag = 0;
	clear_term();

	for (i = 0, x = 0, y = 0, max = 0; i < gl_env.nbelems; i++, y++)
	{
		if (y >= gl_env.win.ws_row)
		{
			y = 0;
			x += max + 5;
			max = 0;
		}
		if (max < gl_env.elements[i].size)
		{
			max = gl_env.elements[i].size;
		}
		if (x + max >= gl_env.win.ws_col)
		{
			clear_term();
			my_str("Please enlarge the window.");
			gl_env.flag = 1;
			break;
		}
		gl_env.elements[i].x = x;
		gl_env.elements[i].y = y;
		no_underline_refresh(i);

		if (!gl_env.flag)
		{
			underline_refresh();
		}
	}
}