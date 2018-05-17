#ifndef __SERVER__ 
#define __SERVER__ 

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>

#include "agent.h"
#include "socket.h"

#include <bc_tracker.h>

#define STREAM_FILE "bc_tracker"
#define MAX_BUF_SIZE 1024

void process_request(int socket);
void server(void);

#endif /* __SERVER__ */
