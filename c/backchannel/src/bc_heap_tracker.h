#ifndef __BC_HEAP_TRACKER__
#define __BC_HEAP_TRACKER__

#include "bc_os_headers.h"

#define LOG_BUFFER_LENGTH   100
#define HEAP_TRACKER        "bc_heap"

int bc_heap_tracker_fd;
void* bc_heap_tracker_data;

struct bc_struct_heap_tracker
{
  void (*malloc)(void *ptr, const char *func, int line);
  void (*calloc)(void *ptr, const char *func, int line);
  void (*free)(void *ptr, const char *func, int line);
};

void bc_init_heap_tracker(void);
void bc_update_heap_tracker(void);
void bc_malloc_probe_pt(void *ptr, const char *func, int line);
void bc_calloc_probe_pt(void *ptr, const char *func, int line);
void bc_free_probe_pt(void *ptr, const char *func, int line);
int  bc_print_allocations(const char *fmt, ...);

#ifndef __BC_PROCESS_HEADERS__
struct bc_struct_heap_tracker heap_tracker_cbs;
#endif /* __BC_PROCESS_HEADERS__ */

#endif /* __BC_HEAP_TRACKER__ */