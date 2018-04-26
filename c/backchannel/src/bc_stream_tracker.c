#include "bc_stream_tracker.h"

void bc_update_stream_type(int stream, enum STREAM_TYPE type)
{
	if (stream < stream_tracker.header->streams_count)
	{
		if (stream_tracker.streams[stream].enable)
			stream_tracker.streams[stream].type = type;
	}
}

void bc_update_stream(int stream, const char *name, pid_t pid)
{
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

void bc_update_stream_cmd(int stream, int cmd, enum position pos, int status)
{
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

					stream_tracker.streams[stream].cmds[id].tavg   = spec;
					stream_tracker.streams[stream].cmds[id].status = status;
			}
		}
	}
}

void bc_enable_stream(int stream)
{
	if (stream < stream_tracker.header->streams_count)
	{
		if (!stream_tracker.streams[stream].enable)
		{
			stream_tracker.streams[stream].enable = 1;
			stream_tracker.header->streams_size++;
		}
	}
}

void bc_disable_stream(int stream)
{
	if (stream < stream_tracker.header->streams_count)
	{
		if (stream_tracker.streams[stream].enable)
		{
			stream_tracker.streams[stream].enable = 0;
			stream_tracker.header->streams_size--;
		}
	}
}

void bc_setup_stream()
{
	stream_tracker.header = (struct streams_header*) stream_tracker.mblock->mmap;
	stream_tracker.header->streams_offset = sizeof(struct streams_header);
	stream_tracker.header->streams_count  = STREAM_SIZE;
	stream_tracker.header->cmds_count     = CMDS_SIZE;
	
	stream_tracker.streams = 
		(struct streams*)
		(stream_tracker.mblock->mmap + stream_tracker.header->streams_offset);
}

void bc_init_stream_tracker()
{
	stream_tracker.tracker = bc_allocate_tracker(STREAM_TRACKER);
	stream_tracker.mblock = bc_allocate_mblock(stream_tracker.tracker, STREAM_SIZE);

	bc_setup_stream();
}

void bc_deinit_stream_tracker()
{
	bc_deallocate_tracker(stream_tracker.tracker);
}