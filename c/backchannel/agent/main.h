#ifndef __MAIN__
#define __MAIN__

#include "daemon.h"
#include "server.h"
#include "client.h"
#include "bridge.h"
#include "signals.h"

#include "bc_print.h"

enum MODE {
	BRIDGE,
	SERVER,
	CLIENT
};

enum CMD {
	DEFAULT,
	LIST_TRACKERS,
	SHOW_TRACKER,
};

struct agent_struct {
	enum MODE mode;
	enum CMD cmd;
	int server_lskt;
	int server_rskt;
	int client_sskt;
	int verbose;
	int tracker_id;
};
extern struct agent_struct agent;

#endif /* __MAIN__ */
