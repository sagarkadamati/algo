#include "socket.h"

#define LOCAL_HOST "127.0.0.1"

int alloc_socket()
{
	return socket(PF_INET, SOCK_STREAM, 0);
}

int connect_socket(int socket)
{
	struct sockaddr_in serverAddr;
	socklen_t addr_size = sizeof serverAddr;
	char* addr = getenv("SERVER_IP");

	serverAddr.sin_addr.s_addr = inet_addr(addr ? addr : LOCAL_HOST);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	return connect(socket, (struct sockaddr *)&serverAddr, addr_size);
}

int bind_socket(int socket)
{
	struct sockaddr_in serverAddr;
	char* addr = getenv("HOST_IP");

	serverAddr.sin_addr.s_addr = inet_addr(addr ? addr : LOCAL_HOST);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	return bind(socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
}

int listen_for_connections(int socket)
{
	return listen(socket, 5);
}

int accept_connection(int socket)
{
	struct sockaddr_storage serverStorage;
	socklen_t addr_size = sizeof serverStorage;

	return accept(socket, (struct sockaddr *)&serverStorage, &addr_size);
}

int release_socket(int socket)
{
	return shutdown(socket, 2);
}