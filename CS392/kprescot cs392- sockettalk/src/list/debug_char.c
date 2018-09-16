#include "my.h"
#include "list.h"

void debug_char(struct s_node* head)
{
	/*
 	Prints all the elems as chars separated by a space in the format
 	(NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
	*/
	if (head)
	{
		struct s_node* temp;
		temp=head;

		while(temp != NULL)
		{
			my_char('(');
			if(temp->prev != NULL)
			{
				print_char(temp->prev);
			}
        	else
        	{
        		my_str("NULL");
        	}

        	my_str( " <- ");
        	if(temp->elem != NULL)
        	{ 
        		print_char(temp);
        	}
        	else
        	{
        		my_str("NULL");
        	}
        	
            my_str( " -> ");
        	if(temp->next != NULL)
        	{
        		print_char(temp->next);
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