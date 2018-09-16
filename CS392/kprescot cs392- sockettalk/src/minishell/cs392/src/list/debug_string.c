#include "my.h"
#include "list.h"

void debug_string(struct s_node* head)
{
	/*
 	Prints all the elems as strings separated by a space in the format
 	(NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
	*/
	if (head != NULL)
	{
		struct s_node* temp;
		temp = head;

		while (temp != NULL)
		{
			my_char('(');
			if (temp->prev != NULL)
			{
				print_string(temp->prev);
			}
			else
			{
				my_str("NULL");
			}

			my_str(" <- ");
			if (temp->elem != NULL)
			{
				print_string(temp);
			}
			else
			{
				my_str("NULL");
			}

			my_str(" -> ");
			if (temp->next != NULL)
			{
				print_string(temp->next);
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