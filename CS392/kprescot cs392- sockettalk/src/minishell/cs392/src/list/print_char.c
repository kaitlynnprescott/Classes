#include "my.h"
#include "list.h"

void print_char(struct s_node* node)
{
	/*
 	Prints the elem of node as a char
	*/

 	char* nodeTemp;
	if (node != NULL && node)
	{
		nodeTemp = (node->elem);
		my_char(*nodeTemp);
	}
}