#include "test.h"

int main()
{
	rb_node node;
	rb_node* rnode = &node;
	rb_node* tnode;

	init_rb_node(rnode);

	tnode = get_rb_node(rnode, 7);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 5);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 2);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 3);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 1);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 4);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 6);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 8);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 9);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 10);
	tnode->data = tnode->key * 3;

	tnode = get_rb_node(rnode, 1);
	printf("Key: %d, Data: %d\n", tnode->key, tnode->data);

	tnode = get_rb_node(rnode, 7);
	printf("Key: %d, Data: %d\n", tnode->key, tnode->data);

	tnode = get_rb_node(rnode, 3);
	printf("Key: %d, Data: %d\n", tnode->key, tnode->data);

	clear_rb_node(rnode, 5);
	clear_rb_node(rnode, 1);
	clear_rb_node(rnode, 2);
	clear_rb_node(rnode, 3);
	clear_rb_node(rnode, 4);
	clear_rb_node(rnode, 6);
	clear_rb_node(rnode, 7);
	clear_rb_node(rnode, 8);
	clear_rb_node(rnode, 9);
	clear_rb_node(rnode, 10);

	return 0;
}