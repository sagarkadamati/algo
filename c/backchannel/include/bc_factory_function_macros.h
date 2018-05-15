#ifndef __BC_FACTORY_FUNCTION_MACROS__
#define __BC_FACTORY_FUNCTION_MACROS__

#include "bc_cmd_tracker.h"

#define CMD_ENUM(_cmd)		BC_##_cmd,

#define CMD_INDEX(_cmd)								\
	case _cmd:										\
		return BC_##_cmd;							\
		break;

#define CMD_NAME(_cmd)								\
	case _cmd:										\
		return (char*)#_cmd;						\
		break;

#define CMD_INIT(_cmd)								\
	cmds[i].cmd = _cmd;								\
	cmds[i].name = #_cmd;							\
	cmds[i].xcount = 0;								\
	i++;

#define BEGIN_CMDS_FUNC(_name)						\
	void bc_init_##_name(struct cmd_stream* stream)	\
	{												\
		command *cmds = stream->cmds;				\
		if (cmds)									\
		{											\
			int i = 0;

#define END_CMDS_FUNC(_name)						\
		}											\
	}

#define BEGIN_INDEX_FUNC(_name) 					\
	int bc_##_name##_index(int cmd)					\
	{												\
		switch (cmd)								\
		{

#define END_INDEX_FUNC(_name)						\
			default:								\
				return -1;							\
				break;								\
		}											\
	}

#define BEGIN_NAME_FUNC(_cmd_name)					\
	char* bc_##_cmd_name##_name(int cmd)			\
	{												\
		switch (cmd)								\
		{

#define END_NAME_FUNC(_name)						\
		default:									\
			return (char*)"---- NO CMD FOUND ----";	\
			break;									\
		}											\
	}

#endif /* __BC_FACTORY_FUNCTION_MACROS__ */