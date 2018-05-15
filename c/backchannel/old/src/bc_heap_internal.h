#ifndef __BC_HEAP_INTERNAL__
#define __BC_HEAP_INTERNAL__

struct bc_struct_heap_tracker
{
	int enable;
	void (*malloc)(void *ptr, int size, const char *func, int line);
	void (*calloc)(void *ptr, int size, const char *func, int line);
	void (*free)(void *ptr, const char *func, int line);
};
extern struct bc_struct_heap_tracker heap_tracker_cbs;
struct bc_struct_heap_tracker heap_tracker_cbs;

#define bc_malloc(_size) ({ \
            void *p; \
            p = malloc(_size); \
            if (heap_tracker_cbs.enable) \
              heap_tracker_cbs.malloc(p, _size, __func__, __LINE__); \
            p; \
        })
#define bc_calloc(_count, _size) ({ \
            void *p; \
            p = calloc(_count, _size); \
            if (heap_tracker_cbs.enable) \
              heap_tracker_cbs.calloc(p, _size * _count, __func__, __LINE__); \
            p; \
        })
#define bc_free(_ptr) ({ \
            if (heap_tracker_cbs.enable) \
              heap_tracker_cbs.free(_ptr, __func__, __LINE__); \
			free(_ptr); \
        })

#endif /* __BC_HEAP_INTERNAL__ */