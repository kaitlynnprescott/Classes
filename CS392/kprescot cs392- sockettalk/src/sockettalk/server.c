#ifndef SERVER 
#define SERVER 
#endif
#include "sockettalk.h"


void exit_server()
{
	my_str("Exiting Server.\n");
	close(gl_env.clientfd);
	close(gl_env.sockfd);
	exit(1);
}
void exit_server_cliet()
{
	close(gl_env.clientfd);
	close(gl_env.sockfd);
	exit(1);
}
void error_func(char* str)
{
	my_str(str);
	exit(1);
}
int main(int argc, char ** argv)
{
	int port_num, clilen, pid, n;
	struct sockaddr_in server_addr, client_addr;
	char *str, *username;
	if (argc >= 2)
	{
		port_num = my_atoi(argv[1]);
	}
	else
	{
		error_func("Invalid Input: ./server [port]\n");
	}
	if ((port_num < 1 || port_num > (2 << 15) - 1))
	{
		error_func("Invalid Input: ./server [port]\n");
	}
	signal(SIGINT, exit_server);

	if ((gl_env.sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		error_func("Cannot create socket.\n");
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_num);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&server_addr.sin_zero, 0, 8);

	if (bind(gl_env.sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
	{
		close(gl_env.sockfd);
		error_func("Cannot bind socket.\n");
	}
	if (listen(gl_env.sockfd, 5) < 0)
	{
		close(gl_env.sockfd);
		error_func("Cannot listen on socket.\n");
	}
	clilen = sizeof(client_addr);

	while(1)
	{
		memset(&client_addr, 0, sizeof(client_addr));
		if ((gl_env.clientfd = accept(gl_env.sockfd, (struct sockaddr*) &client_addr, &clilen)) < 0)
		{
			my_str("Cannot accept socket.\n");
			break;
		}
		if ((pid = fork()) < 0)
		{
			close(gl_env.clientfd);
			close(gl_env.sockfd);
			error_func("Error forking.\n");
		}
		else if (pid == 0)
		{
			signal(SIGINT, exit_server_cliet);
			close(gl_env.sockfd);
			str = (char*)malloc(BUFFER);
			username = my_strdup(str);
			username[my_strlen(username) - 1] = '\0';
			my_str("***");
			my_str(username);
			my_str(" connected.\n");
			free(str);
			for (str = (char*)malloc(BUFFER); (n = read(gl_env.clientfd, str, BUFFER)) > 0;)
			{
				if (my_strncmp("/exit", str, 5) == 0)
				{
					my_str("***");
					my_str(username);
					my_str(" disconnected.\n");
					close(gl_env.clientfd);
					free(username);
					free(str);
					exit(0);
				}
				else if (my_strncmp("/nick", str, 5) == 0)
				{
					my_str(username);
					my_str(" has changed to: ");
					free(username);
					username = my_strdup(&str[6]);
					username[my_strlen(username)-1] = '\0';
					my_str(username);
					my_str("\n");
				}
				else if (my_strncmp("/me", str, 3) == 0)
				{
					my_str("***");
					my_str(username);
					my_char(' ');
					my_str(&str[4]);
				}
				else
				{
					my_str(username);
					my_str(": ");
					my_str(str);
				}
				if ((n = write(gl_env.clientfd, "ACK", 2)) < 0)
				{
					close(gl_env.clientfd);
					free(username);
					free(str);
					error_func("Couldn't send ACK.\n");
				}
			}
		}
	}
	return 0;
}