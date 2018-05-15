#ifndef __BC_stack_dumpper__
#define __BC_stack_dumpper__

#include "bc_os_headers.h"

#define LOG_BUFFER_LENGTH   100
#define STACK_DUMPPER       "bc_stack_dump"

int bc_stack_dumpper_fd;
void* bc_stack_dumpper_data;

void bc_init_stack_dumpper(void);
void bc_init_backtrace(void);
void bc_deinit_stack_dumpper(void);
void bc_update_stack_dumpper(void);
int  bc_print_stackdump(const char *fmt, ...);

#endif /* __BC_stack_dumpper__ */
