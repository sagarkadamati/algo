#ifndef __BC_TRACKER_INTERNAL__
#define __BC_TRACKER_INTERNAL__

#include <bc_os_headers.h>

struct tracker_meta_header {
	int size;
	int tcount;
	int t_hoffset;
	int t_doffset;
};

#define TRACKER_NAME_SIZE 20
struct tracker_header {
	char name[TRACKER_NAME_SIZE];
	int id;
	int offset;
	int size;
	int use;
	int soffset;
	int scount;
};

struct mblock_struct {
	char* mmap;
	int size;
};

#define TRACKER_LINE_SIZE 1
typedef struct struct_tracker_mblock {
	char* mmap;
	int mmap_size;
	int lines;
	list_node node;
} tracker_mblock;

struct tracker_struct {
	struct tracker_meta_header* header;
	struct tracker_header* theaders;
	struct mblock_struct mblock;
} new_trackers;

void bc_init_tracker(void);
void bc_deinit_tracker(void);

void bc_deallocate_mblock(tracker_mblock* mblock);
void bc_release_tracker(tracker* t);

tracker_mblock* bc_allocate_mblock(tracker *t, int lines);
tracker* bc_get_tracker(char* tracker_name);

int      bc_update_tracker(tracker_mblock *mblock,
							int line, const char *fmt, ...);

#endif /* __BC_TRACKER_INTERNAL__ */
