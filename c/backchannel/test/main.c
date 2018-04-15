#include "main.h"

void sighandlers(int signal)
{
    switch(signal)
    {
        case SIGTERM:
            bc_deinit();
            break;
        case SIGSEGV:
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
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

int main(void)
{
    init_sighandler();

    printf("DEBUG: PID: %d\n", getpid());

    while(1);
    return 0;
}