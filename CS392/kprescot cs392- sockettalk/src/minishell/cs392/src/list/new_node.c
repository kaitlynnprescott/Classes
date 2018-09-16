
#include "list.h"

struct s_node* new_node(void* elem, struct s_node* next, struct s_node* previous)
{
	/*
 	Allocates and returns a new node with the given pointers. You may
 	create nodes with NULLs.
	*/
	struct s_node *new = (struct s_node*)malloc(sizeof(struct s_node));
	new->elem = elem;
	new->next = next;
	new->prev = previous;
	return new;
}