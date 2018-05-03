#include "bc_stream_tracker.h"

void bc_tspec_avg(struct timespec *old, struct timespec* new, int count)
{
	old->tv_sec  *= (count - 1);
	old->tv_sec  += new->tv_sec;
	old->tv_sec  /= count;

	old->tv_nsec *= (count - 1);
	old->tv_nsec += new->tv_nsec;
	old->tv_nsec /= count;
}

void bc_update_stream_type(int stream, enum STREAM_TYPE type)
{
	if (stream_tracker.enable)
	{
		stream = stream_tracker.stream_index[stream];
		if (stream < stream_tracker.header->streams_count)
		{
			if (stream_tracker.streams[stream].enable)
				stream_tracker.streams[stream].type = type;
		}
	}
}

void bc_update_stream(int stream, const char *name, pid_t pid)
{
	if (stream_tracker.enable)
	{
		stream = stream_tracker.stream_index[stream];
		if (stream < stream_tracker.header->streams_count)
		{
			if (stream_tracker.streams[stream].enable)
			{
				strcpy(stream_tracker.streams[stream].name, name);

				stream_tracker.streams[stream].id = stream;
				stream_tracker.streams[stream].pid = pid;
				stream_tracker.streams[stream].type = 0;
			}
		}
	}
}

void bc_update_stream_cmd(int stream, int cmd, enum position pos, int status)
{
	if (stream_tracker.enable)
	{
		stream = stream_tracker.stream_index[stream];
		if (stream < stream_tracker.header->streams_count)
		{
			if (stream_tracker.streams[stream].enable)
			{
				struct timespec spec;

				int id = bc_cmd_index(cmd);
				char* name = bc_cmd_name(cmd);

				switch(pos)
				{
					case ENTER:
					 	strcpy(stream_tracker.streams[stream].cmds[id].name, name);
						stream_tracker.streams[stream].cmds[id].cmd = cmd;
						stream_tracker.streams[stream].cmds[id].enable = 1;
						stream_tracker.streams[stream].cmds[id].xcount++;

						clock_gettime(CLOCK_REALTIME,
							&stream_tracker.streams[stream].cmds[id].tenter);
						break;
					case EXIT:
						clock_gettime(CLOCK_REALTIME,
							&stream_tracker.streams[stream].cmds[id].texit);

						timespec_diff(&stream_tracker.streams[stream].cmds[id].tenter,
							&stream_tracker.streams[stream].cmds[id].texit, &spec);

						bc_tspec_avg(&stream_tracker.streams[stream].cmds[id].tavg, &spec,
									stream_tracker.streams[stream].cmds[id].xcount);

						stream_tracker.streams[stream].cmds[id].tavg   = spec;
						stream_tracker.streams[stream].cmds[id].status = status;
				}
			}
		}
	}
}

void bc_allocate_stream(int id)
{
	int stream;
	for (stream = 0; stream < MAX_STREAMS; stream++) {
		if (stream_tracker.streams[stream].used == 0) {
			stream_tracker.streams[stream].used = 1;
			stream_tracker.stream_index[id]		= stream;
			break;
		}
	}
}

void bc_enable_stream(int stream)
{
	if (stream_tracker.enable)
	{
		int index = stream_tracker.stream_index[stream];
		if (index == -1)
			bc_allocate_stream(stream);

		stream = stream_tracker.stream_index[stream];
		if (stream < stream_tracker.header->streams_count)
		{
			if (!stream_tracker.streams[stream].enable)
			{
				stream_tracker.streams[stream].enable = 1;
				stream_tracker.header->streams_size++;
			}
		}
	}
}

void bc_disable_stream(int stream)
{
	if (stream_tracker.enable)
	{
		stream = stream_tracker.stream_index[stream];
		if (stream < stream_tracker.header->streams_count)
		{
			if (stream_tracker.streams[stream].enable)
			{
				stream_tracker.streams[stream].enable = 0;
				stream_tracker.streams[stream].used = 0;
				stream_tracker.header->streams_size--;
				stream_tracker.stream_index[stream] = -1;
			}
		}
	}
}

void bc_setup_stream()
{
	int id;

	stream_tracker.header = (struct streams_header*) stream_tracker.tracker->mblock;
	stream_tracker.header->streams_offset = sizeof(struct streams_header);
	stream_tracker.header->streams_count  = MAX_STREAMS;
	stream_tracker.header->cmds_count     = CMDS_SIZE;

	stream_tracker.streams = (struct streams*)
		(stream_tracker.tracker->mblock + stream_tracker.header->streams_offset);

	for (id = 0; id < MAX_VSTREAMS; id++)
		stream_tracker.stream_index[id] = -1;
	
	for (id = 0; id < MAX_STREAMS; id++) {
		stream_tracker.streams[id].enable = 0;
		stream_tracker.streams[id].used   = 0;
	}

	stream_tracker.enable = 1;
}

void bc_init_stream_tracker()
{
	stream_tracker.tracker = bc_new_tracker(STREAM_TRACKER,
							(1 + MAX_STREAMS) * sizeof(struct streams));

	bc_setup_stream();
}

void bc_deinit_stream_tracker()
{
	if (stream_tracker.enable)
		bc_deallocate_tracker(stream_tracker.tracker);
}