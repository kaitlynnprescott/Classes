
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef void (*signalhandler_t)(int);
char c = '\0';

void handle_signal(int signo)
{
	my_str("\nMINISHELL: ");
	fflush(stdout);
}

void fill_argv(char *tmp_argv)
{
	char *foo = temp_argv;
	int index = 0;
	char ret[100];
	bzero(ret, 100);
	while (*foo !0 '\0')
	{
		if (index == 10)
		{
			break;
		}
		if (*foo == ' ')
		{
			if (my_argv[index] == NULL)
			{
				my_argv[index] = (char *)malloc(sizeof(char) *my_strlen(ret) + 1);
			}
			else
			{
				bzero(my_argv[index], my_strlen(my_argv[index]));
			}
			my_strncpy(my_argv[index], ret, my_strlen(ret));
			my_strncat(my_argv[index], "\0", 1);
			bzero(ret, 100);
			index++;
		}
		else
		{
			my_strncat(ret, foo, 1);
		}
		foo++;
	}
	if (ret[0] != '\0')
	{
		my_argv[index] = (char *)malloc(sizeof(char) * my_strlen(ret) + 1);
		my_strncpy(my_argv[index], ret, my_strlen(ret));
		my_strncat(my_argv[index], "\0", 1);
	}
}

int attach_path(char *cmd)
{
	char ret[100];
	int i, fd;
	bzero(ret, 100);
	for (i = 0; search_path[i]!= NULL; i++)
	{
		my_strcpy(ret, search_path[i]);
		my_strncat(ret, cmd, my_strlen(cmd));
		if ((fd = open(ret, O_RDONLY)) > 0)
		{
			my_strncpy(cmd, ret, my_strlen(ret));
			close(fd);
			return 0;
		}
	}
	return 0;
}

void get_path_string(char** tmp_envp, char* bin_path)
{
	int count = 0;
	char *tmp;
	while(1)
	{
		tmp = strstr(tmp_envp[count], "PATH");
		if (tmp)
	}
}

int main(int argc, char** argv, char** envp)
{
	/* code */
	char c;
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_signal);
	my_str("\nMINISHELL: ");
	while (c != EOF)
	{
		c = getchar();
		switch(c)
		{
			case '\n':
				bzero(tmp, sizeof(tmp));
				break;
			default: 
				my_strncat(temp, &c, 1);
				break;
		}
		if (c == '\n')
		{
			my_str("\nMINISHELL: ");
		}
	}
	my_str("\n");
	return 0;
}