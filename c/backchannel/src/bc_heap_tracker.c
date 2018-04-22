#include "bc_heap_tracker.h"

void bc_malloc_probe_pt(void *ptr, int size, const char *func, int line)
{
	heap_block *block = malloc(sizeof(heap_block));

	block->type = MALLOC;
	block->ptr  = ptr;
	block->func = func;
	block->line = line;
	block->size = size;

	list_add(&heap_tracker.hblocks, &block->hblock);
	heap_tracker.msize += size;

	bc_update_tracker(heap_tracker.mblock, 0,
					"MALLOC   : %05d : %05d\n",
					heap_tracker.msize, heap_tracker.mfree);

	bc_update_tracker(heap_tracker.mblock, 2,
					"MEM LEAK : %05d\n",
					(heap_tracker.msize + heap_tracker.csize) -
					(heap_tracker.mfree + heap_tracker.cfree));
}

void bc_calloc_probe_pt(void *ptr, int size, const char *func, int line)
{
	heap_block *block = malloc(sizeof(heap_block));

	block->type = CALLOC;
	block->ptr  = ptr;
	block->func = func;
	block->line = line;
	block->size = size;

	list_add_tail(&heap_tracker.hblocks, &block->hblock);
	heap_tracker.csize += size;

	bc_update_tracker(heap_tracker.mblock, 1,
					"CALLOC   : %05d : %05d\n",
					heap_tracker.csize, heap_tracker.cfree);

	bc_update_tracker(heap_tracker.mblock, 2,
					"MEM LEAK : %05d\n",
					(heap_tracker.msize + heap_tracker.csize) -
					(heap_tracker.mfree + heap_tracker.cfree));
}

void bc_free_probe_pt(void *ptr, const char *func, int line)
{
	heap_block *block;
	
	list_node *head = &heap_tracker.hblocks;
	list_node *node = head->next;

	while (node != head)
	{
		block = container_of(node, heap_block, hblock);
		if (block->ptr == ptr) {
			switch(block->type) {
				case MALLOC:
					heap_tracker.mfree += block->size;
					bc_update_tracker(heap_tracker.mblock, 0,
									  "MALLOC   : %05d : %05d\n",
									  heap_tracker.msize, heap_tracker.mfree);
					bc_update_tracker(heap_tracker.mblock, 2,
									  "MEM LEAK : %05d\n",
									  (heap_tracker.msize + heap_tracker.csize) -
									  (heap_tracker.mfree + heap_tracker.cfree));
				case CALLOC:
					heap_tracker.cfree += block->size;
					bc_update_tracker(heap_tracker.mblock, 1,
									  "CALLOC   : %05d : %05d\n",
									  heap_tracker.csize, heap_tracker.cfree);
					bc_update_tracker(heap_tracker.mblock, 2,
									  "MEM LEAK : %05d\n",
									  (heap_tracker.msize + heap_tracker.csize) -
									  (heap_tracker.mfree + heap_tracker.cfree));
					break;
			}

			list_remove(&block->hblock);
			free(block);

			break;
		}

		node = node->next;
	}
}

void bc_init_heap_tracker()
{
	heap_tracker.tracker = bc_allocate_tracker(HEAP_TRACKER);
	heap_tracker.mblock = bc_allocate_mblock(heap_tracker.tracker, HEAP_SIZE);
	heap_tracker.cbs = &heap_tracker_cbs;

	heap_tracker_cbs.malloc = bc_malloc_probe_pt;
	heap_tracker_cbs.calloc = bc_calloc_probe_pt;
	heap_tracker_cbs.free   = bc_free_probe_pt;

	list_init(&heap_tracker.hblocks);

	bc_update_tracker(heap_tracker.mblock, 0,
					  "MALLOC   : %05d : %05d\n",
					  heap_tracker.msize,
					  heap_tracker.msize - heap_tracker.mfree);
	bc_update_tracker(heap_tracker.mblock, 1,
					  "CALLOC   : %05d : %05d\n",
					  heap_tracker.csize,
					  heap_tracker.csize - heap_tracker.cfree);
	bc_update_tracker(heap_tracker.mblock, 2,
					  "MEM LEAK : %05d\n",
					  (heap_tracker.msize + heap_tracker.csize) -
					  (heap_tracker.mfree + heap_tracker.cfree));
}

void bc_deinit_heap_tracker()
{
	bc_deallocate_tracker(heap_tracker.tracker);
}