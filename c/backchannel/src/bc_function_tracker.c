#include "bc_function_tracker.h"

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
			// msync(function_stream.mblock->mmap, function_stream.mblock->mmap_size, 0);

			// bc_update_tracker(function_stream.mblock, i++,
			// 	 "\nENTER 0x%x", func);
			break;
		case EXIT:
			f->id = i + 3;
			f->name = "TESTING";
			i++;
			// msync(function_stream.mblock->mmap, function_stream.mblock->mmap_size, 0);
			// bc_update_tracker(function_stream.mblock, i++,
			// 	 "\nEXIT 0x%x", func);
			break;
	}
}

void __NO_TRACKING__ __cyg_profile_func_enter(void *func, void *caller)
{
	switch(function_stream.cond)
	{
		case ENABLE:
			bc_update_function(ENTER, func, caller);
			break;
		case ENABLE_LEVEL:
			function_stream.level++;
			if (function_stream.level == function_stream.level_enabled)
				bc_update_function(ENTER, func, caller);
			break;
		case ENABLE_SELECT_COUNT:
			function_stream.level++;
			if (function_stream.level == 1)
				function_stream.level_count++;
			if (function_stream.level_count == function_stream.level_count_enabled)
				bc_update_function(ENTER, func, caller);
			break;
		case DISABLE:
			break;
	}
}

void __NO_TRACKING__ __cyg_profile_func_exit(void *func, void *caller)
{
	switch(function_stream.cond)
	{
		case ENABLE:
			bc_update_function(EXIT, func, caller);
			break;
		case ENABLE_LEVEL:
			if (function_stream.level == function_stream.level_enabled)
				bc_update_function(EXIT, func, caller);
			function_stream.level--;
			break;
		case ENABLE_SELECT_COUNT:
			if (function_stream.level_count == function_stream.level_count_enabled)
				bc_update_function(EXIT, func, caller);
			function_stream.level--;
		case DISABLE:
			break;
	}
}


void bc_update_function_tracker_header()
{
	bc_update_tracker(function_stream.mblock, 0,
		"|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(function_stream.mblock, 1,
		"\n| %-20s%-10s%-20s |  %14s  | %5s |",
		" ", "FUNCTION NAME", " ", "Execution Time", "Count");

	bc_update_tracker(function_stream.mblock, 2,
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(function_stream.mblock, (FUNCTIONS_SIZE - 1),
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");
}

void bc_deallocate_functions()
{
	if(function_stream.functions)
		bc_free(function_stream.functions);
}

void bc_init_function_tracker()
{
	function_stream.tracker = bc_allocate_tracker(FUNCTION_TRACKER);
	function_stream.mblock = bc_allocate_mblock(function_stream.tracker, FUNCTIONS_SIZE);

	// bc_update_function_tracker_header();
}

void bc_deinit_function_tracker()
{
	bc_deallocate_tracker(function_stream.tracker);
	bc_deallocate_functions();
}