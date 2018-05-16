#include "heap.h"

struct bc_struct_heap_tracker heap_tracker_cbs;

struct heap_tracker_struct {
	tracker *tracker;
	int enable;

	list_node hblocks;
	heap_header *header;
	heap_block *alloc_ptr;
} heap_tracker;

heap_block* new_heap_block()
{
	if (heap_tracker.header->blocks_size != heap_tracker.header->blocks_used)
	{
		heap_block* block = &heap_tracker.alloc_ptr[heap_tracker.header->blocks_used++];
		list_add(&heap_tracker.hblocks, &block->hblock);
		return block;
	}
	else
	{
		if (&heap_tracker.header->free_blocks)
		{
			list_node *node = heap_tracker.header->free_blocks.next;
			if (&heap_tracker.header->free_blocks != node)
			{
				heap_block* block = container_of(node, heap_block, hblock);

				list_remove(&block->hblock);
				list_add(&heap_tracker.hblocks, &block->hblock);
				return block;
			}
		}
	}
	return NULL;
}

void release_heap_block(heap_block* block)
{
	if (block) {
		list_remove(&block->hblock);
		list_add(&heap_tracker.header->free_blocks, &block->hblock);
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
	if (heap_tracker.enable) {
		heap_block *block = new_heap_block();
		if (block) {
			heap_tracker.header->msize += size;
			heap_tracker.header->mcount_alloc++;

			block->state = MALLOC;
			block->ptr   = ptr;
			block->size  = size;
			strcpy(block->alloc_at.func, func);
			block->alloc_at.line  = line;
		}
	}
}

void bc_calloc_probe_pt(void *ptr, int size, const char *func, int line)
{
	if (heap_tracker.enable) {
		heap_block *block = new_heap_block();
		if (block) {
			heap_tracker.header->csize += size;
			heap_tracker.header->ccount_alloc++;

			block->state = CALLOC;
			block->ptr   = ptr;
			block->size  = size;
			strcpy(block->alloc_at.func, func);
			block->alloc_at.line  = line;
		}
	}
}

void bc_free_probe_pt(void *ptr, const char *func, int line)
{
	if (heap_tracker.enable) {
		heap_block *block = get_heap_block(ptr);
		if(block)
		{
			switch(block->state)
			{
				case MALLOC:
					heap_tracker.header->mfree += block->size;
					heap_tracker.header->mcount_free++;

					block->state = FREE;
					strcpy(block->free_at.func, func);
					block->free_at.line  = line;

					break;
				case CALLOC:
					heap_tracker.header->cfree += block->size;
					heap_tracker.header->ccount_free++;

					block->state = FREE;
					strcpy(block->free_at.func, func);
					block->free_at.line  = line;

					break;
				case FREE:
				case DOUBLE_FREE:
					heap_tracker.header->dfree++;
					strcpy(block->double_free_at.func, func);
					block->double_free_at.line  = line;
			}

			release_heap_block(block);
		}
	}
}

static void setup_heap_data(void)
{
	list_init(&heap_tracker.hblocks);
	list_init(&heap_tracker.header->free_blocks);

	heap_tracker_cbs.malloc = bc_malloc_probe_pt;
	heap_tracker_cbs.calloc = bc_calloc_probe_pt;
	heap_tracker_cbs.free   = bc_free_probe_pt;
}

void bc_init_heap_tracker()
{
	heap_tracker.tracker	= bc_get_tracker_by_id(HEAP_TRACKER_ID);

	heap_tracker.header		= (heap_header*) heap_tracker.tracker->mblock;
	heap_tracker.header->blocks_size = MAX_HEAP_BLOCKS;
	heap_tracker.header->blocks_used = 0;

	heap_tracker.header->msize = 0;
	heap_tracker.header->mfree = 0;
	heap_tracker.header->mcount_alloc = 0;
	heap_tracker.header->mcount_free = 0;
	heap_tracker.header->csize = 0;
	heap_tracker.header->cfree = 0;
	heap_tracker.header->ccount_alloc = 0;
	heap_tracker.header->ccount_free = 0;
	heap_tracker.header->dfree = 0;

	heap_tracker.alloc_ptr	= (heap_block*)
				 (heap_tracker.tracker->mblock + sizeof(heap_header));

	setup_heap_data();
	heap_tracker_cbs.enable = 1;
	heap_tracker.enable = 1;
}

void bc_deinit_heap_tracker()
{
	bc_deallocate_tracker(heap_tracker.tracker);
}
