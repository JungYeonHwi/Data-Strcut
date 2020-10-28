#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

void queueInit(Queue* q) {
   q->front = 0;
   q->rear = 0;
   q->count = 0;
   memset(q->item, 0, sizeof(q->item));
}

int queueIsEmpty(Queue* q) {
   int empty = 0;

   if (q->count == 0) empty = 1;

   return empty;
}

void enqueue(Queue* q, interval new_item) {
   if (q->count == MAX_VERTICES) {
      printf("Queue Overflow\n");
      return;
   }
   q->item[q->rear] = new_item;
   q->rear = (q->rear + 1) % MAX_VERTICES;
   q->count++;
}

interval dequeue(Queue* q) {
   if (queueIsEmpty(q)) {
      printf("Queue Underflow\n");
      interval v = {-1, -1};
      return v;
   }

   interval value = q->item[q->front];
   q->front = (q->front + 1) % MAX_VERTICES;
   q->count--;

   return value;
}