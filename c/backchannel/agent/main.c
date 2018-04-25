#include "main.h"

void start_agent(enum MODE mode)
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
			client();
	}
}

int main(int argc, char *argv[])
{
	enum MODE mode = CLIENT;

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
		}
	}

	start_agent(mode);

	return 0;
}