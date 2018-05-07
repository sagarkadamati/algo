#ifndef __SERVER__ 
#define __SERVER__ 

#include "main.h"
#include "socket.h"

void process_request(int socket);
void server(struct agent_struct *agent);

#endif /* __SERVER__ */
