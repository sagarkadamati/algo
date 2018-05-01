#include "rb_tree.h"

rb_node *new_rb_node()
{
	return calloc(1, sizeof(rb_node));
}

void free_rb_node(rb_node *tnode)
{
	free(tnode);
}

rb_node* uncle(rb_node* tnode)
{
	if (is_rchild_of_parent(parent(tnode)))
		tnode = lchild(gparent(tnode));

	if (is_lchild_of_parent(parent(tnode)))
		tnode = rchild(gparent(tnode));

	return tnode;
}

void fix_voilations(rb_node* root, rb_node* child)
{
	if (root == child)
		color(child) = BLACK;
	else
	{
		if(is_red(uncle(child)))
		{
			color(parent(child)) = BLACK;
			color(uncle(child))  = BLACK;
		}
		else
		{
			if(is_line(child))
			{
				if(is_lchild_of_parent(parent(child)))
					rrotate(gparent(child));
				else
					lrotate(gparent(child));

				recolor(gparent(child));
				recolor(parent(child));
			}
			else
			{
				if(is_lchild_of_parent(child))
					rrotate(parent(child));
				else
					lrotate(parent(child));
			}
		}
	}
}

void print_level(rb_node *rnode, int level)
{
	if (rnode)
	{
		print_level(lchild(rnode), level++);
		printf(" %d ", key(rnode));
		print_level(rchild(rnode), level++);
	}
}

void bfs(rb_node* root)
{
	int level = 0;

	print_level(root, level);
}

rb_node *get_rb_node(rb_node *root, int key)
{
	rb_node *tnode = root;
	rb_node *pnode = root;
	int tkey;

	while (tnode)
	{
		tkey = key(tnode);
		if (key == tkey)
			break;

		pnode = tnode;
		if (key < tkey)
			tnode = lchild(tnode);
		else
			tnode = rchild(tnode);
	}

	if (!tnode)
	{
		tnode = new_rb_node();

		init_rb_node(tnode);
		tnode->key = key;

		if (!root)
			root = tnode;
		else if (key < tkey)
			link_lchild(pnode, tnode);
		else
			link_rchild(pnode, tnode);

		fix_voilations(root, tnode);
	}

	return tnode;
}

rb_node* get_least_key_node(rb_node* tnode)
{
	while(lchild(tnode))
		tnode = lchild(tnode);

	return tnode;
}

void clear_rb_node(rb_node* root, int key)
{
	rb_node *tnode = get_rb_node(root, key);
	rb_node *rnode;

	if (lchild(tnode)) {
		if (rchild(tnode)) {
			rnode = get_least_key_node(rchild(tnode));

			key(tnode) = key(rnode);
			tnode->data = rnode->data;
			tnode = rnode;

			if (rchild(tnode))
				replace_parent_child(tnode, rchild(tnode));
		}
		else
			replace_parent_child(tnode, lchild(tnode));
	}
	else if (rchild(tnode))
		replace_parent_child(tnode, rchild(tnode));

	fix_voilations(root, parent(tnode));

	deinit_rb_node(tnode);
	free_rb_node(tnode);
}

rb_node *insert_rb_node(rb_node *root, int key, int data)
{
	rb_node *tnode = get_rb_node(root, key);
	tnode->data = data;

	return tnode;
}