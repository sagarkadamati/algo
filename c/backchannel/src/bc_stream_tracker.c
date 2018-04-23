#include "bc_stream_tracker.h"

void bc_update_stream_header(int sid)
{
	bc_update_tracker(stream_tracker.stream[sid].mblock, 0,
		"|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(stream_tracker.stream[sid].mblock, 1,
		"\n| %-19s%-10s%-19s |  %14s  | %5s |",
		" ", "STREAM NAME", " ", "Execution Time", "Count");

	bc_update_tracker(stream_tracker.stream[sid].mblock, 2,
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(stream_tracker.stream[sid].mblock, (STREAM_SIZE - 1),
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");
}

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

void bc_update_stream(int sid, enum position pos, int cmd)
{
	if(!stream_tracker.stream[sid].data)
		return;

	// index = bc_get_stream_num(cmd);
	switch(pos)
	{
		case ENTER:
			clock_gettime(CLOCK_REALTIME, &stream_tracker.stream[sid].data->trequest);
			stream_tracker.stream[sid].data->exe_count++;
			break;
		case EXIT:
			clock_gettime(CLOCK_REALTIME, &stream_tracker.stream[sid].data->tdone);
			bc_update_stream_data(sid);
			break;
	}
}

void bc_update_stream_cmd(int sid, enum position pos, int cmd, int status)
{
	bc_update_cmd_internal(stream_tracker.stream[sid].cmds, pos, cmd, status);
}

void bc_update_stream_type(int sid, enum STREAM_TYPE type)
{
	stream_tracker.stream[sid].data->type  = type;
}

void bc_allocate_stream(pid_t pid, int sid)
{
	stream_tracker.stream[sid].mblock = bc_allocate_mblock(stream_tracker.tracker, STREAM_SIZE);
	stream_tracker.stream[sid].cmds = bc_allocate_cmds(stream_tracker.tracker);

	stream_tracker.stream[sid].data = calloc(STREAM_SIZE, sizeof(struct stream_struct));
	stream_tracker.stream[sid].data->pid  = pid;
	stream_tracker.stream[sid].data->sid = sid;
	stream_tracker.stream[sid].data->type = 0;

	// bc_update_stream_header(int sid);
}

void bc_init_stream_tracker()
{
	stream_tracker.tracker = bc_allocate_tracker(STREAM_TRACKER);
}

void bc_deinit_stream_tracker()
{
	bc_deallocate_tracker(stream_tracker.tracker);
	for (int sid = 0; sid < 512; sid++) {
		if(stream_tracker.stream[sid].data)
			free(stream_tracker.stream[sid].data);
	}
}
