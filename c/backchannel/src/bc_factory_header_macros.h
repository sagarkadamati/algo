#ifndef __BC_FACTORY_HEADER_MACROS__
#define __BC_FACTORY_HEADER_MACROS__

#define DEFINE_ENUM(_name)							\
	enum _name##_enum {

#define END_ENUM(_name)	BC_##_name##_COUNT };
#define CMD_ENUM(_cmd)		BC_##_cmd,

#define DEFINE_PROTOTYPES(_func_name)				\
	int bc_##_func_name##_index(int cmd);			\
	char* bc_##_func_name##_name(int cmd);

#undef  ADD_CMD
#define ADD_CMD	CMD_ENUM

#endif /* __BC_FACTORY_HEADER_MACROS__ */