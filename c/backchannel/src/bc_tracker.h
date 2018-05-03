#ifndef __BC_TRACKER__
#define __BC_TRACKER__

#include "bc_os_headers.h"
#include "bc_heap_internal.h"
#include "bc_list.h"

#define TRACKER_LINE_SIZE 1

#define TRACKER_NAME_SIZE 20

enum tracker_use {
	TRACKER_DONT_USE,
	TRACKER_USE,
};

enum tracker_ids {
	TRACKER1_ID,
	TRACKER2_ID,
	TRACKER3_ID,
	TRACKERS,
};

struct tracker_meta_header {
	int size;
	int tcount;
	int t_hoffset;
	int t_doffset;
};

struct tracker_header {
	char name[TRACKER_NAME_SIZE];
	int id;
	int offset;
	int size;
	int use;
};

struct mblock_struct {
	char* mmap;
	int size;
};

struct tracker_struct {
	struct tracker_meta_header* header;
	struct tracker_header* theaders;
	struct mblock_struct mblock;
} new_trackers;

typedef struct struct_tracker_mblock {
	char* mmap;
	int mmap_size;
	int lines;
	list_node node;
} tracker_mblock;

typedef struct struct_tracker {
	int fd;
	int id;
	char* name;
	char* mblock;
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
tracker* bc_new_tracker(char* tname, int size);
void bc_release_tracker(tracker* t);

#define TRACKER1_NAME "bc_tracker1"
#define TRACKER2_NAME "bc_tracker2"
#define TRACKER3_NAME "bc_tracker3"

#define TRACKER1_SIZE 100
#define TRACKER2_SIZE 100
#define TRACKER3_SIZE 100
#define TRACKER_TOTAL_SIZE (TRACKER1_SIZE + TRACKER2_SIZE + TRACKER3_SIZE)

#define TRACKER1_OFFSET (0)
#define TRACKER2_OFFSET (TRACKER1_OFFSET + TRACKER1_SIZE)
#define TRACKER3_OFFSET (TRACKER2_OFFSET + TRACKER2_SIZE)

void bc_setup_tracker(void);
int bc_load_tracker(void);

#endif /* __BC_TRACKER__ */