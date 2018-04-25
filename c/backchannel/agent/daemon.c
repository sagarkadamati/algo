#include "daemon.h"

void run_as_background()
{
	pid_t process_id = 0;
	pid_t sid = 0;

	// Create child process
	process_id = fork();
	if (process_id < 0)
	{
		// Indication of fork() failure
		printf("fork failed!\n");
		exit(1); // return failure in exit status
	}

	// Parent Process. Need to kill it.
	if (process_id > 0)
	{
		printf("Server Started with PID %d \n", process_id);
		exit(0); // return success in exit status
	}

	// Unmask the file mode
	umask(0);

	// Set New Session
	sid = setsid();
	if (sid < 0)
	{
		exit(1); // return failure
	}

	// Change the current working directory to root.
	chdir("/");

	// Close stdin. stdout and stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}