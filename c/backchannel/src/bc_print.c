#include "bc_print.h"

void bc_print(char* ptr, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vsnprintf(ptr, LINE_BUFFER, fmt, args);
	va_end(args);
}
