#include "my_select.h"

/* turn off highlight */

void highlight_off()
{
	tputs(gl_env.highlightoff, 1, my_termprint);
}