#ifndef __BC_TRACKERS_REG__
#define __BC_TRACKERS_REG__

#define ADD_TRACKER(_id, _name, _size, _init, _deinit)	\
	_id,

enum tracker_ids {
	#include "bc_trackers_list.h"
	TRACKERS_COUNT,
};

void bc_setup_headers(struct tracker_meta_header *header,
						struct tracker_header *theaders);
void bc_setup_trackers(void);

#endif /* __BC_TRACKERS_REG__ */