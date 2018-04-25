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
#include <time.h>
#include <stddef.h>

#define CMDS_FILE "bc_cmds"

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

	fd = shm_open(CMDS_FILE, O_RDWR | O_CREAT, 0666);
	fstat(fd, &stat_buf);
	size = stat_buf.st_size;
	send(socket, &size, sizeof(int), 0);

	recv(socket, buffer, 1024, 0);

	mmaped_mem = (char*) mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	send(socket, mmaped_mem, size, 0);

	munmap(mmaped_mem, size);
	close(fd);
}

void server()
{
	int sskt, cskt;

	sskt = alloc_socket();
	bind_socket(sskt);

	while (1) {
		listen_for_connections(sskt);
		cskt = accept_connection(sskt);

		serve_request(cskt);
		// serve_request(cskt);

		release_socket(cskt);	
	}

	release_socket(sskt);
}
