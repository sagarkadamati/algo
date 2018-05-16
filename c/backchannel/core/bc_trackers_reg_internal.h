#ifndef __BC_TRACKERS_REG_INTERNAL__
#define __BC_TRACKERS_REG_INTERNAL__

#include <bc_tracker.h>
#include <bc_trackers_header.h>

#include "bc_tracker_internal.h"

void bc_setup_headers(struct tracker_meta_header *header,
						struct tracker_header *theaders);
void bc_setup_trackers(void);

#endif /* __BC_TRACKERS_REG_INTERNAL__ */