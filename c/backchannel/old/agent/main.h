#ifndef __MAIN__
#define __MAIN__

enum MODE {
	BRIDGE,
	SERVER,
	CLIENT
};

enum CMD {
	DEFAULT,
	LIST_TRACKERS,
};

struct agent_struct {
	enum MODE mode;
	enum CMD cmd;
	int server_lskt;
	int server_rskt;
	int client_sskt;
	int verbose;
};
extern struct agent_struct agent;

#endif /* __MAIN__ */
