#include "list.h"
#include <unistd.h>
#include <stdio.h>

/* 
	regarding the traverse and debug methods. It's up to them which one
	they used for testing, though obviously debug_ is better to check for back
	pointers. If they only used traverse_ when dealing with main data, take
   -5 overall. They don't really need to test print_ methods as long as they 
	call the debug_ methods.
	Each debug_ and traverse_ method needs to be called at least once with
	and empty list and with a non empty one 
*/

void my_panic(char* str, int i) {
	my_str(str);
	exit(i);
}

int main() {


	my_str("Initializing stuff\n-------------------------------------------\n");
	
	int n = 5; 
	int arr[10] = {4, 65, 32, 1, 68, 23, 83, 12, 6, 82};
	unsigned int i;

	char *str = "Hello!";                     
	char *str2 = "World!";   

	struct s_node *head = NULL;         
	struct s_node *tmp = NULL;

	void *ret = NULL;


	my_str("\nTesting new_node()\n-----------------------------------------\n");

	my_str("Adding a new node with ");
	my_str(str); 
	my_str(" in tmp.\n");
	tmp = new_node(str, NULL, NULL);

	my_str("\nPrinting string (N<-Hello!->N).\n");
	print_string(tmp);

	my_str("\nPrinting char (N<-H->N).\n");
	print_char(tmp);

	my_str("\nFreeing tmp.\n");
	free(tmp);                             

	my_str("new_node with all NULLs.\n\n");
	tmp = new_node(NULL, NULL, NULL);      
	
	if (tmp != NULL && tmp->elem == NULL) {
   	my_str("Node created with NULLs Galore\n\n");
  	}
  	else {
		my_str("Didn't make node with NULLs\n\n");
		exit(1);
  	}


   my_str("\nTesting add_node()\n-----------------------------------------\n\n");
   
   my_str("The list is empty.\n");
   debug_int(head);

   my_str("\nAdding a node with NULL.\n");
   add_node(NULL, &head);

   my_str("\nThe list is empty.\n");
   debug_int(head);

   my_str("\nAdding a node with tmp.\n");
   add_node(tmp, &head);
   print_info(&head);

   my_str("\nThe list is empty.\n");
   debug_int(head);

   my_str("\nThe list is empty.\n");
   tmp->elem = &n;
   add_node(tmp, NULL);
   debug_int(head);

   for (i = 0; i < 3; i++) {
   	my_str("\nAdding node number ");
   	my_int(i); 
   	my_char('\n');
      add_node(new_node(&arr[i], NULL, NULL), &head);
      my_str("\t|\t");
      my_int(i);
      my_char('\n');
      debug_int(head);                                
   }

   my_str("\nThis should print the list.\n");
   traverse_int(head); 

   /* 
   	technically adding 2 should be enough should test for adding to empty
    	and adding to list with only one item. Only 2 cases where things could
    	go wrong. They don't need to print after each insertion, one at the end
    	would suffice.
   */

   my_str("\nEmptying a list, passing a NULL.\n");
   empty_list(NULL); 

   my_str("\nEmptying a list, passing the non-NULL head.\n");
   empty_list(&head);
   
   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head);
   
   my_str("\ntraverse_int - The list is empty,\n");
   traverse_int(head); 

   my_str("\ndebug_string - The List is empty.\n");
   debug_string(head);

   traverse_string(head);
   debug_char(head); /* should print The list is empty */
   traverse_char(head);


   my_str("\nTesting add_elem()\n-----------------------------------------\n");

   my_str("\nAdding an element with NULL.\n");
   add_elem(NULL, &head);

   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head); 

   my_str("\nAdding a non-NULL element to a NULL head.\n");
   add_elem(&n, NULL);

   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head); 

   for (i = 0; i < 3; i++) {
   	my_str("\nAdding an elem with ");
   	my_int(i); 
   	my_char('\n');
      add_elem(&arr[i], &head); 
      debug_int(head);
      my_str("\nprints the list until this point.\n");
   }

	/* 
		technically adding 2 should be enough should test for adding to empty
   	and adding to list with only one item. Only 2 cases where things could
   	go wrong. They don't need to print after each insertion, one at the end
   	would suffice.
 	*/
   
   my_str("\nEmptying the list.\n");
   empty_list(&head);

   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head);


   my_str("\nTesting append()\n-------------------------------------------\n");

   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head); 

   my_str("\nappending a NULL to the head (which is null).\n");
   append(NULL, &head);
   
   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head);

   my_str("\nassigning tmp->elem to NULL then appending tmp to the head.\n");
   tmp->elem = NULL;
   append(tmp, &head);
   
	my_str("\ndebug_int - The List is empty.\n");
   debug_int(head);
   
   my_str("\nassigning tmp->elem to non-NULL then appending tmp to a NULL head.\n");
   tmp->elem = &n;
   append(tmp, NULL);
   
	my_str("\ndebug_int - The List is empty.\n");
   debug_int(head); 

   for (i = 0; i < 3; i++) {
   	my_str("\nappending a new node with ");
   	my_int(i);
   	my_char('\n');
      append(new_node(&arr[i], NULL, NULL), &head); 

      my_str("\nprints the list until this point.\n");
      debug_int(head);
      my_char('\n');
   }

   /* same as usual, 2 insertions should suffice */
   my_str("\nEmptying the list.\n");
   empty_list(&head);

   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head); 


   my_str("\nTesting add_node_at()\n--------------------------------------\n");

   add_node_at(NULL, &head, 1);
   
   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head); 

   tmp->elem = NULL;
   add_node_at(tmp, &head, 2);
   
   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head); 

   tmp->elem = &n;
   add_node_at(tmp, NULL, 3);
   
   my_str("\ndebug_int - The List is empty.\n");
   debug_int(head); 

  	/* 
  		I'm going overboard with these testing with indexes that are at the front 
  		and the back. I don't expect them to be as extreme. As long as they test 
  		0 once, large number once, empty list once, list with only one item once, 
  		and list with 2 or more items once, I'll be happy enough.
   */

   for (i = 0; i < 3; i++) {
   	my_str("\nadding a node at the head.\n");
   	printf("head: %p, &head: %p\n", (void*)head, (void*)&head);
      add_node_at(new_node(&arr[i], NULL, NULL), &head, 0);

      my_str("\nprints the list until this point.\n");
      debug_int(head);                                      
      my_char('\n');
   }

   my_str("Emptying the list.\n");
   empty_list(&head); 

   my_str("\ndebug_int - the list is empty.\n");
   debug_int(head);   

   for (i = 0; i < 3; i++) {
   	my_str("\nadding at the end of the list with a very large number.\n");
      add_node_at(new_node(&arr[i], NULL, NULL), &head, 438); 

      my_str("\nprints the list until this point.\n");
      debug_int(head);                                        
      my_char('\n');
   }

   my_str("Emptying the list.\n");
   empty_list(&head); 

   my_str("\ndebug_int - the list is empty.\n");
   debug_int(head);   

   /* putting all the ints in order to test the removes later on */
   my_str("\nAdding all the integers one after the other with add_node_at.\n");
   for (i = 0; i < 10; i++) {
      add_node_at(new_node(&arr[i], NULL, NULL), &head, i);
      debug_int(head);
      my_char('\n');
   }

   add_node_at(tmp, &head, 2);
   debug_int(head);
   my_char('\n');


   /* 
   	testing count nodes. Technically all they need to do is call it at 
   	some point with an empty list and with an non-empty one 
   */
   my_str("\nTesting count_nodes()\n--------------------------------------\n");
   
	my_str("\nCounting the nodes - 11.\n");
   my_int(count_s_nodes(head)); 
   my_char('\n');

   my_str("\nCounting the nodes with NULL passed- 0.\n");
   my_int(count_s_nodes(NULL));
   my_char('\n');
  

   /* 
   	testing removes: gonna remove a few items with each method, then test 
   	each with NULLs and lists of one item only 
   */
   my_str("\nTesting remove_node()\n--------------------------------------\n");

   my_str("\nThis should print the list\n");
   debug_int(head); 

   ret = remove_node(&head);
   my_int(*((int*)ret));
   my_char('\n');

   my_str("\nThis should print the list\n");
   debug_int(head); 
   my_char('\n');
   

   my_str("\nTesting remove_last()\n--------------------------------------\n");
   
   my_str("\nThis should print the list\n");
   debug_int(head);

   ret = remove_last(&head);
   my_int(*((int*)ret));
   my_char('\n');

   my_str("\nThis should print the list\n");
   debug_int(head);
   my_char('\n');


   my_str("\nTesting remove_node_at() with 0\n----------------------------\n");
   
   my_str("\nThis should print the list\n");
   debug_int(head); 

   ret = remove_node_at(&head, 0);
   my_int(*((int*)ret));
   my_char('\n');
   
   my_str("\nThis should print the list\n");
   debug_int(head); 
   my_char('\n');


   my_str("\nTesting remove_node_at() with a large number\n---------------\n");
   
   my_str("\nThis should print the list\n");
   debug_int(head); 

   ret = remove_node_at(&head, 243);
   my_int(*((int*)ret));
   my_char('\n');
   
   my_str("\nThis should print the list\n");
   debug_int(head); 
   my_char('\n');


   my_str("\nTesting remove_node_at with an in range number()\n-----------\n");
   debug_int(head);
   
   ret = remove_node_at(&head, 3);
   my_int(*((int*)ret));
   my_str("\n\n");
   
   debug_int(head);
   my_char('\n');

   my_str("\nEmptying List.\n");
   empty_list(&head);
   debug_int(head);
   my_char('\n');
   
   my_str("\nAdding back some elements and then removing them.\n");
   add_elem(&n, &head);

   my_str("\nThis should print the list\n");
   debug_int(head);
   my_str("\n\n");
   
   ret = remove_node(&head);
   my_int(*((int*)ret));
   my_str("\n\n");
   
   my_str("The List is empty.\n");
   debug_int(head);
   my_str("\n\n");
   
   add_elem(&n, &head);

   my_str("\nThis should print the list\n");
   debug_int(head);
   my_str("\n\n");
   
   ret = remove_last(&head);
   my_int(*((int*)ret));
   my_str("\n\n");
   
   my_str("The List is empty.\n");
   debug_int(head);
   my_str("\n\n");
   
   add_elem(&n, &head);

   my_str("\nThis should print the list\n");
   debug_int(head);
   my_str("\n\n");
   
   ret = remove_node_at(&head, 0);
   my_int(*((int*)ret));
   my_str("\n\n");
   
   my_str("The List is empty.\n");
   debug_int(head);
   my_str("\n\n");
   
   add_elem(&n, &head);

   my_str("\nThis should print the list\n");
   debug_int(head);
   my_str("\n\n");
   
   ret = remove_node_at(&head, 243);
   my_int(*((int*)ret));
   my_str("\n\n");
   
   my_str("The List is empty.\n");
   debug_int(head);
   my_str("\n\n");

	if (remove_node(&head) == NULL)
		my_str("Passed remove_node from empty\n");
	else
		my_panic("Failed remove_node from empty\n",1);

	if (remove_last(&head) == NULL)
		my_str("Passed remove_last from empty\n");
	else
		my_panic("Failed remove_last from empty\n",1);

	if (remove_node_at(&head, 0) == NULL)
		my_str("Passed remove_node_at 0 from empty\n");
	else
		my_panic("Failed remove_node_at 0 from empty\n",1);

	if (remove_node_at(&head, 3) == NULL)
		my_str("Passed remove_node_at 3 from empty\n");
	else
		my_panic("Failed remove_node_at 3 from empty\n",1);

	if (remove_node(NULL) == NULL)
		my_str("Passed remove_node from NULL\n");
	else
		my_panic("Failed remove_node from NULL\n",1);

	if (remove_last(NULL) == NULL)
		my_str("Passed remove_last from NULL\n");
	else
		my_panic("Failed remove_last from NULL\n",1);

	if (remove_node_at(NULL, 0) == NULL)
		my_str("Passed remove_node_at 0 from NULL\n");
	else
		my_panic("Failed remove_node_at 0 from NULL\n",1);

	if (remove_node_at(NULL, 3) == NULL)
		my_str("Passed remove_node_at 3 from NULL\n");
	else
		my_panic("Failed remove_node_at 3 from NULL\n",1);


	/* testing node_at and elem_at with NULLs */
	my_str("\n\nTesting node_at and elem_at with NULLS\n-----------------------\n");

	if (node_at(NULL, 0) == NULL)
		my_str("Passed node_at 0 from empty\n");
	else
		my_panic("Failed node_at 0 from empty\n", 1);
	
	if (node_at(NULL, 2) == NULL)
		my_str("Passed node_at 2 from empty\n");
	else
		my_panic("Failed node_at 2 from empty\n", 1);
	
	if (elem_at(NULL, 0) == NULL)
		my_str("Passed elem_at 0 from empty\n");
	else
		my_panic("Failed elem_at 0 from empty\n", 1);
	
	if (elem_at(NULL, 2) == NULL)
		my_str("Passed elem_at 2 from empty\n");
	else
		my_panic("Failed elem_at 2 from empty\n", 1);


	/* adding strings to list to test these 2 methods and the last debug ones */
	add_elem(str2, &head);
	my_char('\n');
	
	add_elem(str, &head);
	my_char('\n');
	
	debug_string(head);
	my_char('\n');
	
	traverse_string(head);
	my_char('\n');
	
	debug_char(head);
	my_char('\n');
	
	traverse_char(head);
	my_char('\n');
	
	my_str("\nPrinting the elem_at - Hello!\n");
	my_str((char*)elem_at(head, 0)); 
	my_char('\n');
	
	my_str("\nPrinting the elem_at - World!\n");
	my_str((char*)elem_at(head, 43));
	my_char('\n');
	
	tmp = node_at(head, 0);
	print_string(tmp);
	my_char('\n');
	
	tmp = node_at(head, 43);
	print_string(tmp);
	my_char('\n');
	
	/* this last one is mainly to clear memory */
	empty_list(&head);
	debug_string(head);
	
	return 0;
}