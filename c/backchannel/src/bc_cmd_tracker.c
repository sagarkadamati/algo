#include "bc_cmd_tracker.h"

#include "bc_cmd_factory.h"

void bc_update_cmd_data(struct cmds *cmds, int index)
{
	struct timespec spec;

	timespec_diff(&cmds->cmd[index].tenter,
			&cmds->cmd[index].texit, &spec);

	bc_update_tracker(cmds->mblock, (index),
		"\n| %-50s | %4lu.%09lu | %5d | %5d |",
		cmds->cmd[index].name,
		spec.tv_sec, spec.tv_nsec,
		cmds->cmd[index].xcount,
		cmds->cmd[index].status);
}

void bc_update_cmd_internal(struct cmds *cmds, enum position pos, int cmd, int status)
{
	int index;

	if(cmds && cmds->cmd) {
		index = bc_cmd_index(cmd);
		switch(pos)
		{
			case ENTER:
				clock_gettime(CLOCK_REALTIME, &cmds->cmd[index].tenter);
				break;
			case EXIT:
				clock_gettime(CLOCK_REALTIME, &cmds->cmd[index].texit);

				cmds->cmd[index].xcount++;
				cmds->cmd[index].status = status;

				bc_update_cmd_data(cmds, index);
				break;
		}
	}
}

void bc_update_cmd(enum position pos, int cmd, int status)
{
	bc_update_cmd_internal(cmd_stream.cmds, pos, cmd, status);
}

void bc_update_cmd_tracker_header(struct cmds *cmds)
{
	bc_update_tracker(cmds->mblock, 0,
		"|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(cmds->mblock, 1,
		"\n| %-20s%-10s%-20s |  %14s  | %5s |",
		" ", "CMD NAME", " ", "Execution Time", "Count");

	bc_update_tracker(cmds->mblock, 2,
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(cmds->mblock, (BC_CMDS_COUNT - 1),
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");
}

struct cmds* bc_allocate_cmds(tracker *t)
{
	struct cmds *cmds = bc_calloc(1, sizeof(struct cmds));
	cmds->mblock = bc_allocate_mblock(t, CMDS_SIZE);
	cmds->cmd = bc_calloc(BC_CMDS_COUNT, sizeof(struct cmd_struct));
	if (cmds->cmd)
		bc_init_cmds(cmds->cmd);

	return cmds;
}

void bc_deallocate_cmds(struct cmds *cmds)
{
	if(cmds->mblock)
		bc_deallocate_mblock(cmds->mblock);

	if(cmds->cmd)
		bc_free(cmds->cmd);
}

void bc_init_cmd_tracker()
{
	cmd_stream.tracker = bc_allocate_tracker(CMD_TRACKER);
	cmd_stream.cmds = bc_allocate_cmds(cmd_stream.tracker);

	// bc_update_cmd_tracker_header(cmd_stream.cmds);
}

void bc_deinit_cmd_tracker()
{
	bc_deallocate_tracker(cmd_stream.tracker);
	bc_deallocate_cmds(cmd_stream.cmds);
}
