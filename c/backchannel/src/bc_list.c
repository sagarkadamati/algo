#include "bc_list.h"

void list_init(list_node *node)
{
	node->next = node;
	node->prev = node;
}

void list_add(list_node *head, list_node *node)
{
	list_attach(node, head->next);
	list_attach(head, node);
}

void list_add_tail(list_node *head, list_node *node)
{

}

void list_remove(list_node *node) {
	list_attach(node->prev, node->next);
}
