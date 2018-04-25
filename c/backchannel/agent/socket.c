#include "socket.h"

int alloc_socket()
{
	return socket(PF_INET, SOCK_STREAM, 0);
}

void connect_socket(int socket)
{
	struct sockaddr_in serverAddr;
	socklen_t addr_size = sizeof serverAddr;
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	connect(socket, (struct sockaddr *)&serverAddr, addr_size);
}

void bind_socket(int socket)
{
	struct sockaddr_in serverAddr;
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	bind(socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));	
}

void listen_for_connections(int socket)
{
	listen(socket, 5);
}

int accept_connection(int socket)
{
	struct sockaddr_storage serverStorage;
	socklen_t addr_size = sizeof serverStorage;

	return accept(socket, (struct sockaddr *)&serverStorage, &addr_size);
}

void process_request(int socket)
{
	char buffer[1024];

	recv(socket, buffer, 1024, 0);
		
	strcpy(buffer, "My Hello World\n");
	send(socket, buffer, 1024, 0);
}

void release_socket(int socket)
{
	shutdown(socket, 2);
}