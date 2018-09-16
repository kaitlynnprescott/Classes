#include "my_select.h"

/* restore terminal to original state */

void restore_term()
{
	tputs(gl_env.cursoron, 0, my_termprint);
	clear_term();
	ioctl(0, TCSETA, &(gl_env.line_backup));
	dup2(gl_env.stdio_backup, 1);
}