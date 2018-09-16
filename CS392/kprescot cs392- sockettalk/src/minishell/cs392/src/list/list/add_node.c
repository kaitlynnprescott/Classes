#include "my.h"
#include "list.h"

void add_node(struct s_node* node, struct s_node** head)
{
	/*
	 Inserts a node at the start of the list. DO NOT add a NULL pointer or
	 a node with a NULL elem.
	 DOES NOT PARSE
	*/
	 if ((node && head != NULL) && (node->elem != NULL))
	 {
 		node->next = *head;
 		if (node->next != NULL)
 		{
 			node->next->prev = node;
 		}
	 	*head = node;
	 }
}