#if 0
#include "bc_stack_dumpper.h"

int
	__NO_TRACKING__
	bc_print_stackdump(const char *fmt, ...)
{
	char log[LOG_BUFFER_LENGTH];
	va_list args;
	int len;

	va_start(args, fmt);
	len = vsnprintf(log, LOG_BUFFER_LENGTH, fmt, args);
	va_end(args);

	return write(bc_stack_dumpper_fd, log, len);
}

void
	__NO_TRACKING__
	bc_update_stack_dumpper()
{

}

bt_accessor_t acc;

void
	__NO_TRACKING__
	bc_init_backtrace()
{
	bt_init_accessor( &acc, BT_SELF);
}

void
	__NO_TRACKING__
	bc_init_stack_dumpper()
{
	if ((bc_stack_dumpper_fd = shm_open(STACK_DUMPPER, O_RDWR | O_CREAT, 0666)) < 0)
		return;

	// bc_init_backtrace();	
}

void
	__NO_TRACKING__
	bc_deinit_stack_dumpper()
{
	if (bc_stack_dumpper_fd)
		close(bc_stack_dumpper_fd);
}

#endif
