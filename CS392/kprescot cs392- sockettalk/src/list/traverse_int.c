#include "my.h"
#include "list.h"


void traverse_int(struct s_node* head)
{
	/*
	Prints all the elems as ints separated by a space
	*/
	struct s_node* temp;
	temp = head;

	while (temp != NULL)
	{
		if (temp->elem == NULL)
		{
			my_str("NULL");
		}
		else
		{
			print_int(temp);
		}
		my_str(" ");
		temp = temp->next;

	}
	my_char('\n');
}