#ifndef __BC_CMD_FACTORY__
#define __BC_CMD_FACTORY__

#include "bc_cmd_tracker.h"

#define ADD_CMD(_cmd) BC_##_cmd,

enum commands {
	#include CMDS_FILE
	BC_CMDS_COUNT
};

int bc_cmd_index(int cmd);
char* bc_cmd_name(int cmd);

#endif  /* __BC_CMD_FACTORY__ */
