#include "my.h"
#include "list.h"

void* elem_at(struct s_node *head, int n)
{
	/*
	Returns a pointer to the elem at index n or the last node.
	Parse once.
	*/

	void* element = NULL;
	struct s_node* temp;

	if (head != NULL)
	{
		temp = head;
		while (n > 0 && temp->next != NULL)
		{
			temp = temp->next;
			n--;
		}
		element = temp->elem;
	}
	return element;
}