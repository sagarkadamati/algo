#include "main.h"

#include "daemon.h"
#include "server.h"
#include "client.h"
#include "bridge.h"
#include "signals.h"

struct agent_struct agent;

void start_agent()
{
	switch(agent.mode) {
		case BRIDGE:
			run_as_background("Running in bridge mode");
			bridge();
			break;
		case SERVER:
			run_as_background("Running in server mode");
			server();
			break;
		default:
			client();
	}
}

static void init_agent(void)
{
	agent.cmd = DEFAULT;
	agent.mode = CLIENT;
	agent.verbose = 0;
}

int main(int argc, char *argv[])
{
	int opt;
	int field;
	while ((opt = getopt(argc, argv, "dbv")) != -1)
	{
		switch (opt)
		{
			case 'd':
				agent.mode = SERVER;
				break;
			case 'b':
				agent.mode = BRIDGE;
			case 'v':
				agent.verbose = 1;
		}
	}

	for (field = 1; field < argc; field++)
	{
		if (!(strcmp(argv[field], "list")))
			agent.cmd = LIST_TRACKERS;
	}

	init_agent();
	init_sighandlers();
	start_agent();

	return 0;
}
