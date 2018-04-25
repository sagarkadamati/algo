#ifndef __SOCKET__
#define __SOCKET__

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int alloc_socket(void);
void connect_socket(int socket);
void bind_socket(int socket);
void listen_for_connections(int socket);
int accept_connection(int socket);
void release_socket(int socket);

#endif /* __SOCKET__ */
