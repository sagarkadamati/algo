#ifndef __AMTLIB__
#define __AMTLIB__

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct amtdata {
	unsigned int ofile_fd;
	unsigned int cfile_fd;
	unsigned int finial;

	unsigned int ofile_size;
	unsigned int cfile_size;

	char* ofile_data;
	char* cfile_data;
};

void begin(void);
void process(void);
void end(void);

int main(void)
{
	begin();
	process();
	end();

	return 0;
}

#endif /* __AMTLIB__*/
