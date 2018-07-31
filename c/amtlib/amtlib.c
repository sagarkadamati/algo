#include "amtlib.h"

struct amtdata amtdata;

void begin()
{
	struct stat statbuf;

	amtdata.ofile_fd  = open("./original/amtlib.dll", 'r');
	amtdata.cfile_fd  = open("./crack/amtlib.dll", 'r');
	amtdata.finial = open("./finial/amtlib.dll", 'w', O_CREAT | S_IRWXU);

	fstat(amtdata.ofile_fd, &statbuf);
	amtdata.ofile_size = statbuf.st_size;
	fstat(amtdata.cfile_fd, &statbuf);
	amtdata.cfile_size = statbuf.st_size;

	amtdata.ofile_data = mmap(0, amtdata.ofile_size, PROT_READ | PROT_WRITE, MAP_SHARED, amtdata.ofile_fd, 0);
	amtdata.cfile_data = mmap(0, amtdata.cfile_size, PROT_READ | PROT_WRITE, MAP_SHARED, amtdata.cfile_fd, 0);
}

void end()
{
	munmap(amtdata.ofile_data, amtdata.ofile_size);
	munmap(amtdata.cfile_data, amtdata.cfile_size);

	close(amtdata.ofile_fd);
	close(amtdata.cfile_fd);
	close(amtdata.finial);
}

void process()
{
	unsigned int i = 0;

	printf("----------------------------------------\n");
	printf("| %8s  :  %8s  ->  %8s  |\n", "Offset", "Original", "Modified");
	printf("----------------------------------------\n");
	for (i = 0; i < amtdata.ofile_size; i++)
	{
		if (amtdata.ofile_data[i] != amtdata.cfile_data[i]) {
			printf("| 0x%08X: 0x%08X -> 0x%08X |\n", i, amtdata.ofile_data[i], amtdata.cfile_data[i]);

			write(amtdata.finial, &amtdata.cfile_data[i], 1);
		}
		else
		{
			write(amtdata.finial, &amtdata.ofile_data[i], 1);
		}
	}
	printf("----------------------------------------\n");
}