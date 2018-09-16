/*
*	Meng Qui, Kaitlynn Prescott and Christopher Rudel
*	I pledge my honor that I have abided by the Stevens Honor System
*	2/19/18
*	hashit.c
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TABLE_SIZE 101

typedef struct{
   char* keys[TABLE_SIZE];
   int num_keys;
}hash_set;

/*This function just sets everything in the hash_set struct to default */
void clear_table(hash_set *set)
{
   for(int i=0; i<101; i++)
	set->keys[i] = '\0';
   set->num_keys = 0;
}

/*This is just a helper function to hash */
int hKey(char* str)
{
   int len = strlen(str);
   int num = 0;
   for(int i=0; i<len; i++)
   {
	num+= (str[i] * (i+1)); 
   }
   num *= 19;
   return num;
   /* h(key)= 19* (ASCII(a_1)*1 + ... + ASCII(a_n)*n) */
}

int hash(char *key)
{
   int num = hKey(key); 
   num %= 101; /* Hash(key) = h(key) mod 101 */
   return num;
}

/*Returns -1 if not found, >-1 if found */
int findKey(hash_set *set, char *key)
{
   int ret = -1;
   for(int i=0; i<101; i++)
   {
	if(set->keys[i] != '\0')/* strcmp of \0 and key will segfault */
	{
	   if(strcmp(set->keys[i], key) == 0)
	      {
		ret=i;
		break;
	      }
	}
   }
   return ret;
}

/* Returns the key position, -1 if could not add */
int insert_key(hash_set *set, char *key)
{
   int hKey = hash(key);
   if(findKey(set,key) >= 0 ) /* spoj specifies to ignore insertion of key that already exists */
	return -1;
   if(set->keys[hKey] == '\0')
   {
	set->keys[hKey] = key;
	set->num_keys++;
   }
   else{
	for(int j=1; j<=19; j++)
	{
	   int jKey = (hKey + (j*j) + (23*j))%101; /* spoj specifies if there is no free position to put it in (Hash(key)+j^2+23*j) */
	   if(set->keys[jKey] == '\0')
	   {
		set->keys[jKey] = key;
		set->num_keys++;
		hKey = jKey;
		break;
	   }
	   else if(j ==19)
		hKey = -1;
	}
   }
   return hKey;
}

/* 0 if deletion did not occur, place of key if it occured */
int delete_key(hash_set *set, char *key)
{
   int place = findKey(set,key);
   if(place >= 0)
   {
	set->keys[place] = '\0';
	set->num_keys-=1;
	return place;
   }
   else return 0;
}

void display_keys(hash_set *set)
{
   for(int i=0; i<101; i++)
   {
	if(set->keys[i] != '\0')
	   printf("%d:%s\n", i, set->keys[i]);
   } 
}

int main()
{
   int times;
   scanf("%d", &times); /* This is the number of test cases */
   hash_set *s = malloc(sizeof(hash_set));
   for(int i=0; i<times; i++)
   {
      int n;
      scanf("%d", &n); /* This is the number of operations */
      for(int i=0; i<n; i++)
      {
   	   char* op = (char*)malloc(1000*sizeof(char));
	   scanf("%s", op); /* This is ADDing or DELeting keys */
	   if(op != NULL && strncmp(op,"ADD:", 4) == 0)
	      insert_key(s,&op[4]);
	   else if(op != NULL && strncmp(op, "DEL:", 4) == 0)
	      delete_key(s,&op[4]);
      }
      printf("%d\n", s->num_keys);
      display_keys(s);
      sleep(0);
      clear_table(s);
   }  
   free(s); /* I think this is all i have to free */
   return 0;
}

