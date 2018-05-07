
#ifndef __BC_CMD_FACTORY__
#define __BC_CMD_FACTORY__

#include "bc_factory_header_macros.h"
#include "bc_factory_function_macros.h"

#define CMDS_LIST "bc_cmds_list.h"

DEFINE_ENUM(CMDS)
	#include CMDS_LIST
END_ENUM(CMDS)

DEFINE_PROTOTYPES(cmd)

#endif  /* __BC_CMD_FACTORY__ */
