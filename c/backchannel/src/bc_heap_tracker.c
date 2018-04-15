#include "bc_heap_tracker.h"

int
	__NO_TRACKING__
	bc_print_allocations(const char *fmt, ...)
{
	char log[LOG_BUFFER_LENGTH];
	va_list args;
	int len;

	va_start(args, fmt);
	len = vsnprintf(log, LOG_BUFFER_LENGTH, fmt, args);
	va_end(args);

	return write(bc_heap_tracker_fd, log, len);
}

void
	__NO_TRACKING__
	bc_update_heap_tracker()
{

}

void
	__NO_TRACKING__
	bc_malloc_probe_pt(void *ptr, const char *func, int line)
{
	bc_print_allocations("| malloc | %-5d | 0x%-10p | %-40s |\n", line, ptr, func);
	bc_update_heap_tracker();
}

void
	__NO_TRACKING__
	bc_calloc_probe_pt(void *ptr, const char *func, int line)
{
	bc_print_allocations("| calloc | %-5d | 0x%-10p | %-40s |\n", line, ptr, func);
	bc_update_heap_tracker();
}

void
	__NO_TRACKING__
	bc_free_probe_pt(void *ptr, const char *func, int line)
{
	bc_print_allocations("| free   | %-5d | 0x%-10p | %-40s |\n", line, ptr, func);
	bc_update_heap_tracker();
}

void
	__NO_TRACKING__
	bc_init_heap_tracker()
{
	if ((bc_heap_tracker_fd = shm_open(HEAP_TRACKER, O_RDWR | O_CREAT, 0666)) < 0)
		return;

	heap_tracker_cbs.malloc = bc_malloc_probe_pt;
	heap_tracker_cbs.calloc = bc_calloc_probe_pt;
	heap_tracker_cbs.free = bc_free_probe_pt;
}

void
	__NO_TRACKING__
	bc_deinit_heap_tracker()
{
	if (bc_heap_tracker_fd)
		close(bc_heap_tracker_fd);
}