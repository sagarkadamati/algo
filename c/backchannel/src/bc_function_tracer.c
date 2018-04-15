#include "bc_function_tracer.h"

int
	__NO_TRACKING__
	bc_print_functions(const char *fmt, ...)
{
	char log[LOG_BUFFER_LENGTH];
	va_list args;
	int len;

	va_start(args, fmt);
	len = vsnprintf(log, LOG_BUFFER_LENGTH, fmt, args);
	va_end(args);

	return write(bc_function_tracker_fd, log, len);
}

void
	__NO_TRACKING__
	bc_update_functions(enum position pos, void *func, void *caller)
{
	long int ns;
	struct timespec spec;

	clock_gettime(CLOCK_REALTIME, &spec);
	ns = spec.tv_nsec;

	switch(pos)
	{
		case ENTER:
			bc_print_functions("| %-50s | %-5s | %lu |\n",
				func, pos ? "EXIT" : "ENTER", ns / 1000000);
			break;
		case EXIT:
			bc_print_functions("| %-50s | %-5s | %lu |\n",
				func, pos ? "EXIT" : "ENTER", ns / 1000000);
			break;
	}
}

void
	__NO_TRACKING__
	__cyg_profile_func_exit(void *func, void *caller)
{
	bc_update_functions(EXIT, func, caller);
}

void
	__NO_TRACKING__
	__cyg_profile_func_enter(void *func, void *caller)
{
	bc_update_functions(ENTER, func, caller);
}

void
	__NO_TRACKING__
	bc_init_function_tracer(void)
{
	if ((bc_function_tracker_fd = shm_open(FUNCTION_TRACKER, O_RDWR | O_CREAT, 0666)) < 0)
		return;
}

void
	__NO_TRACKING__
	bc_deinit_function_tracer(void)
{
	if (bc_function_tracker_fd)
		close(bc_function_tracker_fd);
}