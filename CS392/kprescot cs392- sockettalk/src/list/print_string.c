#include "my.h"
#include "list.h"

void print_string(struct s_node* node)
{
	/*
 	Prints the elem of node as a string
	*/

	if (node != NULL && node)
	{
		my_str((char*)node->elem);
	}
}