#include <bc_tracker.h>

int bc_set_streams(tracker *tracker, stream *strm, unsigned int size)
{
	int id;
	int ssize;

	for (id = 0; id < size; id++) {
		if (strm[id].ssize > 0)
			ssize += strm[id].ssize;
	}

	if (ssize <= tracker->size) {
		tracker->scount = size;
		stream* tstream = (stream*) tracker->mblock;
		for (id = 0; id < tracker->scount; id++) {
			tstream[id].sid = strm[id].sid;
			tstream[id].ssize = strm[id].ssize;

			if (id)
				tstream[id].soffset =
					tstream[id - 1].soffset + tstream[id - 1].ssize;
			else
				tstream[id].soffset = (size * sizeof(stream));
		}
		return 0;
	}

	return -1;
}

stream* bc_get_stream_by_id(tracker *tracker, int sid)
{
	int id;

	stream* tstream = (stream*) tracker->mblock;
	for (id = 0; id < tracker->scount; id++)
		if (tstream[id].sid == sid)
			return &tstream[id];

	return 0;
}