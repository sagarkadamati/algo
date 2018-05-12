#ifndef __BC_STREAM_TRACKER__
#define __BC_STREAM_TRACKER__

#include "bc_os_headers.h"
#include "bc_tracker.h"
#include "bc_trackers_reg.h"

#include "bc_cmd_factory.h"
#include "bc_cmd_tracker.h"
#include "bc_stream.h"

#define MAX_CMDS			CMDS_SIZE
#define MAX_STREAMS			3
#define MAX_VSTREAMS		550

DEFINE_STREAM_HEADER(streams_header, MAX_VSTREAMS);
DEFINE_STREAM(streams, MAX_CMDS);

#define STREAM_TRACKER_NAME	"stream_tracker"
#define STREAM_TRACKER_SIZE (MAX_STREAMS * sizeof(struct streams))

enum STREAM_TYPE {
	TYPE1 = 1,
	TYPE2
};

struct stream_tracker {
	int enable;
	int sindex[MAX_VSTREAMS];

	struct streams_header *header;
	struct streams *streams;

	tracker *tracker;
} stream_tracker;

void bc_setup_stream(void);
void bc_init_stream_tracker(void);
void bc_deinit_stream_tracker(void);

void bc_enable_stream(int stream);
void bc_disable_stream(int stream);

void bc_update_stream(int stream, const char *name, pid_t pid);
void bc_update_stream_cmd(int stream, int cmd, enum position pos, int status);
void bc_update_stream_data(int index);
void bc_update_stream_header(int stream);
void bc_update_stream_type(int stream, enum STREAM_TYPE type);
void bc_allocate_stream(int id);

#endif /* __BC_STREAM_TRACKER__ */
