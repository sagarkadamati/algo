#include "signals.h"

struct sigaction sa = {};

void sig_handlers(int signal)
{
	switch (signal)
	{
	case SIGTERM:
		release_socket(agent.server_lskt);
		break;
	case SIGINT:
		release_socket(agent.server_lskt);
		break;
	case SIGSEGV:
		break;
	case SIGABRT:
		break;
	case SIGILL:
		break;
	case SIGFPE:
		break;
	default:
		break;
	}
}

void init_sighandlers()
{
	sa.sa_handler = sig_handlers;
	sa.sa_flags = SA_SIGINFO;
	// sa.sa_flags = /*SA_RESETHAND | */SA_NODEFER;  /* To have or have not */

	sigaction(SIGTERM,	&sa, NULL);
	sigaction(SIGSEGV,	&sa, NULL);
	sigaction(SIGINT,	&sa, NULL);
	sigaction(SIGILL,	&sa, NULL);
	sigaction(SIGABRT,	&sa, NULL);
	sigaction(SIGFPE,	&sa, NULL);
}
