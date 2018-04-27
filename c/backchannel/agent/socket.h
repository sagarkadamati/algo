#ifndef __SOCKET__
#define __SOCKET__

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int alloc_socket(void);
int connect_socket(int socket);
int bind_socket(int socket);
int listen_for_connections(int socket);
int accept_connection(int socket);
int release_socket(int socket);

#endif /* __SOCKET__ */
