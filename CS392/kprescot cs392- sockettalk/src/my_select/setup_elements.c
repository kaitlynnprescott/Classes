#include "my_select.h"

/* set global elements */

void setup_elements(int num, char** elements)
{
	int count;
	gl_env.nbelems = num;
	gl_env.elements = malloc(num * sizeof(t_elem));

	for (count = 0; count < num; count++)
	{
		gl_env.elements[count].elem = elements[count];
		gl_env.elements[count].size = my_strlen(elements[count]);
		gl_env.elements[count].mode = 0;
	}
}