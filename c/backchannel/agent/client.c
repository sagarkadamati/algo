#include "client.h"

void client()
{
	char buffer[1024];

	int cskt = alloc_socket();
	connect_socket(cskt);
	
	strcpy(buffer, "AAAAAAAAAAAAAAAAAA\n");
	send(cskt, buffer, 1024, 0);
	printf("Data sent: %s\n", buffer);

	recv(cskt, buffer, 1024, 0);
	printf("Data received: %s\n", buffer);

	release_socket(cskt);
}
