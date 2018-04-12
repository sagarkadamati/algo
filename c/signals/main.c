#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

volatile char *ptr;
char i;

static void DisasterSignals(int signal)
{
  /* We cannot save the situation, the purpose of catching the signal is
     only to do something clever to aid debugging before we go. */
  write(1, "11\n", 3);
  *ptr = &i;
  write(1, "13\n", 3);
  abort(); /* This should give us the expected core dump (if we survive to this point) */
}

struct sigaction sa = {}; /* initialised to all zero (I vote for GCC style breach of standard here) */

int main()
{
  sa.sa_handler = DisasterSignals;
  sa.sa_flags = /*SA_RESETHAND | */SA_NODEFER;  /* To have or have not */
  sigaction(SIGSEGV, &sa, NULL);

  write(1, "25\n", 3);
  *ptr = 1;
}
