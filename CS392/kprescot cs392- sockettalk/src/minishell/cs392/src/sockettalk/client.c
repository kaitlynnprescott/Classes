#include "my.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h> 
#include <strings.h>
#include <openssl/blowfish.h>

#define SIZE 8
void exit_func()
{
	my_str("Exiting Client.");
	exit(0);
}
void error_func(char* str)
{
	my_str(str);
	exit(1);
}

int main(int argc, char **argv)
{
	int sockfd, port_num, n, i;
	struct sockaddr_in server_addr;
	struct hostent *server;
	char buffer[1024];
	char* user_name;
	unsigned char* password = calloc(SIZE+1, sizeof(char));
	BF_KEY *key = calloc(1, sizeof(BF_KEY));
	BF_set_key(key, SIZE, (const unsigned char*) "Password");

	if(argc < 2)
	{
		error_func("Invalid Input: ./client [host] [port]");
	}
	else
	{
		signal(SIGINT, exit_func);
		port_num = my_atoi(argv[2]);
		sockfd = socket(AF_INET, SOCK_STREAM, 0);

		if(sockfd < 0)
		{
			error_func("Socket error.");
		}
		server = gethostbyname(argv[1]);

		if (server == NULL)
		{
			error_func("Server error.");
		}

		bzero((char*)&server_addr, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port_num);
		bcopy((char*)server->h_addr, (char*)&server_addr.sin_addr.s_addr, server->h_length);

		if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		{
			error_func("Cannot connect.");
		}

		my_str("Aschente!\n");

		/* add commands*/
		my_str("Commands: /nick, /me, /exit \n");
		my_str("Enter Username: ");
		bzero(buffer, 1024);
		user_name = (char *)malloc(100*sizeof(char));

		n = read(0, user_name, 99);
		user_name[n] = '\0';

		i = 0;
		while (user_name[i] != '\0')
		{
			if (user_name[i++] == '\n')
			{
				user_name[--i] = '\0';
			}
		}

		if (n <= 0)
		{
			error_func("Username Error.");
		}

		n = write(sockfd, user_name, my_strlen(user_name));

		while (1)
		{
			bzero(buffer, 1024);
			my_str(user_name);
			my_str(": ");

			n = read(0, buffer, 1023);

			i = 0;
			while (buffer[i] != '\0')
			{
				if (buffer[i++] == '\n')
				{
					buffer[--i] = '\0';
				}
			}

			if (n <= 0)
			{
				error_func("Read error.");
			}
			BF_ecb_encrypt((unsigned char*)buffer, password, key, BF_ENCRYPT);
			puts(buffer);
			puts(password);
			printf("%d", my_strlen(password));

			if ((n = write(sockfd, password, my_strlen(password))) < 0)
			{
				error_func("Write error.");
			}

			if (n == 0)
			{
				continue;
			}

			if (my_strncmp(buffer, "/exit", 5) == 0)
			{
				exit_func();
			}

			if (my_strncmp(buffer, "/nick", 5) == 0)
			{
				free(user_name);
				user_name = my_strdup(&buffer[6]);
			}

			if (my_strncmp(buffer, "/me", 3) == 0)
			{
				my_str(user_name);
				my_str(" ");
				my_str(&buffer[4]);
			}
		}
	}

	return 0;
}