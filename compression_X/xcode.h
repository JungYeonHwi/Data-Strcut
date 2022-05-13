#ifndef __XCODE__
#define __XCODE__

#define MAX_STRING 1000000000
#define b 2 
#define code_size (1<<b)

/*Array which stores the codebook*/
char* code_book[code_size+5];

typedef struct xnode {
	char* string;
	double p;
	struct xnode* leftchild;
	struct xnode* rightchild;
}xnode;

void print_error();
void codebook(xnode* xtree);
xnode* construct_xtree(char* file);
void compress_x(xnode* xtree, char* file);
void decompress_x(char* output, char* codebook);

#endif
