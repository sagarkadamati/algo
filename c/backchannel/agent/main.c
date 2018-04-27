#include "main.h"

void start_agent(enum MODE mode, int verbose)
{
	switch(mode) {
		case BRIDGE:
			run_as_background();
			bridge();
			break;
		case SERVER:
			run_as_background();
			server();
			break;
		default:
			client(verbose);
	}
}

int main(int argc, char *argv[])
{
	enum MODE mode = CLIENT;
	int verbose = 0;

	int opt;
	while ((opt = getopt(argc, argv, "db")) != -1)
	{
		switch (opt)
		{
			case 'd':
				mode = SERVER;
				break;
			case 'b':
				mode = BRIDGE;
			case 'v':
				verbose = 1;
		}
	}

	start_agent(mode, verbose);

	return 0;
}