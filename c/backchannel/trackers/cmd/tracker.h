#ifndef __BC_CMD_TRACKER__
#define __BC_CMD_TRACKER__

#include <bc_os_headers.h>
#include <bc_tracker.h>
#include <bc_time.h>

#define CMDS_SIZE			BC_CMDS_COUNT

#include <bc_cmd.h>

void bc_init_cmd_tracker(void);
void bc_deinit_cmd_tracker(void);

void bc_allocate_cmds(struct cmd_stream* stream, int size);
void bc_deallocate_cmds(struct cmd_stream* stream);

void bc_update_cmd_tracker_header(void);
void bc_update_cmd(int cmd, enum states state, int status);
void bc_update_cmd_internal(struct cmd_stream *stream, enum states state, int cmd, int status);

#define CMD_TRACKER_NAME	"Command"
#define CMD_TRACKER_SIZE	(CMDS_SIZE * sizeof(command))

#endif /* __BC_CMD_TRACKER__ */
