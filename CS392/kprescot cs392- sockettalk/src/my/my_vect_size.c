/* Michael John
 * I pledge my Honor that I have abided by The Stevens Honor System
 * February 29, 2015
 */

#include "my.h"

int my_vect_size(char** vec)
{
  int i = 0;
  int size = 0;
  char* temp = vec[i];
  while(temp != NULL)
    {
      size += my_strlen(temp);
      size++;
      i++;
      temp = vec[i];
    }
  return size;
}
