#ifndef __SIGNALS__
#define __SIGNALS__

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

void init_sighandlers(struct agent_struct *data);

#endif /* __SIGNALS__ */
