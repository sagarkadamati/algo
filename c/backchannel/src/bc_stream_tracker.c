#include "bc_stream_tracker.h"

void bc_update_stream_data(int sid)
{
	struct timespec spec;
	char * type;

	switch(stream_tracker.stream[sid].data->type)
	{
		case TYPE1:
			type = "TYPE1";
			break;
		case TYPE2:
			type = "TYPE2";
			break;
		default:
			type = "OTHER";
			break;
	}

	timespec_diff(&stream_tracker.stream[sid].data->trequest,
			&stream_tracker.stream[sid].data->tdone, &spec);
	bc_update_tracker(stream_tracker.stream[sid].mblock, 0,
			"\n| %-5s%-10d | %-5s%-10d | %-6s%-10s |  %4lu.%-9lu  | %5d |",
			"SID: ", stream_tracker.stream[sid].data->sid,
			"PID: ", stream_tracker.stream[sid].data->pid,
			"TYPE:", type,
			spec.tv_sec, spec.tv_nsec,
			stream_tracker.stream[sid].data->exe_count);
}

void bc_update_stream_cmd(int sid, enum position pos, int cmd, int status)
{
	bc_update_cmd_internal(stream_tracker.stream[sid].cmds, pos, cmd, status);
}

void bc_update_stream_type(int sid, enum STREAM_TYPE type)
{
	stream_tracker.stream[sid].data->type  = type;
}

int bc_get_stream_size()
{
	return sizeof(struct stream_struct);
}

int bc_get_cmd_size()
{
	return sizeof(cmd_struct) * CMDS_SIZE;
}

void bc_allocate_stream(pid_t pid, int sid)
{
	int size = bc_get_stream_size() + bc_get_cmd_size();

	stream_tracker.stream[sid].mblock = bc_allocate_mblock(stream_tracker.tracker, size);
	stream_tracker.stream[sid].cmds = bc_allocate_cmds(stream_tracker.tracker);

	stream_tracker.stream[sid].data = calloc(STREAM_SIZE, sizeof(struct stream_struct));
	stream_tracker.stream[sid].data->pid  = pid;
	stream_tracker.stream[sid].data->sid = sid;
	stream_tracker.stream[sid].data->type = 0;

	// bc_update_stream_header(int sid);
}

void bc_update_streams(int stream, const char *name, pid_t pid)
{
	if (stream_tracker.streams[stream].enable)
	{
		strcpy(stream_tracker.streams[stream].name, name);

		stream_tracker.streams[stream].id = stream;
		stream_tracker.streams[stream].pid = pid;
	}
}

void bc_update_streams_cmd(int stream, int cmd, enum position pos, int status)
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
				stream_tracker.streams[stream].cmds[id].xcount++;

				stream_tracker.streams[stream].cmds[id].enable = 1;

				clock_gettime(CLOCK_REALTIME,
					&stream_tracker.streams[stream].cmds[id].tenter);
				break;
			case EXIT:
				clock_gettime(CLOCK_REALTIME,
					&stream_tracker.streams[stream].cmds[id].texit);

				stream_tracker.streams[stream].cmds[id].status = status;

				timespec_diff(&stream_tracker.streams[stream].cmds[id].tenter,
					&stream_tracker.streams[stream].cmds[id].texit, &spec);

				stream_tracker.streams[stream].cmds[id].tavg = spec;
		}
	}
}

void bc_enable_stream(int stream)
{
	if (!stream_tracker.streams[stream].enable)
	{
		stream_tracker.streams[stream].enable = 1;
		stream_tracker.header->streams_size++;
	}
}

void bc_disable_stream(int stream)
{
	if (stream_tracker.streams[stream].enable)
	{
		stream_tracker.streams[stream].enable = 0;
		stream_tracker.header->streams_size--;
	}
}

void bc_update_stream_offsets()
{
	stream_tracker.header = (struct streams_header*) stream_tracker.mblock->mmap;
	stream_tracker.header->streams_offset = sizeof(struct streams_header);
	
	stream_tracker.streams = 
		(struct streams*)
		(stream_tracker.mblock->mmap + stream_tracker.header->streams_offset);
}

void bc_init_stream_tracker()
{
	int size = 100;

	stream_tracker.tracker = bc_allocate_tracker(STREAM_TRACKER);
	stream_tracker.mblock = bc_allocate_mblock(stream_tracker.tracker, size);

	bc_update_stream_offsets();
}

void bc_deinit_stream_tracker()
{
	bc_deallocate_tracker(stream_tracker.tracker);
	for (int sid = 0; sid < 512; sid++) {
		if(stream_tracker.stream[sid].data)
			free(stream_tracker.stream[sid].data);
	}
}