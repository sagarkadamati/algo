#ifndef __BC_PRINT__
#define __BC_PRINT__

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define LINE_BUFFER 100

void bc_print(char* ptr, const char *fmt, ...);
int str_to_long(const char *str, long *value);

#endif /*__BC_PRINT__ */
