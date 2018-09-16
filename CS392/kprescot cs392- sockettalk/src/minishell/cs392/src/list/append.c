#include "my.h"
#include "list.h"

void append(struct s_node* node, struct s_node** head)
{
	/*
	 Adds a node to the end of a list. DO NOT add a NULL pointer or
	 a node with a NULL elem.
	 Parse once
	*/
	struct s_node* temp;
	struct s_node* previous;

	if (head != NULL && node != NULL && *head !=NULL)
	{
		previous = *head;
		temp = *head;
		if (count_s_nodes(*head) ==0)
		{
			add_node(node, head);
		}
		while(temp !=NULL)
		{
			previous = temp;
			temp = temp->next;
		}

		if(previous != NULL)
		{
			previous->next = node;
		}
		else
		{
			(*head)->next = node;
		}
	}

	/*struct s_node* temp = *head;
	if (*head == NULL)
	{
		*head = node;
	}
	while ((temp->next) != NULL)
	{
		temp = (temp->next);
	}
	temp->next = node;
	(temp->next)->prev = temp;
	(temp->next)->next = NULL;*/
}