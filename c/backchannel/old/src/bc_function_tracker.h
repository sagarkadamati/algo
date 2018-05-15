#ifndef __BC_function_TRACKER__
#define __BC_function_TRACKER__

#include "bc_os_headers.h"
#include "bc_tracker.h"
#include "bc_time.h"

#define FUNCTION_TRACKER     "bc_functions"
#define FUNCTIONS_SIZE       100

enum condition {
	DISABLE,
	ENABLE,
	ENABLE_LEVEL,
	ENABLE_SELECT_COUNT,
};

typedef struct function_struct {
	int id;
	char* name;
	long int xcount;
	struct timespec tenter;
	struct timespec texit;
	struct timespec tavg;
	int status;
} function_struct;

struct function_stream {
	tracker *tracker;
	tracker_mblock *mblock;

	function_struct *functions;
	list_node head;
	enum condition cond;
	int enable;
	int depth;
	int level;
	int enable_level_at_depth;
	int level_count;
	int level_enabled;
	int level_count_enabled;
} function_stream;

void __cyg_profile_func_enter(void *func, void *caller);
void __cyg_profile_func_exit(void *func, void *caller);

void bc_init_function_tracker(void);
void bc_deinit_function_tracker(void);
void bc_update_function_tracker_header(void);
void bc_update_function(enum position pos, void *func, void *caller);

void bc_deallocate_functions(void);

#endif /* __BC_FUNCTION_TRACKER__ */
