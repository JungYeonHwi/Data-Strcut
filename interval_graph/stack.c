#include "stack.h"

#include <stdio.h>

#include "graph.h"

void stackInit(Stack* s) { s->top_idx = -1; }
int stackIsEmpty(Stack* s) {
   if (s->top_idx == -1)
      return 1;
   else
      return 0;
}
void push(Stack* s, interval new_item) {
   if (s->top_idx < MAX_VERTICES - 1) {
      s->top_idx++;
      s->stack[s->top_idx] = new_item;
   } else {
      printf("Cannot insert data, Stack is full.\n");
   }
}
interval pop(Stack* s) {
   interval item;
   if (!stackIsEmpty(s)) {
      item = s->stack[s->top_idx];
      s->top_idx--;
      return item;
   } else {
      printf("Cannot retrieve data, Stack is empty.\n");
   }
}
