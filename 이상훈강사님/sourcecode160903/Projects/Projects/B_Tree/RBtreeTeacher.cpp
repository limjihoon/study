#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>


#define BLACK		0
#define RED			1

typedef struct _rb_tree rb_tree;
typedef struct _rb_node_y rb_node_y;
typedef struct _rb_node_x rb_node_x;

struct _rb_node_y
{
	int data;
	int color;

	rb_node_y *left;
	rb_node_y *right;
	rb_node_y *parent;
	rb_node_x *root_x;
};
struct _rb_node_x
{
	int data;
	int color;

	rb_node_x *left;
	rb_node_x *right;
	rb_node_x *parent_y;
};
struct _rb_tree
{
	rb_node_y *root;
	rb_node_y *nil;
};

void rb_left_rot(rb_tree **tree, rb_node_y *x)
{
	rb_node_y *y;
	rb_node_y *nil = (*tree)->nil;

	y = x->right;
	x->right = y->left;

	if(y->left != nil)
		y->left->parent = x;

	y->parent = x->parent;

	if(x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}
void rb_right_rot(rb_tree **tree, rb_node_y *y)
{
	rb_node_y *x;
	rb_node_y *nil = (*tree)->nil;

	x = y->left;
	y->left = x->right;

	if(nil != x->right)
		x->right->parent = y;

	x->parent = y->parent;

	if(y->parent->left == y)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}

void rb_tree_ins_helper(rb_tree **tree, rb_node_y *z)
{
	rb_node_y *x;
	rb_node_y *y;
	rb_node_y *nil = (*tree)->nil;

	z->left = z->right = nil;
	y = (*tree)->root;
	x = (*tree)->root->left;

	while(x != nil)
	{
		y = x;

		if(x->data > z->data)
			x = x->left;
		else
			x = x->right;

	}

	z->parent = y;

	if (((*tree)->root == y) || (y->data > z->data))
		y->left = z;
	else
		y->right = z;
}
int sub_print_tree(rb_node_y *root,int x, int y, rb_node_y *nil){
	COORD pos;
	if(root != nil){
		x = sub_print_tree(root->left, x, y+3, nil);
		pos.X = x; pos.Y =y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		if(root->color == RED)
			printf("(%2d)", root->data);
		else
			printf("%4d", root->data);
		x = sub_print_tree(root->right, x+3, y+3, nil);
	}
	return x;
}
void print_tree(rb_tree *tree){
	sub_print_tree(tree->root, 0, 5, tree->nil);
	getchar();
	system("cls");
}

void rb_tree_ins(rb_tree **tree, int data)
{
	rb_node_y *y;
	rb_node_y *x;

	x = (rb_node_y *)malloc(sizeof(rb_node_y));
	x->data = data;

	rb_tree_ins_helper(tree, x);

	x->color = RED;

	while(x->parent->color)
	{
		if(x->parent == x->parent->parent->left)
		{
			y = x->parent->parent->right;

			if(y->color)
			{
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				if(x->parent->right == x)
				{
					x = x->parent;
					rb_left_rot(tree, x);
				}

				x->parent->color = BLACK;
				x->parent->parent->color = RED;

				rb_right_rot(tree, x->parent->parent);
			}
		}
		else
		{
			y = x->parent->parent->left;
			
			if(y->color)
			{
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				if(x->parent->left == x)
				{
					x = x->parent;

					rb_right_rot(tree, x);
				}

				x->parent->color = BLACK;
				x->parent->parent->color = RED;

				rb_left_rot(tree, x->parent->parent);
			}
		}
	}

	(*tree)->root->left->color = BLACK;
}

rb_tree *rb_tree_create(void)
{
	rb_tree *rbtree;
	rb_node_y *tmp;

	rbtree = (rb_tree *)malloc(sizeof(rb_tree));

	tmp = rbtree->nil = (rb_node_y *)malloc(sizeof(rb_node_y));
	tmp->parent = tmp->left = tmp->right = tmp;
	tmp->color = BLACK;
	tmp->data = 0;
	tmp->root_x = 0;

	tmp = rbtree->root = (rb_node_y *)malloc(sizeof(rb_node_y));
	tmp->parent = tmp->left = tmp->right = rbtree->nil;
	tmp->color = BLACK;
	tmp->data = 0;
	tmp->root_x = 0;

	return rbtree;
}

void rb_tree_inorder_print(rb_tree *tree, rb_node_y *x)
{
	rb_node_y *nil = tree->nil;
	rb_node_y *root = tree->root;

	if(x != tree->nil)
	{
		rb_tree_inorder_print(tree, x->left);

		printf("Data = %4i ", x->data);
		printf("Left Data = ");

		if(x->left == nil)
			printf("NULL ");
		else
			printf("%4i ", x->left->data);

		printf("Right Data = ");

		if(x->right == nil)
			printf("NULL ");
		else
			printf("%4i ", x->right->data);

		printf("Parent Data = ");

		if(x->parent == root)
			printf("NULL ");
		else
			printf("%4i ", x->parent->data);

		printf("Color = %4i\n", x->color);

		rb_tree_inorder_print(tree, x->right);
	}
}
void rb_tree_print(rb_tree *tree)
{
	rb_tree_inorder_print(tree, tree->root->left);
}

int data_test(int num1, int num2)
{
	if(num1 > num2)
		return 1;
	else if(num1 < num2)
		return -1;
	else
		return 0;
}
rb_node_y *rb_tree_find(rb_tree *tree, int data)
{
	int tmp;

	rb_node_y *x = tree->root->left;
	rb_node_y *nil = tree->nil;

	if(x == nil)
		return 0;

	tmp = data_test(x->data, data);

	while(tmp != 0)
	{
		if(x->data > data)
			x = x->left;
		else
			x = x->right;

		if(x == nil)
			return 0;

		tmp = data_test(x->data, data);
	}

	return x;
}

rb_node_y *rb_tree_successor(rb_tree *tree, rb_node_y *x)
{
	rb_node_y *y;
	rb_node_y *nil = tree->nil;
	rb_node_y *root = tree->root;

	if(nil != (y = x->right))
	{
		while(y->left != nil)
			y= y->left;

		return y;
	}
	else
	{
		y = x->parent;

		while(y->right == x)
		{
			x = y;
			y = y->parent;
		}

		if(y == root)
			return nil;

		return y;
	}
}

void rb_tree_delete_fixup(rb_tree *tree, rb_node_y *x)
{
	rb_node_y *root = tree->root->left;
	rb_node_y *w;

	while((!x->color) && (root != x))
	{
		if(x->parent->left == x)
		{
			w = x->parent->right;

			if(w->color)
			{
				w->color = BLACK;
				x->parent->color = RED;
				rb_left_rot(&tree, x->parent);
				w = x->parent->right;
			}

			if((!w->right->color) && (!w->left->color))
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if(!w->right->color)
				{
					w->left->color = BLACK;
					w->color = RED;
					rb_right_rot(&tree, w);
					w = x->parent->right;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rb_left_rot(&tree, x->parent);
				x = root;
			}
		}
		else
		{
			w = x->parent->left;

			if(w->color)
			{
				w->color = BLACK;
				x->parent->color = 1;
				rb_right_rot(&tree, x->parent);
				w = x->parent->left;
			}

			if((!w->right->color) && (!w->left->color))
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if(!w->left->color)
				{
					w->right->color = BLACK;
					w->color = RED;
					rb_left_rot(&tree, w);
					w = x->parent->left;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rb_right_rot(&tree, x->parent);
				x = root;
			}
		}
	}

	x->color = BLACK;
}
void rb_tree_delete(rb_tree *tree, rb_node_y *z)
{
	rb_node_y *y;
	rb_node_y *x;
	rb_node_y *nil = tree->nil;
	rb_node_y *root = tree->root;

	y = ((z->left == nil) || (z->right == nil)) ? z : rb_tree_successor(tree, z);
	x = (y->left == nil) ? y->right : y->left;

	if(root == (x->parent = y->parent))
		root->left = x;
	else
	{
		if(y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	if(y != z)
	{
		if(!(y->color))
			rb_tree_delete_fixup(tree, x);

		y->left = z->left;
		y->right = z->right;
		y->parent = z->parent;
		y->color = z->color;
		z->left->parent = z->right->parent = y;

		if(z->parent->left == z)
			z->parent->left = y;
		else
			z->parent->right = y;
		
		free(z);
	}
	else
	{
		if(!(y->color))
			rb_tree_delete_fixup(tree, x);

		free(y);
	}
}


int main(void)
{
	int i;
	int data[20] = { 3, 7, 10, 12, 14, 15, 16, 17, 19, 20, 21,
					23, 26, 28, 30, 35, 38, 39, 41, 47};

	rb_tree *rbtree = NULL;
	rb_node_y *find = NULL;

	rbtree = rb_tree_create();

	for(i=0; i<20; i++){
		rb_tree_ins(&rbtree, data[i]);
//		print_tree(rbtree);
	}
	print_tree(rbtree);
//	rb_tree_print(rbtree);

	find = rb_tree_find(rbtree, 3);

	if(find)
		printf("Get Data at 0x%x\n", find);
	else
		printf("No Data in rb_tree\n");
	
	find = rb_tree_find(rbtree, 3);
	rb_tree_delete(rbtree, find);
	print_tree(rbtree);
	find = rb_tree_find(rbtree, 17);
	rb_tree_delete(rbtree, find);
	print_tree(rbtree);
	find = rb_tree_find(rbtree, 35);
	rb_tree_delete(rbtree, find);
	print_tree(rbtree);
	find = rb_tree_find(rbtree, 30);
	rb_tree_delete(rbtree, find);
	print_tree(rbtree);
	find = rb_tree_find(rbtree, 28);
	rb_tree_delete(rbtree, find);

//	rb_tree_print(rbtree);
	print_tree(rbtree);
	return 0;
}