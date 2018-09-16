#include "my.h"
#include <strings.h>
#include <stdio.h>

#define BSIZE 1024

int main(int argc, char *argv[])
{	
	char buffer[BSIZE];
	int fdpar[2];
	int fdchild[2];
	int pid, length;
	char* read_in;

	if(argc < 2)
	{
		my_str("Usage: ");
		exit(2);
	}

	pipe(fdpar);

	if((pid = fork()) < 0)
	{
		my_str("Error: Bad fork parent");
		exit(1);
	}

	if(pid > 0)
	{
		close(fdpar[0]);
		read_in = my_vect2str(&argv[1]);
		/* parent */
		my_str("Parent: ");
		my_str(read_in);
		my_char('\n');

		write(fdpar[1], read_in, (my_strlen(read_in)));
		wait();
		exit(0);
	}
	else
	{
		close(fdpar[1]);
		/* child */
		length = read(fdpar[0], buffer, BSIZE - 1);
		buffer[length] = '\0';

		pipe(fdchild);
		if ((pid = fork()) < 0)
		{
			my_str("Error: Bad fork child");
			exit(1);
		}

		if (pid > 0)
		{
			close(fdchild[0]);

			my_str("Child: ");
			my_str(buffer);
			my_char('\n');

			write(fdchild[1], buffer, (my_strlen(buffer)));
			wait();
			exit(0);

		}
		else
		{
			close(fdchild[1]);
			/* grandchild */
			length = read(fdchild[0], buffer, BSIZE - 1);
			buffer[length] = '\0';


			my_str("Grandchild: ");
			my_str(buffer);
			my_char('\n');
			exit(0);
		}
	}
}
