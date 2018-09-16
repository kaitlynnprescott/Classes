#include "my.h"
#include <limits.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

int main(int argc, char **argv)
{
	/*Variable Declarations for Testing*/
	char str[] = {'H','E','L','L','O','\0'};
	char* arr = (char*)malloc(sizeof(char) * 20);
	char* temp;
	int maxneg = INT_MIN;
	/* 
	This can be calculated without the header using:
	int maxneg = 1 <<= (sizeof(int)*8)-1;
	*/

	/*Testing my_str()*/
	my_str("Testing my_str()\n----------------------------------------------\n");
	my_str(NULL);								my_str("\t|\tNULL\n");
	my_str("");									my_str("\t|\tEmpty String\n");
	my_str("Hello");							my_str("\t|\tHello\n");

	/*Testing my_int()*/
	my_str("\nTesting my_int()\n----------------------------------------------\n");
	my_int(-1); 								my_str("\t|\t-1\n");
	my_int(-156); 								my_str("\t|\t-156\n");
	my_int(0);									my_str("\t|\t0\n");
	my_int(3);									my_str("\t|\t3\n");
	my_int(30);									my_str("\t|\t30\n");
	my_int(maxneg);								my_str("\t|\tMax Neg\n");

	/*Testing my_num_base();*/
	my_str("\nTesting my_num_base()\n----------------------------------------------\n");
	my_num_base(17, NULL);						my_str("\t|\tNULL\n");
	my_num_base(17, "");						my_str("\t|\tEmpty Set\n ");
	my_num_base(5, "A");						my_str("\t|\tSingle Char - \"AAAAA\"\n ");
	my_num_base(-5, "A");						my_str("\t|\tSingle Char Neg - \"-AAAAA\"\n ");
	my_num_base(0, "01");						my_str("\t|\tZero - \"0\"\n ");
	my_num_base(4, "012345");					my_str("\t|\tSingle Digit - \"4\"\n ");
	my_num_base(18, "01");						my_str("\t|\tDouble Digit - \"10010\"\n ");
	my_num_base(-7, "0123456789ABCDEF");		my_str("\t|\tSingle Digit Negative - \"-7\"\n");
	my_num_base(-195, "0123456789ABCDEF");		my_str("\t|\tDouble Digit Negative - \"-C3\"\n");
	my_num_base(maxneg, "0123456789");			my_str("\t|\tTest Max Negative - \""); my_int(maxneg); my_str("\"\n\n");

	/*Testing Alpha and Digits*/
	my_str("\nTesting my_alpha and my_digits()\n----------------------------------------------\n");
	my_alpha();									my_str("\t|\tAlpha - ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
	my_digits();								my_str("\t|\tDigits - 0123456789\n");

	/*Testing my_strlen()*/
	my_str("\nTesting my_strlen()\n----------------------------------------------\n");
	my_int(my_strlen(NULL));					my_str("\t|\tNULL - \"-1\"\n");
	my_int(my_strlen(""));						my_str("\t|\tEmpty String - \"0\"\n");
	my_int(my_strlen("Hello"));					my_str("\t|\tRegular String - \"5\"\n");

	/*Testing my_revstr*/
	my_str("\nTesting my_revstr()\n----------------------------------------------\n");
	my_int(my_revstr(NULL));					my_str("\t|\tNULL - \"-1\"\n");
	my_int(my_revstr(""));						my_str("\t|\tEmpty String - \"0\"\n");
	my_int(my_revstr(str));						my_str("\t|\tRegular String Return - \"5\"\n");
	my_str(str);								my_str("\t|\tRegular String Changed - \"OLLEH\"\n");
	
	/*Testing my_strindex*/
	my_str("Testing my_strindex()\n----------------------------------------------\n");
	if(my_strindex(NULL, 'a') == -1) my_char('X');			my_str("\t|\tNull Pointer\n");
	if(my_strindex("", 'a') == -1) my_char('X');				my_str("\t|\tEmpty String\n");
	if(my_strindex(str, 'a') == -1) my_char('X');				my_str("\t|\tNot Found in String\n");
	my_int(my_strindex(str, 'L'));								my_str("\t|\tFound in String - \"1\"\n");
	
	/*Testing my_strrindex*/
	my_str("\nTesting my_strrindex()\n----------------------------------------------\n");
	if(my_strrindex(NULL, 'a') == -1) my_char('X');			my_str("\t|\tNull Pointer\n");
	if(my_strrindex("", 'a') == -1) my_char('X');				my_str("\t|\tEmpty String\n");
	if(my_strrindex(str, 'a') == -1) my_char('X');			my_str("\t|\tNot Found in String\n");
	my_int(my_strrindex(str, 'L'));								my_str("\t|\tFound in String - \"2\"\n");

	/*Testing my_strfind*/
	my_str("Testing my_strfind()\n----------------------------------------------\n");
	if(my_strfind(NULL, 'a') == NULL) my_char('X');			my_str("\t|\tNull Pointer\n");
	if(my_strfind("", 'a') == NULL) my_char('X');				my_str("\t|\tEmpty String\n");
	if(my_strfind(str, 'a') == NULL) my_char('X');				my_str("\t|\tNot Found in String\n");
	my_str(my_strfind(str, 'L'));								my_str("\t|\tFound in String - \"LLO\"\n");
	
	/*Testing my_strrfind*/
	my_str("\nTesting my_strrfind()\n----------------------------------------------\n");
	if(my_strrfind(NULL, 'a') == NULL) my_char('X');			my_str("\t|\tNull Pointer\n");
	if(my_strrfind("", 'a') == NULL) my_char('X');				my_str("\t|\tEmpty String\n");
	if(my_strrfind(str, 'a') == NULL) my_char('X');			    my_str("\t|\tNot Found in String\n");
	my_str(my_strrfind(str, 'L'));								my_str("\t|\tFound in String - \"LO\"\n");

	/*Testing my_strcmp*/
	my_str("\nTesting my_strcmp()\n----------------------------------------------\n");
	my_int(my_strcmp(NULL, NULL));								my_str("\t|\tBoth Null - \"0\"\n");
	my_int(my_strcmp(NULL, ""));								my_str("\t|\tLeft Empty - Negative\n");
	my_int(my_strcmp("", NULL));								my_str("\t|\tRight Empty - Positive\n");
	my_int(my_strcmp("", ""));									my_str("\t|\tBoth Empty - \"0\"\n");
	my_int(my_strcmp("abc", "abcd"));							my_str("\t|\tInequal Strings - Negative\n");
	my_int(my_strcmp("abcd", "abc"));							my_str("\t|\tInequal Strings - Positive\n");
	my_int(my_strcmp("abcd", "abcd"));							my_str("\t|\tSame String - \"0\"\n");

	/*Testing my_strncmp*/
	my_str("\nTesting my_strncmp()\n----------------------------------------------\n");
	my_int(my_strncmp(NULL, NULL, 50));							my_str("\t|\tBoth Null - \"0\"\n");
	my_int(my_strncmp(NULL, "", 60));							my_str("\t|\tLeft Empty - Negative\n");
	my_int(my_strncmp("", NULL, 20));							my_str("\t|\tRight Empty - Positive\n");
	my_int(my_strncmp("", "", 30));								my_str("\t|\tBoth Empty - \"0\"\n");
	my_int(my_strncmp("", NULL, 0));							my_str("\t|\tEmpty and NULL with 0 - Positive\n");
	my_int(my_strncmp("", NULL, -5));							my_str("\t|\tEmpty and NULL with Neg - Positive\n");
	my_int(my_strncmp("abc", "abcd", 42));						my_str("\t|\tInequal Strings - Negative\n");
	my_int(my_strncmp("abcd", "abc", 69));						my_str("\t|\tInequal Strings - Positive\n");
	my_int(my_strncmp("abcd", "abcd", 120));					my_str("\t|\tSame String - \"0\"\n");
	my_int(my_strncmp("abcdefg", "abcdfge", 3));				my_str("\t|\tSame String up to n - \"0\"\n");
	my_int(my_strncmp("apple", "dog", 0));						my_str("\t|\tDifferent Strings with 0 - \"0\"\n");
	my_int(my_strncmp("apple", "dog", -4));						my_str("\t|\tDifferent Strings with Neg - \"0\"\n");

	/*Testing my_strdup*/
	my_str("\nTesting my_strdup()\n----------------------------------------------\n");
	temp = my_strdup(str);
	if(my_strdup(NULL) == NULL) my_char('X');					my_str("\t|\tNull Pointer - X\n");
	my_str(temp);												my_str("\t|\tDuplicate String - \"HELLO\"\n");
	free(temp);
	
	/*Testing my_strcpy*/
	my_str("\nTesting my_strcpy()\n----------------------------------------------\n");
	if(my_strcpy(NULL, NULL) == NULL) my_char('X');				my_str("\t|\tBoth Null - X \n");
	if(my_strcpy(NULL, "Hey") == NULL) my_char('X');			my_str("\t|\tNULL Destination - X\n");
	my_str(my_strcpy(arr, "Hello"));							my_str("\t|\tCopy String - \"Hello\"\n");
	my_str(my_strcpy(arr, NULL));								my_str("\t|\tNULL Src - \"Hello\"\n");
	
	/*Testing my_strncpy*/
	my_str("\nTesting my_strncpy()\n----------------------------------------------\n");
	if(my_strncpy(NULL, "Hey", 69) == NULL) my_char('X');		my_str("\t|\tNULL Destination - X\n");
	my_str(my_strncpy(arr, "Hello", 25));						my_str("\t|\tCopy String - \"Hello\"\n");
	my_str(my_strncpy(arr, NULL, 5));							my_str("\t|\tNULL Src - \"Hello\"\n");
	my_str(my_strncpy(arr, "test", 3));							my_str("\t|\tCopy Some of String - \"tes\"\n");
	my_str(my_strncpy(arr, "nothing", 0));						my_str("\t|\tCopy 0 Chars- \"0 copied\"\n");
	my_str(my_strncpy(arr, "negative", -2));					my_str("\t|\tCopy 0 Chars- \"negative\"\n");

	/*Testing my_strcat*/
	my_str("\nTesting my_strcat()\n----------------------------------------------\n");
	my_strcpy(arr, "Hello ");
	if(my_strcat(NULL, "Hello") == NULL) my_char('X');			my_str("\t|\tNULL Destination\n");
	my_str(my_strcat(arr, NULL));								my_str("\t|\tNULL Src - \"Hello \"\n");
	my_str(my_strcat(arr, "World"));							my_str("\t|\tCat String - \"Hello World\"\n");

	/*Testing my_strconcat*/
	my_str("\nTesting my_strconcat()\n----------------------------------------------\n");
	if(my_strconcat(NULL, NULL) == NULL) my_char('X');			my_str("\t|\tBoth NULL\n");
	my_str((temp = my_strconcat(NULL, "Hello")));				my_str("\t|\tNULL Dst - \"Hello\"\n"); free(temp);
	my_str((temp = my_strconcat("Hola", NULL)));				my_str("\t|\tNULL Src - \"Hola\"\n"); free(temp);
	my_str((temp = my_strconcat("Hello ", "and Goodbye")));		my_str("\t|\tConcat 2 Strings - \"Hello and Goodbye\"\n"); free(temp);

	/*Testing my_strnconcat*/
	my_str("\nTesting my_strnconcat()\n----------------------------------------------\n");
	if(my_strnconcat(NULL, NULL, 50) == NULL) my_char('X');		my_str("\t|\tBoth NULL\n");
	my_str((temp = my_strnconcat(NULL, "Hello",3)));			my_str("\t|\tNULL Dst - \"Hello\" with 3\n"); free(temp);
	my_str((temp = my_strnconcat("Hola", NULL, 2)));			my_str("\t|\tNULL Src - \"Hola\" with 2\n"); free(temp);
	my_str((temp = my_strnconcat("Hello ", "and Goodbye", 7)));	my_str("\t|\tConcat 2 Strings - \"Hello and Goodbye\" with 7 \n"); free(temp);
	
	/*Testing my_atoi*/
	my_str("\nTesting my_atoi()\n----------------------------------------------\n");
	my_int(my_atoi("17"));										my_str("\t|\t 17\n");
	my_int(my_atoi("-15"));										my_str("\t|\t -15\n");
	my_int(my_atoi("he12lo3"));									my_str("\t|\t he12lo3 -> 12\n");
	my_int(my_atoi("Hello"));									my_str("\t|\t Hello -> 0\n");
	my_int(my_atoi(""));										my_str("\t|\t Empty 0\n");
	my_int(my_atoi(NULL));										my_str("\t|\t Null 0\n");


/*
	char *x[3];
	my_str("---Printing test for my_vect2str---\n");

	x[0] = "hello";
	x[1] = "world";
	x[3] = NULL;

	my_str(my_vect2str(x)); */
	return 0;
} 