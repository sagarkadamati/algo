#ifndef __BC_CMD__
#define __BC_CMD__

#define DEFINE_CMD_HEADER(_states)			\
	struct command_header {					\
		char name;							\
		int type;							\
		int cmds_stream;					\
		int cmd_names_stream;				\
	} __attribute__ ((packed))

#define DEFINE_CMD(_states)					\
	struct command {						\
		int cmd_id;							\
		int name_id;						\
		int used_count;						\
		int status;							\
		int cur_state;						\
		int max_states;						\
		int ftracer_cond;					\
		struct timespec timespec[_states];	\
	} __attribute__ ((packed))

#ifndef /* __BC_CMD__ */
