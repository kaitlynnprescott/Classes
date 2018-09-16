#include "my.h"
#include "list.h"

void print_int(struct s_node* node)
{
	/*
 	Prints the elem of node as a int
	*/
 	int* nodeTemp;
	if (node != NULL)
	{
		nodeTemp = ((int*)node->elem);
		my_int(*nodeTemp);
	}
}