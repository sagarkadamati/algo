#ifndef __SERVICE__
#define __SERVICE__

enum MODE {
	BRIDGE,
	SERVER,
	CLIENT
};

struct agent_struct {
	enum MODE mode;
	int server_lskt;
	int server_rskt;
	int client_sskt;
	int verbose;
};

#endif /* __SERVICE__ */
