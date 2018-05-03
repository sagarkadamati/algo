#ifndef __BC_STREAM_TRACKER__
#define __BC_STREAM_TRACKER__

#include "bc_os_headers.h"

#include "bc_tracker.h"
#include "bc_cmd_tracker.h"

#define STREAM_TRACKER		"bc_stream"

#define MAX_STREAMS			3
#define MAX_VSTREAMS		550

#define STREAM_NAME_SIZE	20

enum STREAM_TYPE {
	TYPE1 = 1,
	TYPE2
};

struct streams_header {
	char name[STREAM_NAME_SIZE];
	int  enable;

	int streams_offset;
	int streams_size;
	int streams_count;

	int cmds_count;
};

struct streams {
	char name[STREAM_NAME_SIZE];

	int enable;
	int used;

	int id;
	int type;
	int sid;
	pid_t pid;

	command cmds[CMDS_SIZE];
};

struct new_stream_tracker {
	int enable;
	int sindex[MAX_VSTREAMS];
	struct streams_header header;
	struct streams streams[MAX_STREAMS];
};

struct stream_tracker {
	tracker *tracker;
	int stream_index[MAX_VSTREAMS];
	int enable;

	struct streams_header *header;
	struct streams *streams;
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
void bc_tspec_avg(struct timespec *old, struct timespec* new, int count);

#endif /* __BC_STREAM_TRACKER__ */
