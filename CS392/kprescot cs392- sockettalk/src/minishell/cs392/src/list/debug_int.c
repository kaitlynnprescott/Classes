#include "my.h"
#include "list.h"

void debug_int(struct s_node* head)
{
	/*
 	Prints all the elems as ints separated by a space in the format
 	(NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
	*/
	if (head)
	{
		struct s_node* temp;
		temp = head;
		while (temp != NULL)
		{
			my_char('(');
			if (temp->prev != NULL)
			{
				print_int(temp->prev);
			}
			else
			{
				my_str("NULL");
			}
			my_str(" <- ");
			if (temp->elem != NULL)
			{
				print_int(temp);
			}
			else
			{
				my_str("NULL");
			}
			my_str(" -> ");
			if (temp->next != NULL)
			{
				print_int(temp->next);
			}
			else
			{
				my_str("NULL");
			}
			my_char(')');
			my_str(", ");
			temp = temp->next;
		}
	}
}