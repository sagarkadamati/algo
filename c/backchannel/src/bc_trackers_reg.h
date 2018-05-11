#ifndef __BC_TRACKERS_REG__
#define __BC_TRACKERS_REG__

enum tracker_ids {
	HEAP_TRACKER_ID,
	CMD_TRACKER_ID,
	STREAM_TRACKER_ID,
	TRACKERS_COUNT,
};

void bc_setup_headers(struct tracker_meta_header *header,
						struct tracker_header *theaders);
void bc_setup_trackers(void);

#endif /* __BC_TRACKERS_REG__ */
