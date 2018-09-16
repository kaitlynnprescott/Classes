#include "my.h"
#include "list.h"

void* remove_node(struct s_node** node)
{
	/* 
	 Removes the first node from the list. Returns elem and frees the 
	 node from memory.
	 DOES NOT PARSE.
	*/

	 void* element = NULL;
	 struct s_node *temp;

	 if (node != NULL && *node != NULL)
	 {
	 	temp = *node;
	 	element = (*node)->elem;
	 	*node = temp->next;
	 	free(temp);
	 	temp = NULL;
	 }
	 return element;
}