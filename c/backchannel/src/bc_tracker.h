#ifndef __BC_TRACKER__
#define __BC_TRACKER__

#include "bc_os_headers.h"
#include "bc_heap_internal.h"
#include "bc_list.h"

#define TRACKER_LINE_SIZE 1

typedef struct struct_tracker_mblock {
	char* mmap;
	int mmap_size;
	int lines;
	list_node node;
} tracker_mblock;

typedef struct struct_tracker {
	int fd;
	char* name;
	int size;
	list_node mblocks;
	list_node node;
} tracker;

list_node trackers;

void bc_init_tracker(void);
void bc_deinit_tracker(void);
tracker* bc_allocate_tracker(char* tracker_name);
tracker_mblock* bc_allocate_mblock(tracker *t, int lines);
void bc_deallocate_tracker(tracker *t);
void bc_deallocate_mblock(tracker_mblock* mblock);
int bc_update_tracker(tracker_mblock *mblock, int line, const char *fmt, ...);
tracker* bc_get_tracker(char* tracker_name);

#endif /* __BC_TRACKER__ */