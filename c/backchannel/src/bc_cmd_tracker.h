#ifndef __BC_CMD_TRACKER__
#define __BC_CMD_TRACKER__

#include "bc_os_headers.h"
#include "bc_tracker.h"
#include "bc_trackers_reg.h"
#include "bc_time.h"

#define CMD_NAME_SIZE		100
#define CMDS_SIZE			BC_CMDS_COUNT

enum states {
	STATE1,
	STATE2,
	STATES_COUNT,
};

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
	struct timespec tavg;
}  __attribute__ ((packed)) command;

struct cmd_stream {
	tracker *tracker;
	command *cmds;

	list_node head;
} cmd_stream;

void bc_init_cmd_tracker(void);
void bc_deinit_cmd_tracker(void);

void bc_allocate_cmds(struct cmd_stream* stream, int size);
void bc_deallocate_cmds(struct cmd_stream* stream);

void bc_update_cmd_tracker_header(void);
void bc_update_cmd(int cmd, enum states state, int status);
void bc_update_cmd_internal(struct cmd_stream *stream, enum states state, int cmd, int status);

#define CMD_TRACKER_NAME	"cmds_tracker"
#define CMD_TRACKER_SIZE	(CMDS_SIZE * sizeof(command))

#endif /* __BC_CMD_TRACKER__ */
