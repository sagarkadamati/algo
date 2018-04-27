#ifndef __BC_STREAM_TRACKER__
#define __BC_STREAM_TRACKER__

#include "bc_os_headers.h"

#include "bc_tracker.h"
#include "bc_cmd_tracker.h"

#define STREAM_TRACKER		"bc_stream"
#define STREAM_ALLOC_SIZE	550
#define STREAM_SIZE			3

enum STREAM_TYPE {
	TYPE1 = 1,
	TYPE2
};

struct streams_header {
	char name[100];
	int  enable;

	int streams_offset;
	int streams_size;
	int streams_count;

	int cmds_count;
};

struct streams {
	char name[100];

	int enable;
	int used;

	int id;
	int type;
	int sid;
	pid_t pid;

	struct cmd_str {
		char name[100];
		int  enable;

		int cmd;
		int status;
		int xcount;

		struct timespec tenter;
		struct timespec texit;
		struct timespec tavg;
	} cmds[CMDS_SIZE];
};

struct stream_tracker {
	tracker *tracker;
	tracker_mblock *mblock;
	int stream_index[550];

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

#endif /* __BC_STREAM_TRACKER__ */
