#include "bc_init.h"

void
	__attribute__((constructor))
	bc_init(void)
{
	bc_init_tracker();

	bc_setup_trackers();
	bc_load_trackers();

	#undef  ADD_TRACKER
	#define ADD_TRACKER(_id, _name, _size, _init, _deinit)	\
		_init();

	#include "bc_trackers_list.h"
}

void
	__attribute__((destructor))
	bc_deinit(void)
{
	#undef  ADD_TRACKER
	#define ADD_TRACKER(_id, _name, _size, _init, _deinit)	\
		_deinit();

	#include "bc_trackers_list.h"

	bc_deinit_tracker();
}