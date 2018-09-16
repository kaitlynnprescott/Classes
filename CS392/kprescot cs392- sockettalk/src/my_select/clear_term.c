#include "my_select.h"

/* clear terminal */
void clear_term()
{
	tputs(gl_env.clear, 1, my_termprint);
}