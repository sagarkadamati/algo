#include "data_processor.h"

void process_heap_data()
{
	heap_header *header;
	heap_block *alloc_ptr;

	tracker *t = bc_get_tracker_by_id(HEAP_TRACKER_ID);

	header		= (heap_header*) t->mblock;
	alloc_ptr	= (heap_block*)(t->mblock + sizeof(heap_header));
	printf("Heap:\n\n");

	printf("%4s Status:\n", "");
		printf("%8s M Alloc : %-10u (%u blocks)\n", "", header->msize, header->mcount_alloc);
		printf("%8s M Free  : %-10u (%u blocks)\n", "", header->mfree, header->mcount_free);
		printf("%8s C Alloc : %-10u (%u blocks)\n", "", header->csize, header->ccount_alloc);
		printf("%8s C Free  : %-10u (%u blocks)\n", "", header->cfree, header->ccount_free);
		if (header->dfree)
			printf("%8s D Free  : %u\n", "", header->dfree);
	printf("\n");
	printf("%4s Total:\n", "");
		printf("%8s Alloc   : %-10u (%u blocks)\n", "",
					(header->msize + header->csize),
					(header->mcount_alloc + header->ccount_alloc));
		printf("%8s Free    : %-10u (%u blocks)\n", "",
					(header->mfree + header->cfree),
					(header->mcount_free + header->ccount_free));
		printf("%8s Leak    : %-10u (%u blocks)\n", "",
					((header->msize + header->csize) -
					(header->mfree + header->cfree)),
					((header->mcount_alloc + header->ccount_alloc) -
					(header->mcount_free + header->ccount_free)));
	printf("\n");
	if ((header->msize + header->csize) - (header->mfree + header->cfree))
	{
		printf("%4s Leaks:\n", "");
	}
	printf("\n");
}

void process_tracker()
{
	struct streams_header *header;
	struct streams *stream;
	struct streams *streams;
	int offset;
	int i, j, size;
	char* ch;

	tracker* t = bc_get_tracker_by_id(STREAM_TRACKER_ID);

	ch = t->mblock;
	header = (struct streams_header*)ch;
	offset = header->streams_offset;
	size = header->streams_size;
	streams = (struct streams*) (ch + offset);

	if (agent.verbose)
		printf("DEBUG: Processing data\n");
	for (i = 0; i < size; i++) {
		stream = streams + i;
		if (stream->enable) {
			printf("%s %d: %d\n",
				stream->name,
				stream->id,
				stream->pid);

			for (j = 0; j < header->cmds_count; j++) {
				if (stream->cmds[j].enable) {
					printf("%4s %-40s: %5d, %4lu.%09lu sec\n",
						"", stream->cmds[j].new_name,
						stream->cmds[j].xcount,
						stream->cmds[j].tavg.tv_sec,
						stream->cmds[j].tavg.tv_nsec);
				}
			}
		}
	}
}

void update_tracker_id()
{
	if (agent.tracker_id == -1) {

	}
}

void process_data()
{
	switch (agent.cmd) {
		case LIST_TRACKERS:
			print_theaders();
			break;
		case SHOW_TRACKER:
			update_tracker_id();
			if (agent.tracker_id != -1)
				printf("\n");

			switch (agent.tracker_id) {
				case HEAP_TRACKER_ID:
					process_heap_data();
					break;
				default:
					// process_tracker();
					break;
			}
//			if (agent.tracker_id != -1)
//				printf("\n");

			break;
		case DEFAULT:
			break;
	}
}
