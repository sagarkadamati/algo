#ifndef __BC_TRACKER__
#define __BC_TRACKER__

#include <bc_stream.h>
#include <bc_list.h>

#define ADD_TRACKER(_id, _name, _size, _init, _deinit)	\
	_id,

enum tracker_ids {
	#include <bc_trackers_list.h>
	TRACKERS_COUNT,
};

enum can_we_user_tracker {
	DONT_USE_TRACKER,
	USE_TRACKER,
};

typedef struct struct_tracker {
	int fd;
	int id;
	int use;
	int scount;
	char* name;
	char* mblock;
	int size;
	list_node mblocks;
	list_node node;
} tracker;

tracker* bc_allocate_tracker(char* tracker_name);
void     bc_deallocate_tracker(tracker *t);

/////////////////////////////////

#define can_we_use(_tracker) (_tracker->use)

int bc_load_trackers(void);
int bc_load_trackers_from_data(char* data, int size);

tracker* bc_get_tracker_by_id(int id);
tracker* bc_get_tracker_by_name(char* tracker_name);

void print_theaders(void);
void bc_enable_tracker(tracker *t);
void bc_disable_tracker(tracker *t);

int bc_setup_streams(tracker *tracker, stream *strm, unsigned int size);
stream* bc_get_stream_by_id(tracker *tracker, int sid);

#endif /* __BC_TRACKER__ */