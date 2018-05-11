#include "data_processor.h"

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
