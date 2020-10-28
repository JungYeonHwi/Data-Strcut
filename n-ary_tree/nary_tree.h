#ifndef __NARY_TREE__
#define __NARY_TREE__

#define n 4

typedef struct nary_node {
	int key;
	struct nary_node* children[n];
}nary_node;
typedef struct binarynode {
	int key;
	struct binarynode* leftchild;
	struct binarynode* rightchild;
}binarynode;
void print_preorder(binarynode* root);
void print_inorder(binarynode* root);
void print_error();
nary_node* createtree(nary_node* root, int key);
nary_node* key_node(nary_node* root, int key);
nary_node* add_i_child(nary_node* root, int parent_key, int i, int key);
nary_node* delete_i_child(nary_node* root, int parent_key, int i);
int height_node(nary_node* root, int node_value);
int height_tree(nary_node* root);
int depth_node(nary_node* root, int node_value);
int depth_tree(nary_node* root);
int child_rank(nary_node* root, int node_value);
int child_select(nary_node* root, int parent_key, int i);
binarynode* lcps(nary_node* root);
void preorder(nary_node * root);
#endif