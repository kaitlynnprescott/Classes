#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pid_t pid;
int running = 1;

void hello(int sig)
{
	printf("%s\n", "You pressed C!");
}

void received(int sig)
{
	if (sig == SIGTSTP)
	{
		kill(0, SIGTSTP);
	}
	else if (sig == SIGINT)
	{
		
	}
}

void child(int sig)
{
	if (sig == SIGUSR1)
	{
		printf("%s\n", "Signal Received!");
	}
}

void sigurs2()
{
	printf("%s\n", "child exiting... ");
	running = 0;

}

void alarmHandler()
{
	kill(pid, SIGKILL);
	raise(SIGSEGV);
}


int main()
{
	int pid = fork();
	while(1)
	{
		if (pid != 0)
		{
			signal(SIGTSTP, received);
			signal(SIGINT, sigurs2);
			alarm(10);
			signal(SIGALRM, alarmHandler);
			pause();
		}
		else if (pid == 0)
		{
			signal(SIGUSR1, received);
			signal(SIGUSR2, sigurs2);
			signal(SIGINT, 0);
			signal(SIGTSTP, 0);
	
		}
	}
	return 1;
}
