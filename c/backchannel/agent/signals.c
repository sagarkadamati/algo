#include "signals.h"

void sig_handlers(int signal)
{

	switch (signal)
	{
	case SIGTERM:
		break;
	case SIGSEGV:
		break;
	case SIGINT:
		break;
	case SIGILL:
		break;
	case SIGABRT:
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

	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGILL, &sa, NULL);
	sigaction(SIGABRT, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);
}