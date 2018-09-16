#include "my.h"
#include "list.h"

void add_elem(void* elem, struct s_node** head)
{
	/* 
	 Creates a new node with elem and adds it to head. DO NOT add a NULL 
	 elem.
	 DOES NOT PARSE
	*/
	 struct s_node* new_elem;
	 if (elem != NULL && head != NULL)
	 {
	 	new_elem = new_node(elem, *head, NULL);
	 	add_node(new_elem, head);
	 }
}