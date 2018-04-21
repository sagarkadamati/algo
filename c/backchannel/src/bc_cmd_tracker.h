#ifndef __BC_CMD_TRACKER__
#define __BC_CMD_TRACKER__

#include "bc_os_headers.h"
#include "bc_tracker.h"
#include "bc_time.h"

#define CMD_TRACKER       "bc_cmds"

#define CMD1 1
#define CMD2 2
#define CMD3 3
#define CMD4 4
#define CMD5 5

typedef struct cmd_struct {
	int id;
	char* name;
	long int xcount;
	int enable;
	struct timespec tenter;
	struct timespec texit;
	struct timespec tavg;
	int status;
} cmd_struct;

struct cmd_stream {
	tracker *tracker;
	cmd_struct *cmds;
	list_node head;
} cmd_stream;

void bc_init_cmd_tracker(void);
void bc_deinit_cmd_tracker(void);
void bc_update_cmd_data(int index);
void bc_update_cmd(enum position pos, int cmd, int status);
void bc_update_cmd_tracker_header(void);
int bc_get_cmd_num(int cmd);
char* bc_get_cmd_name(int cmd);
void bc_init_cmds(struct cmd_struct *cmds);

void bc_print_cmds(int index, const char *fmt, ...);
void bc_add_cmds(void);
void bc_deallocate_cmds(void);
int get_cmds_count(void);
void* bc_allocate_cmds(void);
// void bc_update_cmds(enum position pos, int cmd);

int bc_cmd_index(int cmd);
char* bc_cmd_name(int cmd);

#endif /* __BC_CMD_TRACKER__ */
