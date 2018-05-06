#ifndef __BC_TRACKER__
#define __BC_TRACKER__

#include "../src/bc_os_headers.h"
#include "../src/bc_list.h"

#define TRACKER_LINE_SIZE 1
#define TRACKER_NAME_SIZE 20

enum tracker_use {
	DONT_USE_TRACKER,
	USE_TRACKER,
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
	int use;
	char* name;
	char* mblock;
	int size;
	list_node mblocks;
	list_node node;
} tracker;

list_node trackers;

#define can_we_use(_tracker) (_tracker->use)

void bc_init_tracker(void);
void bc_deinit_tracker(void);

void bc_deallocate_mblock(tracker_mblock* mblock);
void bc_release_tracker(tracker* t);

void bc_enable_tracker(tracker *t);
void bc_disable_tracker(tracker *t);

tracker* bc_allocate_tracker(char* tracker_name);
int      bc_update_tracker(tracker_mblock *mblock,
							int line, const char *fmt, ...);
void     bc_deallocate_tracker(tracker *t);

tracker_mblock* bc_allocate_mblock(tracker *t, int lines);
tracker* bc_get_tracker(char* tracker_name);
tracker* bc_new_tracker(char* tname, int size);

enum tracker_ids {
	TRACKER1_ID,
	TRACKER2_ID,
	TRACKER3_ID,
	TRACKERS,
};

#include "../src/bc_heap_internal.h"
#include "../src/bc_cmd_tracker.h"

#define TRACKER1_NAME "bc_heap"
#define TRACKER2_NAME "bc_cmds"
#define TRACKER3_NAME "bc_stream"

#define TRACKER1_SIZE 100
#define TRACKER2_SIZE (BC_CMDS_COUNT * sizeof(command))
#define TRACKER3_SIZE 100
#define TRACKER_TOTAL_SIZE (TRACKER1_SIZE + TRACKER2_SIZE + TRACKER3_SIZE)

#define TRACKER1_OFFSET (0)
#define TRACKER2_OFFSET (TRACKER1_OFFSET + TRACKER1_SIZE)
#define TRACKER3_OFFSET (TRACKER2_OFFSET + TRACKER2_SIZE)

void bc_setup_headers(struct tracker_meta_header *header,
						struct tracker_header *theaders);
void bc_setup_trackers(void);
int  bc_load_trackers(void);

tracker* bc_get_tracker_by_id(int id);
tracker* bc_get_tracker_by_name(char* name);
int bc_load_trackers_from_data(char* data, int size);

#endif /* __BC_TRACKER__ */