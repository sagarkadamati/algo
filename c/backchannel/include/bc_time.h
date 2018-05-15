#ifndef __BC_TIME__
#define __BC_TIME__

#include "bc_os_headers.h"

#define timespec_current(_time)									\
	clock_gettime(CLOCK_REALTIME, _time);

#define timespec_diff(_start, _end, _diff)						\
    if (((_end)->tv_nsec - (_start)->tv_nsec) < 0)				\
	{															\
        (_diff)->tv_sec  =										\
			(_end)->tv_sec  - (_start)->tv_sec - 1;				\
        (_diff)->tv_nsec =										\
			(_end)->tv_nsec - (_start)->tv_nsec + 1000000000UL;	\
    }															\
	else														\
	{															\
        (_diff)->tv_sec  = (_end)->tv_sec  - (_start)->tv_sec;	\
        (_diff)->tv_nsec = (_end)->tv_nsec - (_start)->tv_nsec;	\
    }

void timespec_diff_func(struct timespec *start, struct timespec *stop,
                   struct timespec *result);

void update_time(struct timespec *time);

void timespec_avg(struct timespec *old, struct timespec* new, int count);

#endif /*__BC_TIME__ */