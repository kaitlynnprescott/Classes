#include "my.h"
#include <limits.h>


int main(int argc, char const *argv[])
{
	char* ptr;
	char str[] = {'h', 'e', 'l', 'l', 'o', '\0'};
	ptr = my_malloc(sizeof(str));
	my_strcpy(ptr, str);
	my_str(ptr);
	my_str("\n");
	return 0;
}