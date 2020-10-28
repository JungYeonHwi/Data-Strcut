#include "xcode.h"
#include <stddef.h>
#include <stdlib.h>
int main() {
	
    //Initialize root node of Xtree
    xnode* root = NULL;
	
    //Returns a tree consisting of a substring of the input file
	root=construct_xtree("input.txt");
	
    //Generate "codebook.txt" file arranged in lexicographical order
	codebook(root);
	
    //Compresses input files with the xtree and generate "output.txt"
	compress_x(root, "input.txt");
	
    //Decompress the files and create "input_original.txt" file(equivalent to the input file)
	decompress_x("output.txt", "codebook.txt");
	
	for (int i = 0; i < code_size; i++)
		free(code_book[i]);

	/*
	 When b of the Z-Pumsb2 is 16, the codebook has 2^b(65536) items.
	 							   the length of the "output.txt" is 12014542.
								   the length of the "input_original.txt" is 1742466020(The length and content of the file must be same)

	 When b of the "0001110011" is 2, the codebook has 2^b(4) items.
	 								  the length of the "output.txt" is 13.
									  the length of the "input_original.txt" is 14(same as above)
	 */
}
