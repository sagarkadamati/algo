#ifndef __BC_HEAP_TRACKER__
#define __BC_HEAP_TRACKER__

#include "bc_os_headers.h"
#include "bc_tracker.h"

#define MAX_HEAP_BLOCKS	100

enum state {
	MALLOC,
	CALLOC,
	FREE,
	DOUBLE_FREE
};

struct location {
	char func[50];
	int line;
};

typedef struct heap_block {
	void* ptr;
	enum state state;
	int size;
	list_node hblock;

	const char* func;
	int line;

	struct location alloc_at;
	struct location free_at;
	struct location double_free_at;
} heap_block;

typedef struct heap_status {
	int msize;
	int mfree;
	int csize;
	int cfree;
} heap_status;

struct heap_tracker_struct {
	tracker *tracker;

	list_node hblocks;
	heap_status *status;
	heap_block *alloc_ptr;
} heap_tracker;

void bc_init_heap_tracker(void);
void bc_deinit_heap_tracker(void);
void bc_malloc_probe_pt(void *ptr, int size, const char *func, int line);
void bc_calloc_probe_pt(void *ptr, int size, const char *func, int line);
void bc_free_probe_pt(void *ptr, const char *func, int line);
heap_block* new_heap_block(void);
void release_heap_block(heap_block* block);
heap_block* get_heap_block(void* ptr);

#define HEAP_TRACKER_NAME	"Heap"
#define HEAP_TRACKER_SIZE	(sizeof(heap_status) + \
							(MAX_HEAP_BLOCKS * sizeof(heap_block)))

#endif /* __BC_HEAP_TRACKER__ */
