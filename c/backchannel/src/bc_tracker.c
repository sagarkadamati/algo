#include "bc_tracker.h"

#include "bc_heap_tracker.h"
#include "bc_cmd_tracker.h"
#include "bc_stream_tracker.h"

#define TRACKER_TOTAL_SIZE	(HEAP_TRACKER_SIZE +	\
							CMD_TRACKER_SIZE +		\
							STREAM_TRACKER_SIZE)

void print_theaders()
{
	int id;
	for (id = 0; id < new_trackers.header->tcount; id++)
	{
		printf("\n");
		printf("Name       : %s\n", new_trackers.theaders[id].name);
		printf("id         : %d\n", new_trackers.theaders[id].id);
		printf("offset     : %d\n", new_trackers.theaders[id].offset);
		printf("size       : %d\n", new_trackers.theaders[id].size);
		printf("use        : %d\n", new_trackers.theaders[id].use);
	}
}

char* bc_get_mblock(int fd, int offset, int size)
{
	void* map = mmap(0, size,
				PROT_READ | PROT_WRITE,
				MAP_SHARED,	fd, offset);
	if (map == MAP_FAILED)
		return NULL;

	return (char*) map;
}

void bc_setup_headers(struct tracker_meta_header *header,
						struct tracker_header *theaders)
{
	int id;
	struct tracker_header_tmp {
		char* name;
		int size;
	} thread_headers[] = {
		{ HEAP_TRACKER_NAME		, HEAP_TRACKER_SIZE		},
		{ CMD_TRACKER_NAME		, CMD_TRACKER_SIZE		},
		{ STREAM_TRACKER_NAME	, STREAM_TRACKER_SIZE	},
	};

	for (id = 0; id < header->tcount; id++)
	{
		strcpy(theaders[id].name, thread_headers[id].name);
		theaders[id].size	= thread_headers[id].size;
		theaders[id].use	= DONT_USE_TRACKER;
		theaders[id].id		= id;

		if (id)
			theaders[id].offset = theaders[id - 1].offset +
									theaders[id - 1].size;
		else
			theaders[id].offset = 0;
	}
}

void bc_setup_trackers()
{
	int fd = shm_open("bc_tracker", O_RDWR | O_CREAT, 0666);
	if (fd)
	{
		struct tracker_meta_header *header;
		struct tracker_header *theaders;
		char* map;

		int meta_hsize			= sizeof(struct tracker_meta_header);
		int tracker_hsize		= sizeof(struct tracker_header);
		int size				= meta_hsize + TRACKER_TOTAL_SIZE +
									(TRACKERS_COUNT * tracker_hsize);

		ftruncate(fd, size);
		map						= bc_get_mblock(fd, 0, size);

		header					= (struct tracker_meta_header*) map;
		header->size			= size;
		header->tcount			= TRACKERS_COUNT;
		header->t_hoffset		= meta_hsize;
		header->t_doffset		= header->t_hoffset + (TRACKERS_COUNT * tracker_hsize);

		theaders				= (struct tracker_header*)
									map + header->t_hoffset;

		bc_setup_headers(header, theaders);
		munmap(map, size);
		close(fd);
	}
}

int bc_load_trackers()
{
	int fd = shm_open("bc_tracker", O_RDWR, 0666);
	if (fd)
	{
		struct tracker_meta_header header;

		read(fd, &header, sizeof(header));
		new_trackers.mblock.mmap	= bc_get_mblock(fd, 0, header.size);
		new_trackers.mblock.size	= header.size;

		new_trackers.header			= (struct tracker_meta_header*)
										new_trackers.mblock.mmap;

		new_trackers.theaders		= (struct tracker_header*)
										new_trackers.mblock.mmap +
										new_trackers.header->t_hoffset;
		close(fd);

		print_theaders();
		return 0;
	}

	return 1;
}

int bc_load_trackers_from_data(char* data, int size)
{
	int fd = shm_open("bc_tracker", O_RDWR, 0666);
	if (fd)
	{
		new_trackers.mblock.mmap	= data;
		new_trackers.mblock.size	= size;

		new_trackers.header			= (struct tracker_meta_header*)
										new_trackers.mblock.mmap;
		new_trackers.theaders		= (struct tracker_header*)
										new_trackers.mblock.mmap +
										new_trackers.header->t_hoffset;
		print_theaders();
		return 0;
	}

	return 1;
}

tracker* bc_get_tracker_by_id(int id)
{
	list_node *node = trackers.next;
	tracker *t = NULL;
	int index;

	while (node != &trackers)
	{
		t = container_of(node, tracker, node);
		if (t->id == id)
			return t;

		node = node->next;
	}

	t = bc_calloc(1, sizeof(tracker));
	for (index = 0; index < new_trackers.header->tcount; index++)
		if (new_trackers.theaders[index].id == id)
		{
			t->mblock = (new_trackers.mblock.mmap +
							new_trackers.header->t_doffset +
							new_trackers.theaders[index].offset);
			t->size = new_trackers.theaders[index].size;
			t->id = id;
		}

	list_add(&trackers, &t->node);
	return t;
}

tracker* bc_get_tracker_by_name(char* tracker_name)
{
	list_node *node = trackers.next;
	tracker *t = NULL;
	int index;

	while (node != &trackers)
	{
		t = container_of(node, tracker, node);
		if (!strcmp(t->name, tracker_name))
			return t;

		node = node->next;
	}

	t = bc_calloc(1, sizeof(tracker));
	for (index = 0; index < new_trackers.header->tcount; index++)
		if (!strcmp(new_trackers.theaders[index].name, tracker_name)) {
			t->mblock = (new_trackers.mblock.mmap +
							new_trackers.header->t_doffset +
							new_trackers.theaders[index].offset);
			t->size = new_trackers.theaders[index].size;
			strcpy(t->name, new_trackers.theaders[index].name);
		}

	list_add(&trackers, &t->node);
	return t;
}

void bc_enable_tracker(tracker *t)
{
	t->use = USE_TRACKER;
}

void bc_disable_tracker(tracker *t)
{
	t->use = DONT_USE_TRACKER;
}

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
	t = NULL;
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

	bc_disable_tracker(cmd_stream.tracker);
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
			t->mblock = bc_get_mblock(fd, 0, size);

			close(fd);
			if (!t->mblock)
				bc_release_tracker(t);
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
