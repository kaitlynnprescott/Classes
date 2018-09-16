#include "my_select.h"

/* move cursor */

void move_next(int pos)
{
	tputs(tgoto(gl_env.move, gl_env.elements[pos].x, gl_env.elements[pos].y), 1, my_termprint);
	
}