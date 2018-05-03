#include "bc_init.h"

void
	__attribute__((constructor))
	bc_init(void)
{
	bc_init_tracker();

	bc_init_heap_tracker();
	bc_init_cmd_tracker();
	bc_init_stream_tracker();
	// bc_init_function_tracker();
}

void
	__attribute__((destructor))
	bc_deinit(void)
{
	// bc_deinit_function_tracker();
	bc_deinit_stream_tracker();
	bc_deinit_cmd_tracker();
	bc_deinit_heap_tracker();

	bc_deinit_tracker();
}