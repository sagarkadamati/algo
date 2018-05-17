#include "heap_viewer.h"

void process_heap_data()
{
	stream *strm;
	heap_status *header;

	tracker *t	= bc_get_tracker_by_id(HEAP_TRACKER_ID);

	strm		= bc_get_stream_by_id(t, BC_HEAP_STATUS_STREAM);
	header		= (heap_status*) STREAM_DATA(t, strm);

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
		// heap_block *alloc_ptr;

		// strm		= bc_get_stream_by_id(t, BC_HEAP_BLOCKS_STREAM);
		// alloc_ptr	= (heap_block*) STREAM_DATA(t, strm);

		printf("%4s Leaks:\n", "");
	}
	printf("\n");
}
