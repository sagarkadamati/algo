#include <bc_tracker.h>

int bc_setup_streams(tracker *tracker, stream *strm, unsigned int size)
{
	int id;

	if ((size <= tracker->scount) && (size >= 0)) {
		stream* tstream = (stream*) tracker->mblock;
		for (id = 0; id < tracker->scount; id++) {
			tstream[id].sid		= strm[id].sid;
			tstream[id].ssize	= strm[id].ssize;

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

	stream* tstream = tracker->streams;
	for (id = 0; id < tracker->scount; id++)
		if (tstream[id].sid == sid)
			return &tstream[id];

	return 0;
}