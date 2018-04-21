#ifndef __BC_TIME__
#define __BC_TIME__

#include <time.h>

void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result);

void update_time(struct timespec *time);

#endif /*__BC_TIME__ */