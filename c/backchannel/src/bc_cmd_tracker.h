#ifndef __BC_CMD_TRACKER__
#define __BC_CMD_TRACKER__

#include "bc_os_headers.h"
#include "bc_tracker.h"
#include "bc_time.h"

#define CMDS_FILE "bc_cmds.h"
#include "bc_cmd_factory.h"

#define CMDS_SIZE			BC_CMDS_COUNT

#define CMD_TRACKER_NAME	"bc_cmds"
#define CMD_NAME_SIZE 100

enum states{
	STATE1,
	STATE2,
	STATE3,
	STATE4,
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
	int max_states;
	int ftracer_cond;
	struct timespec timespec[STATES_COUNT];

	struct timespec tenter;
	struct timespec texit;
	struct timespec tavg;
} command;

struct cmd_stream {
	tracker *tracker;
	list_node head;

	command *cmds;
} cmd_stream;

void bc_init_cmd_tracker(void);
void bc_deinit_cmd_tracker(void);
void bc_update_cmd(int cmd, enum states state, int status);
void bc_update_cmd_internal(struct cmd_stream *stream, enum states state, int cmd, int status);
void bc_update_cmd_tracker_header(void);

int bc_get_cmd_num(int cmd);
char* bc_get_cmd_name(int cmd);
void bc_init_cmds(struct cmd_stream* stream);

void bc_print_cmds(int index, const char *fmt, ...);
void bc_add_cmds(void);
void bc_allocate_cmds(struct cmd_stream* stream, int size);
void bc_deallocate_cmds(struct cmd_stream* stream);

#define CMD_TRACKER_SIZE	(100 * (CMDS_SIZE * sizeof(command)))

#endif /* __BC_CMD_TRACKER__ */
