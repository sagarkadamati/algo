#ifndef __BC_CMD__
#define __BC_CMD__

#include <bc_os_headers.h>
#include <bc_tracker.h>

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

enum states {
	STATE1,
	STATE2,
	STATES_COUNT,
};

#define CMD_NAME_SIZE		100
typedef struct command {
	char* name;
	char new_name[CMD_NAME_SIZE];
	int cmd;
	int enable;
	int status;
	int xcount;
	int state;
	int cur_state;
	unsigned int max_states;
	int ftracer_cond;
	struct timespec timespec[STATES_COUNT];

	struct timespec tenter;
	struct timespec texit;

	struct timespec tmin;
	struct timespec tavg;
	struct timespec tmax;
}  __attribute__ ((packed)) command;

struct cmd_stream {
	tracker *tracker;
	command *cmds;

	list_node head;
} cmd_stream;

#endif /* __BC_CMD__ */
