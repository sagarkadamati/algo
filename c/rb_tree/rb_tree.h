#ifndef __RB_TREE__
#define __RB_TREE__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

enum color {
	RED,
	BLACK,
};

typedef struct rb_node {
	struct rb_node *parent;
	struct rb_node *rchild;
	struct rb_node *lchild;

	int color;

	int key;
	int data;
} rb_node;

#define gparent(_node) _node->parent->parent
#define parent(_node)  _node->parent
#define lchild(_node)  _node->lchild
#define rchild(_node)  _node->rchild
#define color(_node)   _node->color
#define key(_node)     _node->key

#define is_lchild_of_parent(_rb_node)				\
		(lchild(parent(_rb_node)) == _rb_node)

#define is_rchild_of_parent(_rb_node)				\
		(rchild(parent(_rb_node)) == _rb_node)

#define is_red(_node)								\
		(color(_node) == RED)

#define is_root(_rb_node) (!parent(_rb_node))

/*
#define uncle(_node) ({								\
		if (is_rchild_of_parent(parent(_node)))		\
			lchild(gparent(_node));					\
		if (is_lchild_of_parent(parent(_node)))		\
			rchild(gparent(_node));					\
	})
*/

// #define is_line(_rb_node) 0

#define rrotate(_rb_node)
#define lrotate(_rb_node)
#define recolor(_rb_node)

#define init_rb_node(_rb_node) ({ 					\
		parent(_rb_node) = NULL;  					\
		rchild(_rb_node) = NULL;  					\
		lchild(_rb_node) = NULL;  					\
		color(_rb_node)  = RED;   					\
	})

#define deinit_rb_node(_rb_node) ({					\
		if (is_rchild_of_parent(_rb_node))			\
			rchild(parent(_rb_node)) = NULL;		\
		else if (is_lchild_of_parent(_rb_node))		\
			lchild(parent(_rb_node)) = NULL;		\
	})

#define replace_parent_child(_rb_node, _child) ({	\
		if (is_rchild_of_parent(_rb_node))			\
			rchild(parent(_rb_node)) = _child;		\
		else if (is_lchild_of_parent(_rb_node))		\
			lchild(parent(_rb_node)) = _child;		\
	})

#define link_lchild(_parent, _child) ({ 			\
		lchild(_parent) = _child; 					\
		parent(_child)  = _parent; 					\
	})

#define link_rchild(_parent, _child) ({ 			\
		rchild(_parent) = _child; 					\
		parent(_child)  = _parent; 					\
	})

rb_node* new_rb_node(void);
rb_node* get_rb_node(rb_node* root, int key);
rb_node* insert_rb_node(rb_node* root, int key, int data);
rb_node* get_least_key_node(rb_node* tnode);
void free_rb_node(rb_node *tnode);
void fix_voilations(rb_node* root, rb_node* tnode);
void clear_rb_node(rb_node* root, int key);

void print_level(rb_node *rnode, int level);
void bfs(rb_node* root);

#endif /* __RB_TREE__ */