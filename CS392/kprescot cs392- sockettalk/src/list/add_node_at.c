
#include "list.h"

void add_node_at(struct s_node* node, struct s_node** head, int n)
{
	/*
	 Adds a node at index n of a list or at the end of the list if n is 
	 too large.
	 Parse once
	*/
	struct s_node* temp;
	if (head != NULL && node != NULL)
	{
		if (n == 0 || *head == NULL)
		{
			add_node(node, head);
		}
		else if (n > count_s_nodes(*head) || n == count_s_nodes(*head))
		{
			append(node, head);
		}
		else
		{
			temp = *head;
			n--;
			for (; n > 0 && temp->next != NULL; n--)
			{
				my_str("\n");
				temp = temp->next;
			}
			temp = temp->next;
			temp->next = node;
		}
	}
}