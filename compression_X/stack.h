#ifndef __STACK_H__
#define __STACK_H__

#include "xcode.h"
#define MAX_ITEM (1<<b)

/*Array-based stack implementation*/


typedef struct {
	int top_idx;
	xnode* stack[MAX_ITEM];
} Stack;

void stackInit(Stack* s);
int stackIsEmpty(Stack* s);
void push(Stack* s, xnode* new_item);
xnode* pop(Stack* s);

#endif
