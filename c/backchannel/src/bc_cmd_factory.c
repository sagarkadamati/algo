#include "bc_cmd_tracker.h"
#define CMDS_FILE "bc_cmds.h"
#include "bc_cmd_factory.h"

#undef  ADD_CMD
#define ADD_CMD(_cmd) \
	case _cmd: \
		return BC_##_cmd;\
		break;

int bc_cmd_index(int cmd)
{
	switch (cmd)
	{
	#include CMDS_FILE
	default:
		return -1;
		break;
	}
}

#undef  ADD_CMD
#define ADD_CMD(_cmd) \
	case _cmd: \
		return (char*)#_cmd;\
		break;

char* bc_cmd_name(int cmd)
{
	switch (cmd)
	{
	#include CMDS_FILE
	default:
		return (char*)"---- NO CMD FOUND ----";
		break;
	}
}

#undef  ADD_CMD
#define ADD_CMD(_cmd) \
	cmds[i].cmd = _cmd; \
	cmds[i].name = #_cmd; \
	cmds[i].xcount = 0; \
	i++;

void bc_init_cmds(struct cmd_stream* stream)
{
	command *cmds = stream->cmds;
	if (cmds)
	{
		int i = 0;
		#include CMDS_FILE
	}
}