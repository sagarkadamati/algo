#include <stdio.h>

int main(int argc, char** argv)
{
	char* FileName = "C:\Users\Sagar\Desktop\amtlib.dll";
	File *fd = fopen(FileName, "r");

	printf("Testing\n");

	close(fd);
	return 0;
}