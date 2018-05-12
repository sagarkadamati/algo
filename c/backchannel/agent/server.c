#include "server.h"

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>

#include "../src/bc_tracker.h"
#include "../src/bc_time.h"

#define STREAM_FILE "bc_tracker"
#define MAX_BUF_SIZE 100

void send_data(int socket, char* ch, int size)
{
	int size_left = size;
	int offset = 0;;
	char buffer[1024];

	while(size_left)
	{
		if (size_left > MAX_BUF_SIZE)
		{
			send(socket, ch + offset, MAX_BUF_SIZE, 0);
			offset += MAX_BUF_SIZE;
			size_left -= MAX_BUF_SIZE;
		}
		else {
			send(socket, ch + offset, size_left, 0);
			offset += size_left;
			size_left = 0;
		}
		recv(socket, buffer, 1024, 0);
	}
}

void process_request(int socket)
{
	char buffer[1024];

	recv(socket, buffer, 1024, 0);

	strcpy(buffer, "My Hello World\n");
	send(socket, buffer, 1024, 0);
}

void serve_request(int socket)
{
	int fd, size;
	struct stat stat_buf;
	char buffer[1024];
	char* mmaped_mem;

	recv(socket, buffer, 1024, 0);

	fd = shm_open(STREAM_FILE, O_RDWR | O_CREAT, 0666);
	fstat(fd, &stat_buf);
	size = stat_buf.st_size;
	send(socket, &size, sizeof(int), 0);

	recv(socket, buffer, 1024, 0);

	mmaped_mem = (char*) mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	send_data(socket, mmaped_mem, size);

	munmap(mmaped_mem, size);
	close(fd);
}

void server(struct agent_struct *agent)
{
	agent->server_lskt = alloc_socket();
	bind_socket(agent->server_lskt);

	bc_load_trackers();

	while (1) {
		listen_for_connections(agent->server_lskt);
		agent->server_rskt = accept_connection(agent->server_lskt);

		serve_request(agent->server_rskt);
		release_socket(agent->server_rskt);
	}

	release_socket(agent->server_lskt);
}
