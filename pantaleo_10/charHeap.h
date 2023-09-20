#ifndef CHARHEAP_H
#define CHARHEAP_H
#include <stdint.h>

typedef struct charNode{
    int moveTime;
    char symbol;
    int id;
} charNode_t;

typedef struct cHeap{
    int size;
    charNode_t charHeapArray[8];
} charHeap_t;

void charHeap_init(charHeap_t *h);
charNode_t charHeap_pop(charHeap_t *h);
void charHeap_add(charHeap_t *h, charNode_t n);
int charHeap_isEmpty(charHeap_t *h);
charNode_t charHeap_peek(charHeap_t *h);
void charHeapifyUp(charHeap_t *h, int location);
void charHeapifyDown(charHeap_t *h, int location);
void charHeap_remove(charHeap_t *h, int location);

#endif