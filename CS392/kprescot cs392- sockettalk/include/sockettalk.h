
#ifndef _SOCKETTALK_H_
#define _SOCKETTALK_H_

#include "my.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define BUFFER 256
#ifdef SERVER
	void exit_server();
	void exit_server_client();
	struct s_env{
		int sockfd, clientfd;
	} gl_env;
#else
	#include <netdb.h>
	void exit_client();
	int sockfd;
#endif

#endif