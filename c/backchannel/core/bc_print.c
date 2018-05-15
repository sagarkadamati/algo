#include "bc_print.h"

void bc_print(char* ptr, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vsnprintf(ptr, LINE_BUFFER, fmt, args);
	va_end(args);
}

int str_to_long(const char *str, long *value)
{
    char *tstr;

    errno = 0;
    *value = strtol(str, &tstr, 0);
    if (tstr == str || *tstr != '\0' || ((*value == LONG_MIN || *value == LONG_MAX) && errno == ERANGE))
        return 0;

    return 1;
}