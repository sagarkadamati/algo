#include "bc_function_tracer.h"

void bc_init_function_tracer(void)
{
}

void
	__attribute__((__no_instrument_function__))
	__cyg_profile_func_enter(void *func, void *caller)
{
}

void
	__attribute__((__no_instrument_function__))
	__cyg_profile_func_exit(void *func, void *caller)
{
}
