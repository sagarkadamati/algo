#ifndef __BC_CMD_FACTORY__
#define __BC_CMD_FACTORY__

#include "bc_cmd_tracker.h"

#define CMDS_FILE "bc_cmds.h"
#define ADD_CMD(_cmd) BC_##_cmd,

enum commands {
	#include CMDS_FILE
	BC_CMDS_COUNT
};

int bc_cmd_index(int cmd);
char* bc_cmd_name(int cmd);
void bc_init_cmds(struct cmd_struct *cmds);

#endif  /* __BC_CMD_FACTORY__ */
