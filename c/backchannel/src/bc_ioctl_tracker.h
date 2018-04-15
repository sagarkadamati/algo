#ifndef __BC_IOCTL_TRACKER__
#define __BC_IOCTL_TRACKER__

#include "bc_os_headers.h"

#define LOG_BUFFER_LENGTH   100
#define IOCTL_TRACKER        "bc_heap"

int bc_ioctl_tracker_fd;
void* bc_ioctl_tracker_data;

enum position{
	ENTER,
	EXIT
};

long int enter_ns;

void bc_init_ioctl_tracker(void);
void bc_update_ioctls(enum position pos, int cmd);
int  bc_print_ioctls(const char *fmt, ...);

#endif /* __BC_IOCTL_TRACKER__ */