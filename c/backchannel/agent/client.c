#include "client.h"

#include <stdlib.h>

void send_request(int socket)
{
	char buffer[1024];
	int size;
	char* ch;

	strcpy(buffer, "AAAAA\n");

	send(socket, buffer, 1024, 0);
	recv(socket, &size, sizeof(int), 0);

	ch = (char*) calloc(1, size);
	send(socket, buffer, 1024, 0);
	recv(socket, ch, size, 0);

	for(int i = 0; i < size; i++)
		printf("%c", ch[i]);
	free(ch);
}

void client()
{
	int cskt = alloc_socket();
	connect_socket(cskt);

	send_request(cskt);
	// send_request(cskt);

	release_socket(cskt);
}
