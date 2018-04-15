#ifndef __TRACE__
#define __TRACE__

#include "bc_os_headers.h"

#define LOG_BUFFER_LENGTH   100
#define FUNCTION_TRACKER        "bc_function"

int bc_function_tracker_fd;
void* bc_function_tracker_data;

void bc_init_function_tracer(void);
void __cyg_profile_func_enter(void *func, void *caller);
void __cyg_profile_func_exit(void *func, void *caller);

#endif /* __TRACE__ */