#include "main.h"
#include "../src/bc_cmd_tracker.h"

// static void full_write(int fd, const char *buf, size_t len)
// {
//         while (len > 0) {
//                 ssize_t ret = write(fd, buf, len);

//                 if ((ret == -1) && (errno != EINTR))
//                         break;

//                 buf += (size_t) ret;
//                 len -= (size_t) ret;
//         }
// }

// void print_backtrace(void)
// {
//         static const char start[] = "BACKTRACE ------------\n";
//         static const char end[] = "----------------------\n";

//         void *bt[1024];
//         int bt_size;
//         char **bt_syms;
//         int i;

//         bt_size = backtrace(bt, 1024);
//         bt_syms = backtrace_symbols(bt, bt_size);
//         full_write(STDERR_FILENO, start, strlen(start));
//         for (i = 1; i < bt_size; i++) {
//                 size_t len = strlen(bt_syms[i]);
//                 full_write(STDERR_FILENO, bt_syms[i], len);
//                 full_write(STDERR_FILENO, "\n", 1);
//         }
//         full_write(STDERR_FILENO, end, strlen(end));
//     free(bt_syms);
// }

// void sighandlers(int signal)
// {
//     switch(signal)
//     {
//         case SIGTERM:
//             // bc_deinit();
//             break;
//         case SIGSEGV:
//             // bc_deinit();
// 			// print_backtrace();
//             break;
//         case SIGINT:
//             // bc_deinit();
// 			// print_backtrace();
//             break;
//         case SIGILL:
//             // bc_deinit();
// 			// print_backtrace();
//             break;
//         case SIGABRT:
//             // bc_deinit();
// 			// print_backtrace();
//             break;
//         case SIGFPE:
//             // bc_deinit();
// 			// print_backtrace();
//             break;
//         default:
//             break;
//             // bc_deinit();
// 			// print_backtrace();
//     }

//     abort();
// }

// static void init_sighandler()
// {
//     sa.sa_handler = sighandlers;
//     sa.sa_flags = SA_SIGINFO;
//     // sa.sa_flags = /*SA_RESETHAND | */SA_NODEFER;  /* To have or have not */
//     sigaction(SIGTERM, &sa, NULL);
//     sigaction(SIGSEGV, &sa, NULL);
//     sigaction(SIGINT, &sa, NULL);
//     sigaction(SIGILL, &sa, NULL);
//     sigaction(SIGABRT, &sa, NULL);
//     sigaction(SIGFPE, &sa, NULL);
// }

int main(void)
{
    // init_sighandler();

    printf("DEBUG: PID: %d\n", getpid());

	bc_update_cmd(ENTER, CMD1, 0);
	bc_update_cmd(EXIT, CMD1, 0);
	bc_update_cmd(ENTER, CMD2, 0);
	bc_update_cmd(EXIT, CMD2, -1);

    // while(1);
    return 0;
}