/* Michael John
 * February 6, 2015
 * I pledge my honor that I have abided by The Stevens Honor System
 */

#include "my.h"

/* pre: Takes a char* and an unsigned int
   post: Prints the char* and exits via 
   the unsigned int
   Crash.
*/
void my_panic(char *s, unsigned int n)
{
  my_str(s);
  exit(n);
}