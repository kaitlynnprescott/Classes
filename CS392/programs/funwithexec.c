#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	if ((pid = fork()) <0)
	{
		perror("Oh noes"), exit(1);
	}
	else if (pid == 0)
	{
		execlp("ls", "ls", "--asdhfishdjkls",NULL);
		printf("Hello from child\n");
	}
	else
	{
		int status;
		wait(&status); 
		int retval = WEXITSTATUS(status);
		// child process finishes before parent process
		printf("Hello from parent, the child says %d\n", retval);
	}

	return 0;
}