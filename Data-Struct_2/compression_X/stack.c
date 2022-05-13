#include "stack.h"

#include <stdio.h>

#include "xcode.h"

void stackInit(Stack* s) { s->top_idx = -1; }
int stackIsEmpty(Stack* s) {
	if (s->top_idx == -1)
		return 1;
	else
		return 0;
}
void push(Stack* s, xnode* new_item) {
	if (s->top_idx < MAX_ITEM - 1) {
		s->top_idx++;
		s->stack[s->top_idx] = new_item;
	}
	else {
		printf("Could not insert data, Stack is full.\n");
	}
}
xnode* pop(Stack* s) {
	xnode* item;
	if (!stackIsEmpty(s)) {
		item = s->stack[s->top_idx];
		s->top_idx--;
		return item;
	}
	else {
		printf("Could not retrieve data, Stack is empty.\n");
	}
}
