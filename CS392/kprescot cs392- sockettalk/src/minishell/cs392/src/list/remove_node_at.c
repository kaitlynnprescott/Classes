
#include "list.h"

void* remove_node_at(struct s_node** head, int n)
{
	/* 
 	 Removes the given node from the list. Returns elem and frees the 
	 node from memory.
	 DOES NOT PARSE.
	*/
	 struct s_node* previous;
	 struct s_node* temp;
	 void* element = NULL;

	 if (head != NULL)
	 {
	 	if (n == 0)
	 	{
	 		element = remove_node(head);
	 	}
	 	else if (n > count_s_nodes(*head) || n == count_s_nodes(*head))
	 	{
	 		element = remove_last(head);
	 	}
	 	else
	 	{
	 		temp = (*head)->next;
	 		while (n > 1 && temp != NULL)
	 		{
	 			previous = temp;
	 			temp = temp->next;
	 			n--;
	 		}
	 		element = previous->next->elem;
	 		previous->next = temp->next;
	 	}
	 }
	 return element;
}