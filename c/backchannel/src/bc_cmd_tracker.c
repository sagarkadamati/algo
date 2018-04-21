#include "bc_cmd_tracker.h"
#include "bc_cmd_factory.h"

void bc_update_cmd_data(int index)
{
	struct timespec spec;

	timespec_diff(&cmd_stream.cmds[index].tenter,
			&cmd_stream.cmds[index].texit, &spec);

	bc_update_tracker(cmd_stream.tracker, (index + 3),
		"\n| %-50s | %4lu.%09lu | %5d | %5d |",
		cmd_stream.cmds[index].name,
		spec.tv_sec, spec.tv_nsec,
		cmd_stream.cmds[index].xcount,
		cmd_stream.cmds[index].status);
}

void bc_update_cmd(enum position pos, int cmd, int status)
{
	int index;

	if(!cmd_stream.cmds)
		return;

	index = bc_cmd_index(cmd);
	switch(pos)
	{
		case ENTER:
			clock_gettime(CLOCK_REALTIME, &cmd_stream.cmds[index].tenter);
			break;
		case EXIT:
			clock_gettime(CLOCK_REALTIME, &cmd_stream.cmds[index].texit);

			cmd_stream.cmds[index].xcount++;
			cmd_stream.cmds[index].status = status;

			bc_update_cmd_data(index);
			break;
	}
}

void bc_update_cmd_tracker_header()
{
	bc_update_tracker(cmd_stream.tracker, 0,
		"|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(cmd_stream.tracker, 1,
		"\n| %-20s%-10s%-20s |  %14s  | %5s |",
		" ", "CMD NAME", " ", "Execution Time", "Count");

	bc_update_tracker(cmd_stream.tracker, 2,
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(cmd_stream.tracker, (BC_CMDS_COUNT - 1),
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");
}

void* bc_allocate_cmds()
{
	void* data = calloc(BC_CMDS_COUNT, sizeof(struct cmd_struct));
	if (data)
		bc_init_cmds(data);

	return data;
}

void bc_deallocate_cmds()
{
	if(cmd_stream.cmds)
		free(cmd_stream.cmds);
}

void bc_init_cmd_tracker()
{
	cmd_stream.tracker = bc_allocate_tracker(CMD_TRACKER, BC_CMDS_COUNT);

	bc_update_cmd_tracker_header();
	cmd_stream.cmds = bc_allocate_cmds();
}

void bc_deinit_cmd_tracker()
{
	bc_deallocate_tracker(cmd_stream.tracker);
	bc_deallocate_cmds();
}
