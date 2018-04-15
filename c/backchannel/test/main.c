#include "main.h"

void sighandlers(int signal)
{
    switch(signal)
    {
        case SIGTERM:
            bc_deinit();
            break;
        case SIGSEGV:
            bc_deinit();
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

    abort();
}

static void init_sighandler()
{
    sa.sa_handler = sighandlers;
    sa.sa_flags = SA_SIGINFO;
    // sa.sa_flags = /*SA_RESETHAND | */SA_NODEFER;  /* To have or have not */
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGILL, &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
    sigaction(SIGFPE, &sa, NULL);
}

int main(void)
{
    init_sighandler();

    printf("DEBUG: PID: %d\n", getpid());

    while(1);
    return 0;
}