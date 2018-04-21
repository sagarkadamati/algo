#ifndef __BC_TRACKER__
#define __BC_TRACKER__

#include "bc_os_headers.h"
#include "bc_list.h"

#define TRACKER_LINE_SIZE 100

typedef struct struct_tracker {
	int fd;
	char* mmap;
	int mmap_size;
	int lines;
	list_node head;
} tracker;

list_node trackers;

void bc_init_tracker();
void bc_deinit_tracker();
tracker* bc_allocate_tracker(char* tracker_name, int lines);
void bc_deallocate_tracker(tracker *t);
int bc_update_tracker(tracker *t, int line, const char *fmt, ...);

#endif /* __BC_TRACKER__ */