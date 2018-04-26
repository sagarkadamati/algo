#ifndef __BC_STREAM_TRACKER__
#define __BC_STREAM_TRACKER__

#include "bc_os_headers.h"

#include "bc_tracker.h"
#include "bc_cmd_tracker.h"

#define STREAM_TRACKER       "bc_stream"

#define STREAM_SIZE  1
#define STREAM_COUNT 550

enum STREAM_TYPE {
	TYPE1 = 1,
	TYPE2
};

struct streams_header {
	char name[100];
	int  enable;

	int streams_offset;
	int streams_size;
};

struct streams {
	char name[100];
	int  enable;

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

struct stream_struct {
	int id;
	int enable;
	char* name;
	long int exe_count;

	struct timespec trequest;
	struct timespec tdone;
	struct timespec tavg;

	int sid;
	int type;
	pid_t pid;
};

struct stream_tracker {
	tracker *tracker;
	tracker_mblock *mblock;

	struct streams_header *header;
	struct streams *streams;

	struct stream {
		tracker_mblock *mblock;
		struct stream_struct *data;
		struct cmds *cmds;
	} stream[512];
} stream_tracker;

void bc_init_stream_tracker(void);
void bc_deinit_stream_tracker(void);
void bc_print_stream(int index, const char *fmt, ...);
void bc_add_stream(void);
void bc_update_stream(int sid, enum position pos, int cmd);
void bc_update_stream_data(int index);
void bc_update_stream_header(int sid);
void bc_update_stream_cmd(int sid, enum position pos, int cmd, int status);
void bc_allocate_stream(pid_t pid, int sid);
void bc_update_stream_type(int sid, enum STREAM_TYPE type);

char* bc_get_stream_name(int cmd);
int get_stream_count(void);
int bc_get_stream_num(int cmd);

void bc_update_streams(int stream, const char *name, pid_t pid);
void bc_update_streams_cmd(int stream, int cmd, enum position pos, int status);
void bc_enable_stream(int stream);
void bc_disable_stream(int stream);
void bc_update_stream_offsets(void);
void bc_init_stream_tracker(void);

#endif /* __BC_STREAM_TRACKER__ */
