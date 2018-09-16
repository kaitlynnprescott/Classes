#include "my.h"
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define BUFFERSIZE 1024

void killProc()
{
	int i = 0;
	char** command = 0;
	if (command != NULL)
	{
		while (command[i] != NULL)
		{
			free(command[i]);
			i++;
		}
		free(command);
	}
}

int main(int argc, char **argv)
{
	char** command; 
	char* cwd; 
	int pid; 
	int read_in; 
	int i;
	char buffer[BUFFERSIZE];
	int dir;

	signal(SIGINT, killProc);

	while (1)
	{
		my_str("MINISHELL: ");
		cwd = getcwd(buffer, BUFFERSIZE);
		my_str(cwd);
		my_str(" $: ");			

		if ((read_in = read(0, buffer, BUFFERSIZE - 1)) < 0)
		{
			my_str("Error reading.\n");
			exit(0);
		}
		buffer[read_in - 1] = '\0';
		command = my_str2vect(buffer);

		if (command[0] != NULL)
		{
			if (my_strcmp("help", command[0]) == 0)
			{
				my_str("\n\tMINISHELL HELP\t\n");
				my_str("Commands:\n");
				my_str("\tcd: changes current working directory.\n");
				my_str("\texit: exits minishell.\n");
				my_str("\thelp: prints help message with built in commands.\n");
				my_str("\tls: displays files within directory.\n");
				my_str("\tCTRL+C: kills current process.\n");
				my_str("\t<executable> <args>: run programs while in their directory.\n");
				my_str("\n");
			}
			else if (my_strcmp("exit", command[0]) == 0)
			{
				my_str("Exiting Minishell.");
				i = 0;
				if (command != NULL)
				{
					while (command[i] != NULL)
					{
						free(command[i]);
						i++;
					}
					free(command);
				}
				exit(0);
			}
			else if (my_strcmp("cd", command[0]) == 0)
			{
				if ((dir = chdir(command[1])) < 0)
				{
					if (command[1] == NULL)
					{
						my_str("invalid");
					}
					else
					{
						my_str(":");
						my_str(command[1]);
						my_str(": Directory isn't real.\n");
					}
				}
			}
			else
			{
				if ((pid = fork()) < 0)
				{
					my_str("Error forking.\n");
					exit(0);
				}
				else if (pid > 0)
				{
					wait(NULL);
				}
				else 
				{
					if ((dir = execvp(command[0], command)) < 0)
					{
						my_str(command[0]);
						my_str(": command not found.\n");
						exit(0);
					}
				}
			}
			i = 0;
			if (command != NULL)
			{
				while (command[i] != NULL)
				{
					free(command[i]);
					i++;
				}
				free(command);
			}
		}
	}
}
#undef BUFFERSIZE