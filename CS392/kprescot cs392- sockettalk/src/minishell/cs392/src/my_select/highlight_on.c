#include "my_select.h"

/* turn higlight on */

void highlight_on()
{
	tputs(gl_env.highlighton, 1, my_termprint);
}