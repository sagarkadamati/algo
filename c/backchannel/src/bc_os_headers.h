#ifndef  __BC_OS_HEADERS__
#define  __BC_OS_HEADERS__

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

enum position{
	ENTER,
	EXIT
};

#define __NO_TRACKING__ __attribute__((__no_instrument_function__))

// #include <bc_process_headers.h>

#endif /* __BC_OS_HEADERS__ */