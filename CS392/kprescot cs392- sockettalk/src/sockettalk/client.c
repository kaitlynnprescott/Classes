#include "sockettalk.h"

void error_func(char* str)
{
	my_str(str);
	exit(1);
}
void exit_client()
{
	my_str("Exiting Client.\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int port_num, n;
	struct hostent *server;
	struct sockaddr_in serv_addr;
	char *str, *username;
	if (argc >= 3)
	{
		port_num = my_atoi(argv[2]);
	}
	else
	{
		error_func("Invalid Input: ./client [host] [port]\n");
	}
	if ((port_num < 1 || port_num > (2 << 15) - 1))
	{
		error_func("Invalid Input: ./client [host] [port].\n");
	}
	signal(SIGINT, exit_client);
	signal(SIGALRM, exit_client);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		error_func("Cannot create socket.\n");
	}
	if ((server = gethostbyname(argv[1])) == NULL)
	{
		close(sockfd);
		error_func("Cannot find host.\n");
	}
	if (server->h_length <= 0)
	{
		close(sockfd);
		error_func("Cannot find host address.\n");
	}
	memset(&serv_addr.sin_zero, 0, 8);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_num);
	memcpy(&(serv_addr.sin_addr.s_addr), server->h_addr, server->h_length);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		close(sockfd);
		error_func("Cannot connect to host.\n");
	}
	str = (char*)malloc(BUFFER);
	my_str("Username: ");
	if ((n = read(STDIN_FILENO, str, BUFFER)) <= 0)
	{
		close(sockfd);
		error_func("No username.\n");
	}
	username = my_strdup(str);
	username[my_strlen(username)-1] = '\0';
	my_char('\n');

	if ((n = write(sockfd, str, BUFFER)) < 0)
	{
		close(sockfd);
		error_func("Username not sent to server.\n");
	}
	while (1)
	{
		memset(str, 0, BUFFER);
		my_str(username);
		my_str(": ");
		if ((n = read(STDIN_FILENO, str, BUFFER)) <= 0)
		{
			my_str("Could not read.\n");
			break;
		}
		if (write(sockfd, str, BUFFER) < 0)
		{
			my_str("Cannot send message to host.\n");
			break;
		}
		if (my_strncmp("/nick", str, 5) == 0)
		{
			free(username);
			username = my_strdup(&str[6]);
		}
		else if (my_strncmp("/exit", str, 5) == 0)
		{
			my_str("Exiting Client.\n");
			break;
		}
		alarm(2);
		if ((n = read(sockfd, str, BUFFER)) > 0)
		{
			alarm(0);
		}
		else if (n == 0)
		{
			my_str("No ack from server.\n");
			break;
		}
	}
	close(sockfd);
	free(str);
	free(username);
	return 0;
}