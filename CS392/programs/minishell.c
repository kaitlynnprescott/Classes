#include <sys/wait.h>
#include "my.h"
#define BUFFERSIZE 100

void killProc()
{
	/* ctrl c */
	int i = 0;
	char** user_input = 0;
	if (user_input != NULL)
	{
		while (user_input[i] != NULL)
		{
			free(user_input[i]);
			i++;
		}
		free(user_input);
	}
}

int main(int argc, char** argv)
{
	int size, i;
	int pid;
	int retVal;
	char* curr;
	char** user_input;
	char buffer[BUFFERSIZE];
	signal(SIGINT, killProc);

	while (1)
	{
		my_str("MINISHELL: ");
		curr = getcwd(curr, BUFFERSIZE);
		my_str(curr);
		my_str(" / ");

		if ((size = read(0, buffer, BUFFERSIZE - 1)) < 0)
		{
			my_str("Error reading\n");
			exit(0);
		}
		buffer[size - 1] = '\0';
		user_input = my_str2vect(buffer);

		if (user_input[0] != NULL)
		{
			if (my_strcmp(user_input[0], "help") == 0)
			{
				/* user types help*/
				my_str("\n MINISHELL HELP DIRECTORY \n");
				my_str("Commands:\n");
				my_str(" cd <directory>: Changes the curr working directory to directory.\n");
				my_str(" exit: Exits the minishell.\n");
				my_str(" help: Prints a help message listing the built in commands.\n");
				my_str(" ls: Lists the files in the curr directory.\n");
				my_str(" CTRL + C: Kills the curr process.\n");
				my_str(" <executable> <args> -- Runs program executable if in the correct directory.\n");
				my_str("\n");
			}
			else if (my_strcmp(user_input[0], "exit") == 0)
			{
				/* user types exit*/
				my_str("Exiting Minishell.");
				i = 0;
				if (user_input != NULL)
				{
					while (user_input[i] != NULL)
					{
						free(user_input[i]);
						i++;
					}
					free(user_input);
				}
				exit(0);
			}
			else if (my_strcmp(user_input[0], "cd") == 0)
			{
				/*user types cd*/
				if ((retVal = chdir(user_input[1])) < 0)
				{
					if (user_input[1] == NULL)
					{
						my_str("Invalid input.");
					}
					else
					{
						my_str(":");
						my_str(user_input[1]);
						my_str(": Directory Not Found.\n");
					}
				}
			}
			else
			{
				if ((pid = fork()) < 0)
				{
					/*executables*/
					my_str("Error\n");
					exit(0);
				}
				if (pid > 0)
				{
					wait(NULL);
				}
				else
				{
					if ((retVal = execvp(user_input[0], user_input)) < 0)
					{
						my_str(user_input[0]);
						my_str(": Command Not Found.\n");
						exit(0);
					}
				}
			}
		
			i = 0;
			if (user_input != NULL)
			{
				while (user_input[i] != NULL)
				{
					free(user_input[i]);
					i++;
				}
				free(user_input);
			}
		}
	}

	return 0;
}