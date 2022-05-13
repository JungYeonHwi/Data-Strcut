#include "xcode.h"

#ifndef __HEAP__
#define __HEAP__

#define MAX_SIZE (1<<b)


/*Max-heap based priority queue implementation
 * Priority : p of each node in Xtree*/

typedef struct heap {
	xnode* heap_array[MAX_SIZE];
	int current_size;
}heap;
void create(heap* h);
int isEmpty(heap* h);
xnode* findmin(heap* h);
void insert(heap* h, xnode* item);
xnode* deletemin(heap* h);
#endif
