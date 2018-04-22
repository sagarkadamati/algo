#ifndef __BC_HEAP_TRACKER__
#define __BC_HEAP_TRACKER__

#include "bc_os_headers.h"
#include "bc_tracker.h"

#define HEAP_TRACKER        "bc_heap"
#define HEAP_SIZE           3

enum alloc_type {
	MALLOC,
	CALLOC,
};

typedef struct heap_block {
	void* ptr;
	const char* func;
	int line;
	int size;
	enum alloc_type type;
	list_node hblock;
} heap_block;

struct heap_tracker_struct {
	tracker *tracker;
	tracker_mblock *mblock;
	struct bc_struct_heap_tracker *cbs;

	list_node hblocks;
	int msize;
	int mfree;
	int csize;
	int cfree;

} heap_tracker;

void bc_init_heap_tracker(void);
void bc_deinit_heap_tracker(void);
void bc_malloc_probe_pt(void *ptr, int size, const char *func, int line);
void bc_calloc_probe_pt(void *ptr, int size, const char *func, int line);
void bc_free_probe_pt(void *ptr, const char *func, int line);

#endif /* __BC_HEAP_TRACKER__ */