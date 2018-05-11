#include "bc_tracker.h"
#include "bc_trackers_reg.h"

#include "bc_heap_tracker.h"
#include "bc_cmd_tracker.h"
#include "bc_stream_tracker.h"

#define TRACKER_TOTAL_SIZE	(				\
					HEAP_TRACKER_SIZE +	\
					CMD_TRACKER_SIZE  +	\
					STREAM_TRACKER_SIZE	\
				)

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
		int tracker_hsize		= TRACKERS_COUNT * sizeof(struct tracker_header);
		int size				= meta_hsize + TRACKER_TOTAL_SIZE + tracker_hsize;

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
