#include "client.h"

#include <stdlib.h>
#include "time.h"

#include "../src/bc_tracker.h"
#include "../src/bc_stream_tracker.h"

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

void process_data(char* ch, int size, int verbose)
{
	struct streams_header *header;
	struct streams *stream;
	struct streams *streams;
	int offset;
	int i, j;

	bc_init_tracker();
	bc_load_trackers_from_data(ch, size);
	ch = ch + new_trackers.theaders[2].offset;

	tracker* t = bc_get_tracker_by_id(STREAM_TRACKER_ID);
	ch = t->mblock;

	header = (struct streams_header*)ch;
	offset = header->streams_offset;
	size = header->streams_size;
	streams = (struct streams*) (ch + offset);

	if (verbose)
		printf("DEBUG: Processing data\n");
	for (i = 0; i < size; i++) {
		stream = streams + i;
		if (stream->enable) {
			printf("%s %d: %d\n",
				stream->name,
				stream->id,
				stream->pid);

			for (j = 0; j < header->cmds_count; j++) {
				if (stream->cmds[j].enable) {
					printf("%4s %-40s: %5d, %4lu.%09lu sec\n",
						"", stream->cmds[j].name,
						stream->cmds[j].xcount,
						stream->cmds[j].tavg.tv_sec,
						stream->cmds[j].tavg.tv_nsec);
				}
			}
		}
	}
}

void start_request(int socket, int verbose)
{
	char buffer[1024];
	char* ch;
	int size;

	strcpy(buffer, "AAAAA\n");

	send(socket, buffer, 1024, 0);
	recv(socket, &size, sizeof(int), 0);
	if (verbose)
		printf("DEBUG: file size: %d\n", size);

	ch = (char*) calloc(1, size);
	send(socket, buffer, 1024, 0);
	if (verbose)
		printf("DEBUG: file receive in progress...");
	receive_data(socket, ch, size);
	if (verbose)
		printf("done\n");
	
	process_data(ch, size, verbose);

	free(ch);
}

void client(struct agent_struct *agent)
{
	int cskt = alloc_socket();
	if (agent->verbose)
		printf("DEBUG: connetcing...");
	if (!connect_socket(cskt))
	{
		if (agent->verbose)
			printf("done\n");
		start_request(cskt, agent->verbose);
		release_socket(cskt);
	}
	else {
		if (agent->verbose)
			printf("fail\n");
	}
}
