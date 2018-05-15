#include "bc_time.h"

void timespec_diff_func(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000UL;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }
}

void update_time(struct timespec *time)
{
	clock_gettime(CLOCK_REALTIME, time);
}

void timespec_avg(struct timespec *old, struct timespec* new, int count)
{
	old->tv_sec  *= (count - 1);
	old->tv_sec  += new->tv_sec;
	old->tv_sec  /= count;

	old->tv_nsec *= (count - 1);
	old->tv_nsec += new->tv_nsec;
	old->tv_nsec /= count;
}