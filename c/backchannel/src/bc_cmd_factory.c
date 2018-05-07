#include "bc_cmds.h"
#include "bc_cmd_factory.h"

#undef  ADD_CMD
#define ADD_CMD CMD_INDEX
BEGIN_INDEX_FUNC(cmd)
	#include CMDS_LIST
END_INDEX_FUNC(cmd)

#undef  ADD_CMD
#define ADD_CMD CMD_NAME
BEGIN_NAME_FUNC(cmd)
	#include CMDS_LIST
END_NAME_FUNC(cmd)

#undef  ADD_CMD
#define ADD_CMD CMD_INIT
BEGIN_CMDS_FUNC(cmd)
	#include CMDS_LIST
END_CMDS_FUNC(cmd)