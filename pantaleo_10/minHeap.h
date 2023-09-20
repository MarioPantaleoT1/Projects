#ifndef MINHEAP_H
#define MINHEAP_H
#include <stdint.h>

typedef struct heapNode{
    int weight;
    char symbol;
    int mapX;
    int mapY;
    int totalDist;
    int id;
} heapNode_t;

typedef struct heap{
    int size;
    heapNode_t heapArray[1680];
} heap_t;

void heap_init(heap_t *h);
heapNode_t heap_pop(heap_t *h);
void heap_add(heap_t *h, heapNode_t n);
int heap_isEmpty(heap_t *h);
heapNode_t heap_peek(heap_t *h);
void heapifyUp(heap_t *h, int location);
void heapifyDown(heap_t *h, int location);
void heap_remove(heap_t *h, int location);

#endif