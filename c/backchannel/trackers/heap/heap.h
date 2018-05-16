#ifndef __BC_HEAP_TRACKER__
#define __BC_HEAP_TRACKER__

#include <bc_os_headers.h>
#include <bc_tracker.h>

#include "tracker.h"
#include "heap_internal.h"

enum HEAP_STATE {
	MALLOC,
	CALLOC,
	FREE,
	DOUBLE_FREE
};

struct location {
	char func[80];
	int line;
};

typedef struct heap_status {
	uint32_t msize;
	uint32_t mfree;
	uint32_t csize;
	uint32_t cfree;

	uint32_t mcount_alloc;
	uint32_t mcount_free;
	uint32_t ccount_alloc;
	uint32_t ccount_free;

	uint32_t dfree;

	int blocks_size;
	int blocks_used;

	list_node free_blocks;
} __attribute__ ((packed)) heap_status;

typedef struct heap_block {
	void* ptr;
	enum HEAP_STATE state;
	int size;
	list_node hblock;

	const char* func;
	int line;

	struct location alloc_at;
	struct location free_at;
	struct location double_free_at;
} __attribute__ ((packed)) heap_block;

void bc_init_heap_tracker(void);
void bc_deinit_heap_tracker(void);

void bc_malloc_probe_pt(void *ptr, int size, const char *func, int line);
void bc_calloc_probe_pt(void *ptr, int size, const char *func, int line);
void bc_free_probe_pt(void *ptr, const char *func, int line);

heap_block* new_heap_block(void);
heap_block* get_heap_block(void* ptr);
void release_heap_block(heap_block* block);

enum HEAP_STREAMS {
	BC_HEAP_STATUS_STREAM,
	BC_HEAP_BLOCKS_STREAM,
	BC_HEAP_STREAM_COUNT,
};

#define BC_HEAP_STATUS_STREAM_OBJ_SIZE		sizeof(heap_status)
#define BC_HEAP_STATUS_STREAM_OBJ_COUNT		1

#define BC_HEAP_BLOCKS_STREAM_OBJ_SIZE		sizeof(heap_block)
#define BC_HEAP_BLOCKS_STREAM_OBJ_COUNT		1000

#define MAX_HEAP_BLOCKS						BC_HEAP_BLOCKS_STREAM_OBJ_COUNT

#define HEAP_TRACKER_NAME					"Heap"
#define HEAP_TRACKER_SIZE					((BC_HEAP_STATUS_STREAM_OBJ_SIZE *		\
												BC_HEAP_STATUS_STREAM_OBJ_COUNT) +	\
											 (BC_HEAP_BLOCKS_STREAM_OBJ_SIZE *		\
												BC_HEAP_BLOCKS_STREAM_OBJ_COUNT))

#endif /* __BC_HEAP_TRACKER__ */
