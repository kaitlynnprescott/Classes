#include "my.h"
#include "list.h"

void empty_list(struct s_node** head)
{
	/*
	 Frees all the nodes in the list.
	 CHALLENGE: Write in two lines (allowed to use other methods in 
	 this assignment)
	*/

	 if (head != NULL && *head != NULL)
	 {
	 	while (*head != NULL)
	 	{
	 		remove_node(head);
	 	}
	 }
}