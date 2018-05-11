#ifndef __BC_IOCTL_TRACKER__
#define __BC_IOCTL_TRACKER__

#include "bc_os_headers.h"

#include "bc_tracker.h"

#define IOCTL_SIZE 100

#define DEFINE_IOCTL(_ioctl) \
	case _ioctl: \
		return (char*) #_ioctl;\
		break;

#define ADD_IOCTL(_ioctl) \
	bc_ioctls[i].id = _ioctl; \
	bc_ioctls[i].name = #_ioctl; \
	bc_ioctls[i].exe_count = 0; \
	i++;

#define DEF_IOCTL(_ioctl) \
	case _ioctl: \
		return (char*) #_ioctl;\
		break;

#define COUNT_IOCTL(_ioctl) ioctl_count++;

#define LOG_BUFFER_LENGTH   100
#define IOCTL_TRACKER       "bc_ioctl"

tracker *ioctl_tracker;

long int enter_ns;

struct bc_ioctl_struct {
	int id;
	char* name;
	long int exe_count;
	int enable;
	struct timespec tenter;
	struct timespec texit;
	struct timespec tavg;
	int status;
} *bc_ioctls;

void bc_init_ioctl_tracker(void);
void bc_deinit_ioctl_tracker(void);
// void bc_update_ioctls(enum position pos, int cmd);
void bc_update_ioctls(enum position pos, int cmd, int status);
void  bc_print_ioctls(int index, const char *fmt, ...);
char* bc_get_ioctl_name(int cmd);
void bc_add_ioctls(void);
int get_ioctls_count(void);
int bc_get_ioctl_num(int cmd);
void bc_update_ioctl(int index);
void bc_update_tracker_header(void);
void* bc_allocate_ioctls(void);
void bc_deallocate_ioctls(void);

#endif /* __BC_IOCTL_TRACKER__ */
