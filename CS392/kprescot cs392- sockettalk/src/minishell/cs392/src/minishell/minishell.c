#include "my.h"
#include <signal.h>
#include <unistd.h>
#include <errno.h>

#define BUFFERSIZE 1024

void exit_command()
{
	my_str("Exiting... \n");
	exit(0);
}

void controlCHandler()
{
	if (kill(getpid(), 0) == 0)
	{
		kill(getpid(),SIGKILL);
	}
}

void error_pid()
{
	my_str("Error forking... Exit\n");
	exit(1);
}

void error_program()
{
	my_str("Error: command not recognized.\n");
}

int main(int argc, char const *argv[])
{
	char** command;
	char* cwd;
	int pid;
	int read_in;
	int status;
	int i = 0;
	int x;
	char* buffer = (char*)malloc(sizeof(char) * BUFFERSIZE);
	char* dir = (char*)malloc(sizeof(char) * BUFFERSIZE);

	cwd = getcwd(buffer, 1024);
	signal(SIGINT, controlCHandler);


	while (1)
	{
		if(cwd !=NULL)
		{
			my_str("MINISHELL: ");
			my_str(cwd);
			my_str(" $: ");			
		}

		read_in = read(0, buffer, BUFFERSIZE-1);
		for (; buffer[i] != '\n' && buffer[i] != '\0'; i++);
		buffer[i] = '\0';
		command = my_str2vect(buffer);

		if (read_in > 1)
		{
			if (my_strncmp("exit", buffer, 4) == 0)
			{
				exit_command();
			}
			else if (my_strncmp("cd", buffer, 2) == 0)
			{
				dir = "\0";
				if (command[1][0] == '/')
				{
					if (chdir(command[1]) < 0)
					{
						my_str("Directory isn't real. \n");
					}
				}
				else
				{
					if (chdir(my_strconcat(my_strconcat(getcwd(dir, BUFFERSIZE-1), "/"), command[1])) < 0)
					{
						my_str("Directory isn't real.\n");
					}
				}
				/*if ((read_in = chdir(command[1])) < 0)
				{
					my_str("Invalid Directory. Try that again.\n");
				}*/
			}
			else
			{
				if ((pid = fork()) < 0)
				{
					error_pid();
				}
				else if (pid == 0)
				{
					if (execvp(*command, command) < 0)
					{
						my_str(buffer);
						my_str(" ");
						error_program();
					}
					exit(0);
				}
				else
				{
					wait();
				}
			}
		}
	}
	free(buffer);
	free(dir);
	for (i = 0; command[i] != NULL; i++)
	{
		free(command[i])
	}
	/*while (command)
	{
		free(*command);
	}
	free(buffer);
	
	return 0;*/

}
#undef BUFFERSIZE