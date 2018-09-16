#include "my_select.h"

/* turn off underline */

void underline_off()
{
	tputs(gl_env.underlineoff, 1, my_termprint);
}