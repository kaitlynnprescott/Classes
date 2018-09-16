#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void main()
{
	// open file
	int fd = open("encrypted.txt", "O_RDONLY");
	int fd1 = open("solution.txt", "O_RDWR");
	int key = 5;
	char buf[3];
	while (fd != '\0')
	{
		int i;
		// read 3 characters
		int num read(fd, buf, strlen(buf));
		// decode with key = 5
		for(i = 0; i <= strlen(buf); i++)
		{
			// take a char from those read in

			// subtract key value
			num[i] -= key;
			// add decrypted character to new txt file
			int num[i] = write(solution.txt, buf, strlen(buf));

		}
		// write 3 characters to solution
		
		// increase key
		key += 2;
	}

	// read full solution.txt

}