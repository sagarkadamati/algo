#include "client.h"

#include "data_processor.h"

#define MAX_BUF_SIZE 100

void receive_data(int socket, char* ch, int size)
{
	int size_left = size;
	int offset = 0;;
	char buffer[1024];

	strcpy(buffer, "AAAAA\n");
	while(size_left)
	{
		if (size_left > MAX_BUF_SIZE)
		{
			recv(socket, ch + offset, MAX_BUF_SIZE, 0);
			offset += MAX_BUF_SIZE;
			size_left -= MAX_BUF_SIZE;
		}
		else {
			recv(socket, ch + offset, size_left, 0);
			offset += size_left;
			size_left = 0;
		}
		send(socket, buffer, 1024, 0);
	}
}

void start_request(int socket)
{
	char buffer[1024];
	char* ch;
	int size;

	strcpy(buffer, "AAAAA\n");

	send(socket, buffer, 1024, 0);
	recv(socket, &size, sizeof(int), 0);
	if (agent.verbose)
		printf("DEBUG: file size: %d\n", size);

	ch = (char*) calloc(1, size);
	send(socket, buffer, 1024, 0);
	if (agent.verbose)
		printf("DEBUG: file receive in progress...");
	receive_data(socket, ch, size);
	if (agent.verbose)
		printf("done\n");

	bc_init_tracker();
	bc_load_trackers_from_data(ch, size);
	process_data();

	free(ch);
}

void client()
{
	int cskt = alloc_socket();
	if (agent.verbose)
		printf("DEBUG: connetcing...");
	if (!connect_socket(cskt))
	{
		if (agent.verbose)
			printf("done\n");
		start_request(cskt);
		release_socket(cskt);
	}
	else {
		if (agent.verbose)
			printf("fail\n");
	}
}
