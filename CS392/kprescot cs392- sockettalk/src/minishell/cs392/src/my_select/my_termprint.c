#include "my_select.h"

/* write character to terminal */

int my_termprint(int c)
{
	return write(1, &c, 1);
}
