#ifndef __SIGNALS__
#define __SIGNALS__

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "main.h"
#include "socket.h"

void init_sighandlers(void);

#endif /* __SIGNALS__ */
