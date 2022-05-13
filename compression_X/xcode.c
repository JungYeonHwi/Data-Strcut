#define _CRT_SECURE_NO_WARNINGS
#include "xcode.h"
#include "stack.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************Pre-defined functions : TO NOT TOUCH ******************************************/

/*Print error message*/
void print_error() {
	printf("ERROR\n");
	return;
}


/***********************************************************************************************************/


/*Read the given 'file' and return the corresponding Xtree.*/
xnode* construct_xtree(char* file) {
	//Implement your function in here

	FILE* fp = NULL;
	fp = fopen(file, "r");

	xnode* Xtree = NULL;

	int string_size = 0;
	int zero_size = 0;
	int one_size = 0;

	if (fp != NULL)
	{
		char* buffer = malloc(sizeof(char) * MAX_STRING);

		fgets(buffer, sizeof(buffer), fp);

		string_size = strlen(buffer);

		for (int i = 0; i < string_size; i++)
		{
			if (buffer[i] == '0')
			{
				zero_size++;
			}

			else if (buffer[i] == '1')
			{
				one_size++;
			}

			else
			{
				print_error();
				return NULL;
			}
		}

		free(buffer);
	}

	Xtree = (xnode*)malloc(sizeof(xnode));

	int leafNodeCount = 0;

	double d0, d1;

	d0 = (double)zero_size / (double)string_size;
	d1 = (double)one_size / (double)string_size;

	heap h;
	create(&h);

	xnode* LeftChild = (xnode*)malloc(sizeof(xnode));
	xnode* RightChild = (xnode*)malloc(sizeof(xnode));
	xnode* parent;

	LeftChild->string = malloc(sizeof(char) * 2);
	RightChild->string = malloc(sizeof(char) * 2);

	LeftChild->leftchild = NULL;
	LeftChild->rightchild = NULL;
	RightChild->leftchild = NULL;
	RightChild->rightchild = NULL;

	LeftChild->string[0] = '0';
	LeftChild->string[1] = '\0';
	RightChild->string[0] = '1';
	RightChild->string[1] = '\0';

	LeftChild->p = d0;
	RightChild->p = d1;

	Xtree->leftchild = LeftChild;
	Xtree->rightchild = RightChild;

	insert(&h, Xtree->leftchild);
	insert(&h, Xtree->rightchild);

	leafNodeCount = 2;
	 
	while (leafNodeCount != code_size)
	{
		parent = deletemin(&h);

		int parent_string_size = strlen(parent->string);
		int child_string_size = parent_string_size + 2;

		xnode* LeftChild = (xnode*)malloc(sizeof(xnode));
		xnode* RightChild = (xnode*)malloc(sizeof(xnode));

		LeftChild->string = malloc(sizeof(char) * child_string_size);
		RightChild->string = malloc(sizeof(char) * child_string_size);

		LeftChild->leftchild = NULL;
		LeftChild->rightchild = NULL;
		RightChild->leftchild = NULL;
		RightChild->rightchild = NULL;

		strcpy(LeftChild->string, parent->string);
		strcat(LeftChild->string, "0");
		LeftChild->string[child_string_size - 1] = '\0';

		strcpy(RightChild->string, parent->string);
		strcat(RightChild->string, "1");
		RightChild->string[child_string_size - 1] = '\0';

		LeftChild->p = parent->p * d0;
		RightChild->p = parent->p * d1;

		parent->leftchild = LeftChild;
		parent->rightchild = RightChild;

		insert(&h, parent->leftchild);
		insert(&h, parent->rightchild);

		leafNodeCount++;
	}

	return Xtree;
}

/*
 Construct a codebook array w.r.t. a given Xtree (xtree is the root node of Xtree).
  After that, Create a "codebook.txt" file based on that array
 */
