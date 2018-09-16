#include "my.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <strings.h>
#include <openssl/blowfish.h>

#define SIZE 8

void exit_func()
{
	my_str("Exiting Server.");
	exit(0);
}
void error_func(char* str)
{
	my_str(str);
	exit(1);
}

int main(int argc, char **argv)
{
	int sockfd, port_num, pid, clinlen, sockfd_2, n;
	unsigned char buffer[4096];
	char* user_name;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;	
	BF_KEY *key = calloc(1, sizeof(BF_KEY));
	BF_set_key(key, SIZE, (const unsigned char*)"Password");
	unsigned char* hashed = calloc(SIZE+1, sizeof(char));

	if(argc < 1)
	{
		error_func("Invalid input: ./server [port] \n");
	}
	else
	{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		signal(SIGINT, exit_func);

		if (sockfd < 0)
		{
			error_func("Socket error.");
		}
		bzero((char*)&server_addr, sizeof(server_addr));
		port_num = my_atoi(argv[1]);

		if (port_num < 1 || port_num > 65535)
		{
			error_func("Invalid port number. \n");
		}

		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = INADDR_ANY;
		server_addr.sin_port = htons(port_num);

		if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		{
			error_func("Binding error.");
		}

		listen(sockfd, 5);

		while (1)
		{
			clinlen = sizeof(client_addr);
			sockfd_2 = accept(sockfd, (struct sockaddr*)&client_addr, &clinlen);

			if (sockfd_2 == 0)
			{
				my_str("Socket Closed. \n");
			}
			if (sockfd_2 < 0)
			{
				error_func("Accept error.");
			}
			my_str("Aschente! \n");
			if (n < 0)
			{
				error_func("Read error.");
			}

			if ((pid = fork()) < 0)
			{
				error_func("Fork error.");
			}
			if (pid == 0)
			{
				user_name = NULL;
				close(sockfd);

				n = read(sockfd_2, buffer, 4095);
				buffer[n] = '\0';
				user_name = my_strdup(buffer);
				my_str(user_name);
				my_str(" has connected. \n");
				while (1)
				{
					bzero(buffer, 4096);
					n = read(sockfd_2, buffer, 4095);

					if (n == 0)
					{
						my_str(user_name);
						my_str(" disconnected. \n");
						close(sockfd_2);
						free(user_name);
						exit(5);
					}
					buffer[n] = '\0';
					printf("%d", n);
					puts(buffer);

					BF_ecb_encrypt(buffer, hashed, key, BF_DECRYPT);

					if (my_strncmp(buffer, "/exit", 5) == 0)
					{
						my_str(user_name);
						my_str( "disconnected. \n");
						close(sockfd_2);
						free(user_name);
						exit(5);
					}
					else if (my_strncmp(buffer, "/nick", 5) == 0)
					{
						my_str(user_name);
						my_str(" changed to: ");
						user_name = my_strdup(&buffer[6]);
						my_str(user_name);
						my_char('\n');
					}
					else if (my_strncmp(buffer, "/me", 3) == 0)
					{
						my_str(user_name);
						my_char(' ');
						my_str(my_strdup(&buffer[4]));
						my_char('\n');
					}
					else
					{
						my_str(user_name);
						my_str(": ");
						my_str(hashed);
						my_char('\n');
					}
				}
			}
			close(sockfd_2); 
		}
	}

	return 0;
}