#ifndef __BC_LIST__
#define __BC_LIST__

typedef struct struct_list_node {
	struct struct_list_node *next;
	struct struct_list_node *prev;
} list_node;

#ifndef container_of
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#define list_attach(_prev, _next) \
	_prev->next = _next; \
	_next->prev = _prev;

void list_init(list_node *node);
void list_add(list_node *head, list_node *node);
void list_add_tail(list_node *head, list_node *node);
void list_remove(list_node *node);

#endif /* __BC_LIST__ */