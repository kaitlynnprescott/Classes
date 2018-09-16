#include "my.h"
#include "list.h"

void print_char(struct s_node* node)
{
	/*
 	Prints the elem of node as a char
	*/

	if (node != NULL && node)
	{
		char* nodeTemp = (node->elem);
		my_char(*nodeTemp);
	}
}