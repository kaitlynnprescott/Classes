#define _DEFAULT_SOURCE
#include <unistd.h>
#include "my.h"

void* my_malloc(int s) 
{
	/*
	 write my_malloc(int) which keeps track of the location of the 
	 program break, uses sbrk(2) to increment it, and returns the 
	 location of the newly allocated memory.
	*/
	void* res;
	res = sbrk(s);
	return res;
}

