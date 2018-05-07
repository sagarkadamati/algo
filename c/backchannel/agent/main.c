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
			run_as_background();
			bridge(&agent);
			break;
		case SERVER:
			run_as_background();
			server(&agent);
			break;
		default:
			client(&agent);
	}
}

int main(int argc, char *argv[])
{
	int opt;
	agent.mode = CLIENT;
	agent.verbose = 0;

	init_sighandlers(&agent);

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

	start_agent();

	return 0;
}