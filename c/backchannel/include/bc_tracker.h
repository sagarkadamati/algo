#ifndef __BC_TRACKER__
#define __BC_TRACKER__

#include "bc_os_headers.h"
#include "bc_list.h"

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

int bc_load_trackers(void);
int bc_load_trackers_from_data(char* data, int size);
tracker* bc_get_tracker_by_id(int id);
tracker* bc_get_tracker_by_name(char* tracker_name);
void print_theaders(void);

#endif /* __BC_TRACKER__ */
