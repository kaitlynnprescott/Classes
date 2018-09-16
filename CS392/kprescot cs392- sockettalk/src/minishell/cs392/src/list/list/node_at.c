#include "my.h"
#include "list.h"

struct s_node* node_at(struct s_node* head, int n)
{
	/*
	Returns a pointer to the node at index n or the last node.
	Parse once
	*/
	struct s_node* temp; 
	temp = NULL;

	if (head != NULL)
	{
		temp = head;
		while (temp->next != NULL && n > 0)
		{
			temp = temp->next;
			n--;
		}
	}
	return temp;
}