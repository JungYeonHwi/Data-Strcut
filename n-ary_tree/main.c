#include "nary_tree.h"
#include <stdio.h>

int main() {
	nary_node* tree = NULL,*tree2 = NULL;
	tree = createtree(tree, 3);
	tree2 = createtree(tree2, 59);

	tree = add_i_child(tree, 3, 2, 1);
	tree = add_i_child(tree, 3, 0, 2);
	tree = add_i_child(tree, 3, 1, 4);

	tree = add_i_child(tree, 3, 0, 6);

	tree = add_i_child(tree, 2, 0, 5);
	tree = add_i_child(tree, 2, 0, 7);
	tree = add_i_child(tree, 1, 0, 9);
	preorder(tree); printf("\n");
	//3 6 2 7 5 4 1 9

	tree = delete_i_child(tree, 3, 1);
	preorder(tree); printf("\n");
	//3 6 4 1 9

	tree2 = add_i_child(tree2, 59, 0, 41);
	tree2 = add_i_child(tree2, 59, 1, 77);
	tree2 = add_i_child(tree2, 59, 2, 83);

	tree2 = add_i_child(tree2, 41, 0, 94);
	tree2 = add_i_child(tree2, 41, 0, 28);
	tree2 = add_i_child(tree2, 41, 1, 10);

	tree2 = add_i_child(tree2, 77, 0, 46);
	tree2 = add_i_child(tree2, 77, 0, 32);
	tree2 = add_i_child(tree2, 77, 0, 53);

	tree2 = add_i_child(tree2, 83, 2, 65);
	tree2 = add_i_child(tree2, 83, 0, 31);
	tree2 = add_i_child(tree2, 83, 0, 12);
	tree2 = add_i_child(tree2, 83, 2, 20);

	tree2 = add_i_child(tree2, 1, 0, 3);	//No parent node	-> print error
	tree2 = add_i_child(tree2, 83, 0, 1);	//already have n(4) children	-> print error
	tree2 = add_i_child(tree2, 83, 5, 5);	//i >= n(4)		-> print error

	tree2 = delete_i_child(tree2, 83, 1);
	tree2 = add_i_child(tree2, 46, 0, 13);
	preorder(tree2); printf("\n");
	// 59 41 28 10 94 77 53 32 46 13 83 12 20 65

	tree2 = delete_i_child(tree2, 77, 1);
	tree2 = delete_i_child(tree2, 77, 2);	//Exceed child num -> print error
	preorder(tree2); printf("\n");
	// 59 41 28 10 94 77 53 46 13 83 12 20 65

	printf("Height of 46: %d\n", height_node(tree2, 46));	// 1
	printf("Height of 94: %d\n", height_node(tree2, 94));	// 0
	printf("Height of 5: %d\n", height_node(tree2, 5));		// No existing node	-> print error and return -1
	printf("Height of Tree: %d\n\n", height_tree(tree2));	// 3(height of root node(59))

	printf("Depth of 46: %d\n", depth_node(tree2,46));		// 2
	printf("Depth of 59: %d\n", depth_node(tree2, 59));		// 0
	printf("Depth of 5: %d\n", depth_node(tree2, 5));		// No existing node -> print error and return -1
	printf("Depth of Tree: %d\n\n", depth_tree(tree2));		// 3(depth of leaf node(13))
	
	printf("Child Rank of 65: %d\n", child_rank(tree2, 65));	// 2
	printf("Child Rank of 46: %d\n", child_rank(tree2, 46));	// 1
	printf("Child Rank of 59: %d\n", child_rank(tree2, 59));	// -1(Root node)
	printf("Child Rank of 13: %d\n", child_rank(tree2, 13));	// 0
	printf("Child Rank of 1: %d\n\n", child_rank(tree2, 1));	//No existing node -> print error and return -1
	
	printf("Select 1th child of 41: %d\n", child_select(tree2, 41,1));		// 10
	printf("Select 1th child of 77: %d\n", child_select(tree2, 77,1));		// 46
	printf("Select 0th child of 83: %d\n", child_select(tree2, 83,0));		// 12
	printf("Select 0th child of 13: %d\n", child_select(tree2, 13,0));		//No have child node -> print error and return -1
	printf("Select 0th child of 5: %d\n\n", child_select(tree2, 5,0));		//No existing node -> print error and return -1

	binarynode* B1 = lcps(tree), *B2=lcps(tree2);
	print_preorder(B1); printf("\n");
	//1 9 4 6
	print_inorder(B1); printf("\n\n");
	//9 1 4 6
	print_preorder(B2);	printf("\n");
	//83 65 20 12 77 46 13 53 41 94 10 28
	print_inorder(B2);	printf("\n");
	//65 20 12 83 13 46 53 77 94 10 28 41
	
	return 0;
}