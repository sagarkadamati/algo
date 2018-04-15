#ifndef __BC_FUNCTION_TRACKER__
#define __BC_FUNCTION_TRACKER__

#include"bc_os_headers.h"

#define LOG_BUFFER_LENGTH   100
#define FUNCTION_TRACKER    "bc_function"

int bc_function_tracker_fd;
void* bc_function_tracker_data;

void bc_init_function_tracer(void);
void bc_deinit_function_tracer(void);
int  bc_print_functions(const char *fmt, ...);

void __cyg_profile_func_enter(void *func, void *caller);
void __cyg_profile_func_exit(void *func, void *caller);

#endif /* __BC_FUNCTION_TRACER__ */