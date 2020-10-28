#include "nary_tree.h"
#include <stdio.h>
#include <stdlib.h>
/************************ PREDEFINED FUNCTIONS (DO NOT CHANGE)*******************************/
/*
Print the binary tree according to the preorder traversal
*/
void print_preorder(binarynode* root) {
	printf("%d ", root->key);
	if (root->leftchild != NULL) print_preorder(root->leftchild);
	if (root->rightchild != NULL) print_preorder(root->rightchild);
}

/*
Print the binary treee according to the inorder traversal
*/
void print_inorder(binarynode* root) {
	if (root->leftchild != NULL) print_inorder(root->leftchild);
	printf("%d ", root->key);
	if (root->rightchild != NULL) print_inorder(root->rightchild);
}

/*
Print error message
*/
void print_error() {
	printf("Error\n");
}
/***************************************************************************************/

/*
Create and return a tree with single root node whose key value is key.
All the children are initialized to NULL
If root already exists, return root
*/
nary_node* createtree(nary_node* root, int key) {
//implement your code
	root = (nary_node*)malloc(sizeof(nary_node));

	root->key = key;

	for (int i = 0; i < n; i++)
	{
		root->children[i] = NULL;
	}
	
	return root;
}

/*
Return a node with corresponding key value
If such node doesn't exist, return NULL
*/
nary_node* key_node(nary_node* root, int key) {
//implement your code
	if (root->key == key)
		return root;
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (root->children[i] != NULL)
			{
				nary_node* tmp = key_node(root->children[i], key);

				if (tmp != NULL)	return tmp;
			}
		}
	}

	return NULL;
}

/*
Insert a node with the key value
as the i-th child of the node whose key value is parent_key
If such (parent) node doesn't exist, tree is already full, or index (i) exceeds the degree, call error function and return root
*/
nary_node* add_i_child(nary_node* root, int parent_key, int i, int key) {
	//implement your code
	if (n <= i)
	{
		print_error();
		return root;
	}
	else
	{
		nary_node* parent_node = key_node(root, parent_key);

		if (parent_node == NULL)
		{
			print_error();
			return root;
		}

		if (parent_node->children[n - 1] != NULL)
		{
			print_error();
			return root;
		}

		nary_node* new_node = NULL;
		new_node = createtree(new_node, key);

		if (parent_node->children[i] == NULL) {
			parent_node->children[i] = new_node;
		}
		else {
			for (int j = n - 1; j > i; --j) {
				parent_node->children[j] = parent_node->children[j - 1];
			}
			parent_node->children[i] = new_node;
		}

		for (int num = i; num > 0; num--)
		{
			if (parent_node->children[num - 1] == NULL)
			{
				parent_node->children[num - 1] = parent_node->children[num];
				parent_node->children[num] = NULL;
			}
		}

	}
	return root;
}

/*
Delete the i-th child of the node with parent_key (with all its descendants) and deallocating memory, by make it as NULL
If the node doesn't exist or index is out of range, call error function and return root
*/
nary_node* delete_i_child(nary_node* root, int parent_key, int i) {
//implement your code
	nary_node* new_node = NULL;
	new_node = key_node(root, parent_key);

	if (new_node != NULL)
	{
		if (new_node->children[i] != NULL)
		{
			free(new_node->children[i]);
			new_node->children[i] = NULL;
		}

		else
		{
			print_error();
			return root;
		}

		for (int num = i + 1; num < n; num++)
		{
			if (new_node->children[num - 1] == NULL)
			{
				new_node->children[num - 1] = new_node->children[num];
				new_node->children[num] = NULL;
			}
		}

		return root;
	}

	else
	{
		print_error();
		return root;
	}
}

/*
Return the height of the node whose key value is node_value
If the node doesn't exist, call error function and return -1
*/
int height_node(nary_node* root, int node_value) {
	//implement your code

	nary_node* new_node = key_node(root, node_value);

	if (new_node == NULL)
	{
		print_error();
		return -1;
	}

	return height_tree(new_node);
}

/*
Return the height of a tree 
*/
int height_tree(nary_node* root) {
	//implement your code
	int height = 0;

	for (int i = 0; i < n; i++)
	{
		if (root->children[i] != NULL) {
			int tmp = height_tree(root->children[i]);
			tmp++;
			if (tmp > height)
			{
				height = tmp;
			}
		}
	}
	return height;
}

/*
Calculate the depth of the node whose key value is node_value
If the node doesn't exist, call error function and return -1
*/
int depth_node(nary_node* root, int node_value) {
	//implement your code
	nary_node* cur_node = root;

	int depth = 0;

	if (node_value == root->key)
	{
		depth = 0;
	}

	if (key_node(root, node_value) == NULL)
	{
		print_error();
		return -1;
	}

	while (cur_node != node_value)
	{
		for (int i = 0; i < n; i++)
		{
			if (cur_node->children[i] != NULL)
			{
				if (key_node(cur_node->children[i], node_value) != NULL)
				{
					cur_node = cur_node->children[i];
					break;
					break;
				}
			}
		}
		depth++;
	}
	return depth;
}

/*
Calculate the depth of a tree
*/
int depth_tree(nary_node* root) {
	//implement your code
	int depth = 0;

	for (int i = 0; i < n; i++)
	{
		if (root->children[i] != NULL) {
			int tmp = depth_tree(root->children[i]);
			tmp++;
			if (tmp > depth)
			{
				depth = tmp;
			}
		}
	}
	return depth;
}

/*
Return the child rank of the node whose key value is node_value
If the node doesn't exist, call error function and return -1
*/
int child_rank(nary_node* root, int node_value) {
//implement your code
	nary_node* cur_parent_node = root;

	int rank = -1;

	if (node_value == root->key)
	{
		print_error();
		return -1;
	}

	if (key_node(root, node_value) == NULL)
	{
		print_error();
		return -1;
	}
	
	while (rank == -1)
	{
		for (int i = 0; i < n; i++)
		{
			if (cur_parent_node->children[i] != NULL)
			{
				if (cur_parent_node->children[i]->key == node_value)
				{
					rank = i;
					break;
				}

				if (key_node(cur_parent_node->children[i], node_value) != NULL)
				{
					cur_parent_node = cur_parent_node->children[i];
					break;
				}
			}
		}
	}

	return rank;
}

/*
Return the i-th child of the node whose key value is parent_key
If the node doesn't exist, call error function and return -1
*/
int child_select(nary_node* root, int parent_key, int i) {
//implement your code
	int count = 0;

	if (i >= n)
	{
		print_error();
		return -1;
	}

	nary_node* parent_node = key_node(root, parent_key);
	

	if (parent_node == NULL)
	{
		print_error();
		return -1;
	}

	if (parent_node->children[i] == NULL)
	{
		print_error();
		return -1;
	}

	else
	{
		nary_node* children_node = key_node(parent_node, parent_node->children[i]->key);

		if (children_node != NULL)
		{
			return parent_node->children[i]->key;
		}

		else
		{
			print_error();
			return -1;
		}
	}
}

/*
Print the tree according to the preorder traversal
*/
void preorder(nary_node* root) {
//implement your code

	printf("%d ", root->key);

	for (int i = 0; i < n; i++)
	{
		if (root->children[i] != NULL)
			preorder(root->children[i]);
	}
}

/*
Convert the nary tree to the binary tree by lcps (last child previous sibling)
*/
binarynode* lcps(nary_node* root) {
	//implement your code
	if (root->key == NULL)	return NULL;
}