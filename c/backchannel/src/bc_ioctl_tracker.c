#include "bc_ioctl_tracker.h"

int
	__NO_TRACKING__
	bc_print_ioctls(const char *fmt, ...)
{
	char log[LOG_BUFFER_LENGTH];
	va_list args;
	int len;

	va_start(args, fmt);
	len = vsnprintf(log, LOG_BUFFER_LENGTH, fmt, args);
	va_end(args);

	return write(bc_ioctl_tracker_fd, log, len);
}

void
	__NO_TRACKING__
	bc_update_ioctls(enum position pos, int cmd)
{
	long int ns;
	struct timespec spec;
	char* ioctl_cmd;

#ifdef __BC_PROCESS_HEADERS__
	ioctl_cmd = bc_get_ioctl_name(cmd);
#else
	ioctl_cmd = (char*)"=== PROCESS HEADERS NOT DEFINED ===";
#endif /* __BC_PROCESS_HEADERS__ */

	clock_gettime(CLOCK_REALTIME, &spec);
	ns = spec.tv_nsec;

	switch(pos)
	{
		case ENTER:
			bc_print_ioctls("| %-50s | %-5s | %lu |\n",
				ioctl_cmd, pos ? "EXIT" : "ENTER", 0);
				enter_ns = ns;
			break;
		case EXIT:
			ns -= enter_ns;
			bc_print_ioctls("| %-50s | %-5s | %lu |\n",
				ioctl_cmd, pos ? "EXIT" : "ENTER", ns / 1000000);
			break;
	}
}

void
	__NO_TRACKING__
	bc_init_ioctl_tracker()
{
	if ((bc_ioctl_tracker_fd = shm_open(IOCTL_TRACKER, O_RDWR | O_CREAT, 0666)) < 0)
		return;

	printf("DEBUG: IOCTL tracer enabled\n");
}

void
	__NO_TRACKING__
	bc_deinit_ioctl_tracker()
{
	if (bc_ioctl_tracker_fd)
		close(bc_ioctl_tracker_fd);
}