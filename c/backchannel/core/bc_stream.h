#ifndef __BC_STREAM__
#define __BC_STREAM__

#include <bc_tracker.h>

void bc_stream_alloc(tracker *t, const int count, int size);
int bc_setup_streams(tracker *tracker, stream *strm, unsigned int size);
stream* bc_get_stream_by_id(tracker *tracker, int sid);

#endif /* __BC_STREAM__ */
