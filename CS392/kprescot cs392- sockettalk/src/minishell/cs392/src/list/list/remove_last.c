#include "my.h"
#include "list.h"

void* remove_last(struct s_node** head)
{
	/*
	 Removes the last node from the list.
	 Parse Once.
	*/
	 struct s_node* temp;
	 void* element = NULL;

	 if (head == NULL)
	 {
	 	return element = remove_node(head);
	 }
	 if (count_s_nodes(*head) == 1)
	 {
	 	element = remove_node(head);
	 }
	 if (head != NULL && *head != NULL)
	 {
	 	temp = *head;
	 	while (temp->next->next != NULL)
	 	{
	 		temp = temp->next;
	 	}
	 	element = temp->next->elem;
	 	temp->next = NULL;
	 }
	 return element;
}