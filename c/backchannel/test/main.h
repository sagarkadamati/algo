#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <execinfo.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include <bc_init.h>

struct sigaction sa = {};
