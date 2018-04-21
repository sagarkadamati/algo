#ifndef __BC_CMD_FACTORY__
#define __BC_CMD_FACTORY__

#define ADD_CMD(_cmd) BC_##_cmd,

enum commands {
	#include "bc_cmds.h"
	BC_CMDS_COUNT
};

#undef  ADD_CMD
#define ADD_CMD(_cmd) \
	case _cmd: \
		return BC_##_cmd;\
		break;

int bc_cmd_index(int cmd)
{
	switch (cmd)
	{
	#include "bc_cmds.h"
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
	#include "bc_cmds.h"
	default:
		return (char*)"---- NO CMD FOUND ----";
		break;
	}
}

#undef  ADD_CMD
#define ADD_CMD(_cmd) \
	cmds[i].id = _cmd; \
	cmds[i].name = #_cmd; \
	cmds[i].xcount = 0; \
	i++;

void bc_init_cmds(struct cmd_struct *cmds)
{
	int i = 0;

	#include "bc_cmds.h"
}

#endif  /* __BC_CMD_FACTORY__ */
