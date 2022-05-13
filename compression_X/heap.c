#include "xcode.h"
#include "heap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void create(heap* h) {
	h->current_size = 0;
}
int isEmpty(heap* h) {
	if (h->current_size > 0) return 0;
	return 1;
}
xnode* findmin(heap* h) {
	return h->heap_array[0];
}
void insert(heap* h, xnode* item) {
	if (h->current_size < MAX_SIZE) {
		h->heap_array[h->current_size] = (xnode*)malloc(sizeof(xnode));
		h->heap_array[h->current_size] = item;

		xnode* temp;
		int parent = (h->current_size - 1) / 2;
		int index = h->current_size;

		while (parent >= 0) {
			if (h->heap_array[parent]->p < h->heap_array[index]->p) {
				temp = h->heap_array[parent];
				h->heap_array[parent] = h->heap_array[index];
				h->heap_array[index] = temp;
				index = parent;
				parent = (index - 1) / 2;
			}
			else break;
		}
		h->current_size++;
	}
}
xnode* deletemin(heap* h) {
	if (isEmpty(h)) return NULL;
	xnode* delete_item = h->heap_array[0];
	xnode* new_root = h->heap_array[h->current_size - 1];
	h->heap_array[h->current_size - 1] = NULL;
	h->heap_array[0] = new_root;
	h->current_size--;
	
	int index = 0,max;
	int	left = 1;
	xnode* temp;
	int	right = 2;
	while (left < h->current_size || right < h->current_size) {
		max = index;
		if (left < h->current_size && (h->heap_array[left]->p > h->heap_array[max]->p)){
			max = left;
		}
		if (right < h->current_size && (h->heap_array[right]->p > h->heap_array[max]->p)){
			max = right;
		}
		if (max != index) {
			temp = h->heap_array[max];
			h->heap_array[max] = h->heap_array[index];
			h->heap_array[index] = temp;
			index = max;
			left = index * 2 + 1;
			right = index * 2 + 2;
		}
		else
		{	break;}
	}
	return delete_item;
}
