#include "my_select.h"

/* turn underline on */

void underline_on()
{
	tputs(gl_env.underlineon, 1, my_termprint);
}