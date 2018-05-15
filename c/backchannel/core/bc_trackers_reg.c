#include "bc_tracker.h"
#include "bc_trackers_reg.h"

#include "bc_trackers_header.h"

#undef  ADD_TRACKER
#define ADD_TRACKER(_id, _name, _size, _init, _deinit)	\
	{ _name, _size },

struct tracker_header_tmp {
	char* name;
	int size;
} thread_headers[] = {
	#include "bc_trackers_list.h"
};

static char* bc_get_mblock(int fd, int offset, int size)
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

		int id;
		int size;
		int tracker_total_size = 0;
		int meta_hsize			= sizeof(struct tracker_meta_header);
		int tracker_hsize		= TRACKERS_COUNT * sizeof(struct tracker_header);

		for (id = 0; id < TRACKERS_COUNT; id++)
			tracker_total_size += thread_headers[id].size;

		size = meta_hsize + tracker_total_size + tracker_hsize;

		ftruncate(fd, size);
		map						= bc_get_mblock(fd, 0, size);

		header					= (struct tracker_meta_header*) map;
		header->size			= size;
		header->tcount			= TRACKERS_COUNT;
		header->t_hoffset		= meta_hsize;
		header->t_doffset		= header->t_hoffset + tracker_hsize;

		theaders				= (struct tracker_header*)
									map + header->t_hoffset;

		bc_setup_headers(header, theaders);
		munmap(map, size);
		close(fd);
	}
}
