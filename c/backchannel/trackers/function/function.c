#include "function.h"
#include "bc_tracker.h"
#include "../core/bc_tracker_internal.h"

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

int i = 0;
void __NO_TRACKING__ bc_update_function(enum position pos, void *func, void *caller)
{
	struct function_struct *f;
	f = (struct function_struct*) function_stream.mblock->mmap;
	f += i;

	switch (pos)
	{
		case ENTER:
			f->id = i + 3;
			f->name = "TESTING";
			i++;
			break;
		case EXIT:
			f->id = i + 3;
			f->name = "TESTING";
			i++;
			break;
	}
}

void __NO_TRACKING__ __cyg_profile_func_enter(void *func, void *caller)
{
	if (function_stream.enable)
	{
		function_stream.depth++;
		if (function_stream.enable_level_at_depth == function_stream.depth)
			function_stream.level++;

		switch(function_stream.cond)
		{
			case ENABLE:
				bc_update_function(ENTER, func, caller);
				break;
			case ENABLE_LEVEL:
				if (function_stream.level & function_stream.level_enabled)
					bc_update_function(ENTER, func, caller);
				break;
			case ENABLE_SELECT_COUNT:
				if (function_stream.level == 1)
					function_stream.level_count++;
				if (function_stream.level_count == function_stream.level_count_enabled)
					bc_update_function(ENTER, func, caller);
				break;
			case DISABLE:
				break;
		}
	}
}

void __NO_TRACKING__ __cyg_profile_func_exit(void *func, void *caller)
{
	if (function_stream.enable)
	{
		switch(function_stream.cond)
		{
			case ENABLE:
				bc_update_function(EXIT, func, caller);
				break;
			case ENABLE_LEVEL:
				if (function_stream.level & function_stream.level_enabled)
					bc_update_function(EXIT, func, caller);
				break;
			case ENABLE_SELECT_COUNT:
				if (function_stream.level_count == function_stream.level_count_enabled)
					bc_update_function(EXIT, func, caller);
			case DISABLE:
				break;
		}

		function_stream.depth--;
	}
}

void bc_init_function_tracker()
{
	function_stream.tracker = bc_allocate_tracker(FUNCTION_TRACKER);
	function_stream.mblock = bc_allocate_mblock(function_stream.tracker, FUNCTIONS_SIZE);
	function_stream.enable = 1;
}

void bc_deallocate_functions()
{
	if(function_stream.functions)
		free(function_stream.functions);
}

void bc_deinit_function_tracker()
{
	if (function_stream.enable)
	{
		bc_deallocate_tracker(function_stream.tracker);
		bc_deallocate_functions();
	}
}