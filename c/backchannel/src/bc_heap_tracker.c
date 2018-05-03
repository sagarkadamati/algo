#include "bc_heap_tracker.h"

heap_block* new_heap_block()
{
	heap_block* block = malloc(sizeof(heap_block));
	if (block) {
		list_add(&heap_tracker.hblocks, &block->hblock);
		return block;
	}
	return NULL;
}

void release_heap_block(heap_block* block)
{
	if (block) {
		// list_remove(&block->hblock);
		// free(block);
	}
}

heap_block* get_heap_block(void* ptr)
{
	heap_block *block = NULL;

	list_node *head = &heap_tracker.hblocks;
	list_node *node = head->next;

	while (node != head)
	{
		block = container_of(node, heap_block, hblock);
		if (block->ptr == ptr)
			return block;

		node = node->next;
	}
	return NULL;
}

void bc_malloc_probe_pt(void *ptr, int size, const char *func, int line)
{
	heap_block *block = new_heap_block();

	if (block) {
		heap_tracker.status->msize += size;

		block->state = MALLOC;
		block->ptr   = ptr;
		block->size  = size;
		strcpy(block->alloc_at.func, func);
		block->alloc_at.line  = line;
	}
}

void bc_calloc_probe_pt(void *ptr, int size, const char *func, int line)
{
	heap_block *block = new_heap_block();

	if (block) {
		heap_tracker.status->csize += size;

		block->state = CALLOC;
		block->ptr   = ptr;
		block->size  = size;
		strcpy(block->alloc_at.func, func);
		block->alloc_at.line  = line;
	}
}

void bc_free_probe_pt(void *ptr, const char *func, int line)
{
	heap_block *block = get_heap_block(ptr);

	if(!block)
		return;

	switch(block->state)
	{
		case MALLOC:
			heap_tracker.status->mfree += block->size;

			block->state = FREE;
			strcpy(block->free_at.func, func);
			block->free_at.line  = line;

			break;
		case CALLOC:
			heap_tracker.status->cfree += block->size;

			block->state = FREE;
			strcpy(block->free_at.func, func);
			block->free_at.line  = line;

			break;
		case FREE:
		case DOUBLE_FREE:
			strcpy(block->double_free_at.func, func);
			block->double_free_at.line  = line;
	}

	release_heap_block(block);
}

void bc_init_heap_tracker()
{
	heap_tracker.tracker	= bc_new_tracker(HEAP_TRACKER, HEAP_SIZE);
	heap_tracker.status		= (heap_status*) heap_tracker.tracker->mblock;
	heap_tracker.alloc_ptr	= (heap_block*)
				 (heap_tracker.tracker->mblock + sizeof(heap_status));

	list_init(&heap_tracker.hblocks);
	heap_tracker_cbs.malloc = bc_malloc_probe_pt;
	heap_tracker_cbs.calloc = bc_calloc_probe_pt;
	heap_tracker_cbs.free   = bc_free_probe_pt;

	heap_tracker_cbs.enable = 1;
}

void bc_deinit_heap_tracker()
{
	bc_deallocate_tracker(heap_tracker.tracker);
}
