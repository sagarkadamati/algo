#include "bc_tracker.h"

int bc_update_tracker(tracker *t, int line, const char *fmt, ...)
{
	int len;
	va_list args;

	if (line >= t->lines)
		return 0;

	va_start(args, fmt);
	len = vsnprintf(t->mmap + (line * TRACKER_LINE_SIZE),
			TRACKER_LINE_SIZE, fmt, args);
	va_end(args);

	return len;
}

tracker* bc_allocate_tracker(char* tracker_name, int lines)
{
	tracker *t = calloc(1, sizeof(tracker));
	list_add(&trackers, &t->head);

	t->lines = lines;
	t->mmap_size = TRACKER_LINE_SIZE * lines;
	
	t->fd = shm_open(tracker_name, O_RDWR | O_CREAT, 0666);
	if ( t->fd < 0)
		return NULL;

	ftruncate(t->fd, t->mmap_size);
	t->mmap = (char*) mmap(0, t->mmap_size,
				PROT_READ | PROT_WRITE, MAP_SHARED, t->fd, 0);
	if (t->mmap == MAP_FAILED)
		close(t->fd);

	t->mmap[t->mmap_size - 1] ='\n';

	return t;
}

void bc_deallocate_tracker(tracker *t)
{
	if(t->mmap != MAP_FAILED)
		munmap(t->mmap, t->mmap_size);

	if (t->fd)
		close(t->fd);

	list_remove(&t->head);
	free(t);
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
		t = container_of(node, tracker, head);
		node = node->next;

		bc_deallocate_tracker(t);
	}
}