#include "client.h"

int alloc_socket()
{
	return socket(PF_INET, SOCK_STREAM, 0);
}

void connect_socket(int socket)
{
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	addr_size = sizeof serverAddr;
	connect(socket, (struct sockaddr *)&serverAddr, addr_size);
}

void client()
{
	char buffer[1024];

	int clientSocket = alloc_socket();
	connect_socket(clientSocket);
	
	strcpy(buffer, "AAAAAAAAAAAAAAAAAA\n");
	send(clientSocket, buffer, 1024, 0);
	printf("Data sent: %s\n", buffer);

	recv(clientSocket, buffer, 1024, 0);
	printf("Data received: %s\n", buffer);
}
