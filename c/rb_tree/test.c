#include "test.h"

int main()
{
	// rb_node node;
	rb_node* rnode = NULL;
	rb_node* tnode;

	tnode = get_rb_node(rnode, 7);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 7\n");

	tnode = get_rb_node(rnode, 5);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 5\n");

	tnode = get_rb_node(rnode, 2);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 2\n");

	tnode = get_rb_node(rnode, 3);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 3\n");

	tnode = get_rb_node(rnode, 1);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 1\n");

	tnode = get_rb_node(rnode, 4);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 4\n");

	tnode = get_rb_node(rnode, 6);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 6\n");

	tnode = get_rb_node(rnode, 8);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 8\n");

	tnode = get_rb_node(rnode, 9);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 9\n");

	tnode = get_rb_node(rnode, 10);
	tnode->data = tnode->key * 3;

	bfs(rnode);
	printf(" - Insert 10\n");

	tnode = get_rb_node(rnode, 1);
	printf("\nKey: %d, Data: %d\n", tnode->key, tnode->data);

	tnode = get_rb_node(rnode, 7);
	printf("Key: %d, Data: %d\n", tnode->key, tnode->data);

	tnode = get_rb_node(rnode, 3);
	printf("Key: %d, Data: %d\n", tnode->key, tnode->data);

	clear_rb_node(rnode, 5);
	clear_rb_node(rnode, 7);
	printf("\n");
	bfs(rnode);

	clear_rb_node(rnode, 3);
	printf("\n");
	bfs(rnode);

	clear_rb_node(rnode, 2);
	printf("\n");
	bfs(rnode);

	clear_rb_node(rnode, 1);
	printf("\n");
	bfs(rnode);

	clear_rb_node(rnode, 4);
	clear_rb_node(rnode, 6);
	clear_rb_node(rnode, 8);
	clear_rb_node(rnode, 9);
	clear_rb_node(rnode, 10);

	return 0;
}