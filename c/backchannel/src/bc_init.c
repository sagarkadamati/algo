#include "bc_init.h"

void
	__attribute__((constructor))
	bc_init(void)
{
	printf("Initialization\n");

	bc_init_heap_tracker();
	bc_init_ioctl_tracker();
	bc_init_function_tracer();
}

void
	__attribute__((destructor))
	bc_deinit(void)
{
	printf("De-Initialization\n");

	bc_deinit_heap_tracker();
	bc_deinit_ioctl_tracker();
	bc_deinit_function_tracer();
}