void codebook(xnode* xtree) {
//Implement your function in here
	
	Stack s;
	xnode* visited_node = NULL;

	for (int i = 0; i < code_size; i++)
	{
		code_book[i] = 0;
	}

	stackInit(&s);

	int leafNodeSize = 0;

	push(&s, xtree);

	while (!stackIsEmpty(&s) && leafNodeSize != code_size)
	{
		visited_node = pop(&s);

		xnode* left = visited_node->leftchild;
		xnode* right = visited_node->rightchild;

		if ((left->leftchild != NULL) && (left->rightchild != NULL))
		{
			push(&s, left);
		}

		else
		{
			code_book[leafNodeSize] = left->string;
			leafNodeSize++;
		}

		if ((right->leftchild != NULL) && (right->rightchild != NULL))
		{
			push(&s, right);
		}

		else
		{
			code_book[leafNodeSize] = right->string;
			leafNodeSize++;
		}
	}

	char* temp;

	for (int i = 0; i < code_size - 1; i++)
	{
		for (int j = 0; j < code_size - i - 1; j++)
		{
			if (strcmp(code_book[j], code_book[j + 1]) == 1)
			{
				temp = code_book[j];
				code_book[j] = code_book[j + 1];
				code_book[j + 1] = temp;
			}
		}	
	}

	char ch[b + 1];
	ch[b] = '\0';
	
	for (int i = 0; i < code_size; i++)
	{
		for (int bit = 1; bit < code_size; bit *= 2)
		{
			for (int j = b - 1; j >= 0; --j)
			{
				if (i & bit == 1)
					ch[i] = 1;
				else
					ch[i] = 0;
			}
		}
	}

	FILE* file = fopen("codebook.txt", "w");
	for (int i = 0; i < code_size; i++)
	{
		fputs(ch[i], file);
		fputs(" ", file);
		fputs(code_book[i], file);
		fputs("\n",file);
	}

	fclose("coodbook.txt");
}

/*
 * Compress the 'file' using given Xtree and current code_book, and store it into "output.txt".
 */
void compress_x(xnode* xtree, char* file) {
//Implement your function in here

	FILE* rfp = fopen(file, "r");
	FILE* wfp = fopen("output.txt", "w");
	char* c = NULL;
	char* not_code = NULL;

	int compressed_string_num = 0;
	int uncompressed_string_num = 0;
	double compression_ratio = 0;
	int input_size;

	// Input string을 맨 왼쪽부터 linear scan 하면서
	// code book에 있에 있는 string을 발견 시 code c로 변경
	if (rfp != NULL)
	{
		char* buffer = malloc(sizeof(char) * MAX_STRING);

		char* tmp;

		int cnt = 0;
		
		fgets(buffer, sizeof(buffer), rfp);

		int string_size = strlen(buffer);

		for (int index = 0; index < code_size; index++)
		{
			for (int i = 0; i < string_size; i++)
			{
				if (buffer[i] == code_book[index])
				{
					cnt++;

					if (cnt == code_size)
					{
						c[index] = xtree->string;
						compressed_string_num++;
					}
				}

				else
				{
					not_code[index] = xtree->string;
					uncompressed_string_num++;
				}
			}
		}

		input_size = string_size;

		free(buffer);
	}

	// 압축된 것 저장
	for (int i = 0; i < code_size; i++)
	{
		fputs(c[i], wfp);
	}

	fputs("\n", wfp);

	// 압축되지 않은 것 저장
	for (int i = 0; i < code_size; i++)
	{
		fputs(not_code[i], wfp);
	}

	compression_ratio = (compressed_string_num + uncompressed_string_num) / input_size;
	printf("%.4d", compression_ratio);
}

/*
 From 'codebook' (codebook file) and 'output' (compressed file), Decompress the original string and store it as "input_original.txt"
 The generated file (input_original.txt) and the original file should be identical.
 */
void decompress_x(char* output, char* codebook) {
//Implement your function in here

	FILE* out_put = fopen(output, "r");
	FILE* code_book = fopen(codebook, "r");
	FILE* input_origianl = fopen("input_original.txt", "w");

	char *output_str = NULL;
	int output_size = 0;

	if (output != NULL)
	{
		char* buffer = malloc(sizeof(char) * MAX_STRING);

		fgets(buffer, sizeof(buffer), out_put);

		output_size = strlen(buffer);

		for (int i = 0; i < output_size; i++)
		{
			output_str[i] = strcat(buffer[i], buffer[i + 1]);
		}
	}

	char *codebook_index = NULL;
	char *codebook_str = NULL;

	if (code_book != NULL)
	{
		char* buffer = malloc(sizeof(char) * MAX_STRING);

		while (fgets(buffer, sizeof(buffer), code_book) != NULL)
		{
			char seps[] = " ";
			char* token = strtok(buffer, seps);

			if (token != NULL)
			{
				for (int i = 0; i < code_size; i++)
					codebook_index[i] = token;
			}

			token = strtok(NULL, seps);

			if (token != NULL)
			{
				for (int i = 0; i < code_size; i++)
					codebook_str[i] = token;
			}
		}
	}

	char *input_origianl_str = NULL;

	for (int i = 0; i < code_size; i++)
	{
		if (strcmp(codebook_index[i], output_str[i]) == 0)
		{
			input_origianl_str[i] = codebook_str[i];
		}

		else
		{
			print_error();
		}

		fputs(input_origianl_str[i], input_origianl);
	}

	fclose(input_origianl);
}