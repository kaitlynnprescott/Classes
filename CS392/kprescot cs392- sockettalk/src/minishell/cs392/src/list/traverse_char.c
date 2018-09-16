#include "my.h"
#include "list.h"

void traverse_char(struct s_node* head)
{
	/*
 	Prints all the elems as chars separated by a space
	*/

	struct s_node* temp = head;
	while(temp != NULL)
	{
		if (temp->elem == NULL)
		{
			my_str("NULL");
		}
		else
		{
			print_char(temp);
		}
		my_str(" ");
		temp = temp->next;
	}
	my_char('\n');
}