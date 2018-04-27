#include "client.h"

#include <stdlib.h>
#include <time.h>

#include "../src/bc_stream_tracker.h"

#define MAX_BUF_SIZE 4096

void receive_data(int socket, char* ch, int size)
{
	int size_left = size;
	int offset = 0;;

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
	}
}

void send_request(int socket)
{
	char buffer[1024];
	int size;
	char* ch;
	struct streams_header *header;
	struct streams *stream;
	struct streams *streams;
	int offset;

	strcpy(buffer, "AAAAA\n");

	send(socket, buffer, 1024, 0);
	recv(socket, &size, sizeof(int), 0);

	ch = (char*) calloc(1, size);
	send(socket, buffer, 1024, 0);
	recv(socket, ch, size, 0);

	header = (struct streams_header*)ch;
	offset = header->streams_offset;
	size = header->streams_size;
	streams = (struct streams*) (ch + offset);

	for (int i = 0; i < size; i++) {
		stream = streams + i;
		if (stream->enable) {
			printf("| %-8s%-10s | %-8s%-10d |\n",
				"Name : ", stream->name,
				"PID  : ", stream->pid);

			for (int j = 0; j < header->cmds_count; j++) {
				if (stream->cmds[j].enable) {
					printf("| %-8s%-10s | %-8s%-10d |  %4lu.%-9lu\n",
						"CMD  : ", stream->cmds[j].name,
						"Count: ", stream->cmds[j].xcount,
						stream->cmds[j].tenter.tv_sec,
						stream->cmds[j].tenter.tv_nsec);
				}
			}
		}
	}

	// for(int i = 0; i < size; i++)
	// 	printf("%c", ch[i]);
	free(ch);
}

void client(int argc, char *argv[])
{
	int cskt = alloc_socket();
	connect_socket(cskt);

	send_request(cskt);
	// send_request(cskt);

	release_socket(cskt);
}