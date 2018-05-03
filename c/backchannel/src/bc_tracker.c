#include "bc_tracker.h"

int __NO_TRACKING__ bc_update_tracker(tracker_mblock *mblock, int line, const char *fmt, ...)
{
	int len;
	va_list args;

	if (line >= mblock->lines)
		return 0;

	va_start(args, fmt);
	len = vsnprintf(mblock->mmap + (line * TRACKER_LINE_SIZE),
			TRACKER_LINE_SIZE, fmt, args);
	va_end(args);

	return len;
}

tracker* bc_get_tracker(char* tracker_name)
{
	list_node *node = trackers.next;
	tracker *t = NULL;

	while (node != &trackers)
	{
		t = container_of(node, tracker, node);
		if(t->name == tracker_name)
			return t;

		node = node->next;
	}

	t = bc_calloc(1, sizeof(tracker));
	t->name = tracker_name;
	list_add(&trackers, &t->node);

	return t;
}

void bc_release_tracker(tracker* t)
{

}

tracker* bc_allocate_tracker(char* tracker_name)
{
	tracker *t = bc_get_tracker(tracker_name);
	t->name = tracker_name;

	list_init(&t->mblocks);

	return t;
}

tracker_mblock* bc_allocate_mblock(tracker *t, int lines)
{
	tracker_mblock *mblock = bc_calloc(1, sizeof(tracker_mblock));
	list_add(&t->mblocks, &mblock->node);

	mblock->lines = lines;
	mblock->mmap_size = TRACKER_LINE_SIZE * lines;

	t->size = mblock->mmap_size;
	t->fd = shm_open(t->name, O_RDWR | O_CREAT, 0666);
	if ( t->fd < 0)
		return NULL;

	ftruncate(t->fd, t->size);
	mblock->mmap = (char*) mmap(0, mblock->mmap_size,
				PROT_READ | PROT_WRITE, MAP_SHARED,
				t->fd, t->size - mblock->mmap_size);
	if (mblock->mmap == MAP_FAILED)
		mblock->mmap = NULL;

	close(t->fd);

	mblock->mmap[mblock->mmap_size - 1] ='\n';

	return mblock;
}

void bc_deallocate_mblock(tracker_mblock* mblock)
{
	/* TBD */

	// if(mblock)
	// 	munmap(mblock, );
}

void bc_deallocate_tracker(tracker *t)
{
	list_node *node = &t->mblocks;
	tracker_mblock *mblock;

	while (node != &t->mblocks)
	{
		mblock = container_of(node, tracker_mblock, node);
		node = node->next;

		list_remove(&mblock->node);
		bc_free(mblock);
	}

	list_remove(&t->node);
	bc_free(t);
}

tracker* bc_new_tracker(char* tname, int size)
{
	tracker *t = bc_get_tracker(tname);
	if (t)
	{
		int fd = shm_open(tname, O_RDWR | O_CREAT, 0666);
		if (fd)
		{
			ftruncate(fd, size);
			t->size   = size;
			t->mblock = (char*) mmap(0, size,
								PROT_READ | PROT_WRITE,
								MAP_SHARED,	fd, 0);

			if (t->mblock == MAP_FAILED)
			{
				bc_release_tracker(t);
			}
			close(fd);
		}
		else
			bc_release_tracker(t);
	}
	return t;
}

void bc_init_tracker()
{
	list_init(&trackers);
}

void bc_deinit_tracker()
{
	list_node *node = trackers.next;
	tracker *t;

	while (node != &trackers)
	{
		t = container_of(node, tracker, node);
		node = node->next;

		bc_deallocate_tracker(t);
	}
}