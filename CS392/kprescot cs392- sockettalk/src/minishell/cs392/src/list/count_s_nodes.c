
#include "list.h"

int count_s_nodes(struct s_node *head)
{
	/*
	 Returns the value the length of the list
	 Parse Once.
	*/
	 int count = 0;
	 if (head != NULL)
	 {
	 	struct s_node *temp;
	 	temp = head;
	 	while(temp != NULL)
	 	{
	 		temp = temp->next;
	 		count++;
	 	}
	 }
	 return count;
}