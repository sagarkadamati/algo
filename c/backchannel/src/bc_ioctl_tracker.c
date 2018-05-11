#include "bc_ioctl_tracker.h"

void bc_update_ioctl(int index)
{
	struct timespec spec;

	bc_ioctls[index].exe_count++;

	timespec_diff(&bc_ioctls[index].tenter,
			&bc_ioctls[index].texit, &spec);
	bc_update_tracker(ioctl_tracker, (index + 3),
		"\n| %-50s | %4lu.%-11lu | %5d | %5d |",
		bc_ioctls[index].name,
		spec.tv_sec, spec.tv_nsec,
		bc_ioctls[index].exe_count,
		bc_ioctls[index].status);
}

void
	__NO_TRACKING__
	bc_update_ioctls(enum position pos, int cmd, int status)
{
	long int ns;
	int index;

	if(!bc_ioctls)
		return;

	index = bc_get_ioctl_num(cmd);
	switch(pos)
	{
		case ENTER:
			clock_gettime(CLOCK_REALTIME, &bc_ioctls[index].tenter);
			break;
		case EXIT:
			clock_gettime(CLOCK_REALTIME, &bc_ioctls[index].texit);
			bc_ioctls[index].status = status;
			bc_update_ioctl(index);
			break;
	}
}

void bc_update_tracker_header()
{
	bc_update_tracker(ioctl_tracker, 0,
		"|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(ioctl_tracker, 1,
		"\n| %-20s%-10s%-20s |  %14s  | %5s |",
		" ", "IOCTL NAME", " ", "Execution Time", "Count");

	bc_update_tracker(ioctl_tracker, 2,
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");

	bc_update_tracker(ioctl_tracker, (IOCTL_SIZE - 1),
		"\n|-%-50s-+--%14s--+-%5s-|", "----------"
		"----------""----------""----------""----------",
		"----------""----","-----");
}

void* bc_allocate_ioctls()
{
	return calloc(IOCTL_SIZE, sizeof(struct bc_ioctl_struct));
}

void bc_deallocate_ioctls()
{
	if(bc_ioctls)
		free(bc_ioctls);
}

void
	__NO_TRACKING__
	bc_init_ioctl_tracker()
{
	ioctl_tracker = bc_allocate_tracker(IOCTL_TRACKER, IOCTL_SIZE);

	bc_update_tracker_header();
	bc_ioctls = bc_allocate_ioctls();
	if (bc_ioctls)
		bc_add_ioctls();
}

void
	__NO_TRACKING__
	bc_deinit_ioctl_tracker()
{
	bc_deallocate_tracker(ioctl_tracker);
	bc_deallocate_ioctls();
}
