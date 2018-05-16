#include <bc_tracker.h>
#include "bc_cmd_factory.h"
#include "tracker.h"

void bc_update_cmd_internal(struct cmd_stream *stream, enum states state, int cmd, int status)
{
	int index = bc_cmd_index(cmd);
	if(index != -1) {
		command *cmd = stream->cmds + index;

		if (state < cmd->max_states)
		{
			clock_gettime(CLOCK_REALTIME, &cmd->timespec[state]);

			if (state == 0)
			{
				cmd->xcount++;
			}
			cmd->cur_state = state;
			cmd->status = status;
		}
	}
}

void bc_update_cmd(int cmd, enum states state, int status)
{
	if (can_we_use(cmd_stream.tracker))
		bc_update_cmd_internal(&cmd_stream, state, cmd, status);
}

void bc_update_cmd_tracker_header()
{
}

void bc_allocate_cmds(struct cmd_stream* stream, int size)
{
	stream->cmds = (command*) cmd_stream.tracker->mblock;

	bc_init_cmd(stream);
}

void bc_deallocate_cmds(struct cmd_stream* stream)
{
	if (stream->cmds)
			stream->cmds = NULL;
}

void bc_init_cmd_tracker()
{
	cmd_stream.tracker = bc_get_tracker_by_id(CMD_TRACKER_ID);

	bc_allocate_cmds(&cmd_stream, CMD_TRACKER_SIZE);
	bc_update_cmd_tracker_header();

	bc_enable_tracker(cmd_stream.tracker);
}

void bc_deinit_cmd_tracker()
{
	if (can_we_use(cmd_stream.tracker))
	{
		bc_disable_tracker(cmd_stream.tracker);
		bc_deallocate_tracker(cmd_stream.tracker);
		bc_deallocate_cmds(&cmd_stream);
	}
}
