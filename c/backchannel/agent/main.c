#include "main.h"

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
	agent.tracker_id = -1;
}

int main(int argc, char *argv[])
{
	int opt;
	int field;
	int long id;

	init_agent();
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
		if (!(strcmp(argv[field], "trackers")))
			agent.cmd = LIST_TRACKERS;

		if (!(strcmp(argv[field], "track"))) {
			agent.cmd = SHOW_TRACKER;
			if (str_to_long(argv[++field], &id))
				agent.tracker_id = id;
		}
	}

	init_sighandlers();
	start_agent();

	return 0;
}
