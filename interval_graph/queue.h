#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "graph.h"

typedef struct {
   int front;
   int rear;
   int count;
   interval item[MAX_VERTICES];
} Queue;

void queueInit(Queue* q);
int queueIsEmpty(Queue* q);
void enqueue(Queue* q, interval new_item);
interval dequeue(Queue* q);

#endif