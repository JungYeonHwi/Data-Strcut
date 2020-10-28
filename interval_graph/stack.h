#ifndef __STACK_H__
#define __STACK_H__

#include "graph.h"

typedef struct {
   int top_idx;
   interval stack[MAX_VERTICES];
} Stack;

void stackInit(Stack* s);
int stackIsEmpty(Stack* s);
void push(Stack* s, interval new_item);
interval pop(Stack* s);

#endif