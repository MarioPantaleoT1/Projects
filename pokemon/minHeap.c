#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "minHeap.h"


int compare(heapNode_t n1, heapNode_t n2){
    if (n1.totalDist > n2.totalDist){
        return 1;
    }
    return 0;
}

int heap_min(heap_t *h, int i, int j){
    if (compare(h->heapArray[i], h->heapArray[j]) == 0){
        return i;
    }
    return j;
}

void swap(heap_t *h, int a, int b){    
    heapNode_t temp = h->heapArray[a];                           
    h->heapArray[a] = h->heapArray[b];      
    h->heapArray[b] = temp;   
}

int parent(heap_t *h, int i){
    if (i != 0){
        return (i - 1) /2;
    }
    return -1;
}

void heap_init(heap_t *h){
    h->size = 0;
}

//when popped may want to assign them to respective map in actual pokemon
heapNode_t heap_pop(heap_t *h){
    heapNode_t top = h->heapArray[0];
    swap(h, 0, h->size - 1);
    heap_remove(h, h->size - 1);
    heapifyDown(h, 0);
    return top;
}

void heap_add(heap_t *h, heapNode_t node){
    h->heapArray[h->size] = node;
    heapifyUp(h, h->size);
    h->size++;
}

int heap_isEmpty(heap_t *h){
    return h->size;
}

heapNode_t heap_peek(heap_t *h){
    return (h->heapArray[0]);
}

void heapifyUp(heap_t *h, int location){
    if (location == 0){
        return;
    }
    //child greater than parent
    if (compare(h->heapArray[location], h->heapArray[parent(h, location)]) == 1){
        return;
    }
    swap(h, location, parent(h, location));
    heapifyUp(h, parent(h, location));
}

void heapifyDown(heap_t *h, int location){
    int leftOrRight = location;
    for (int i = 1; i < 3; i++){
        int newLoc = location * 2 + i;
        if (newLoc > h->size){
            return;
        }
        //if current place is bigger than left child
        if (compare(h->heapArray[leftOrRight], h->heapArray[newLoc]) == 1){
            leftOrRight = heap_min(h, leftOrRight, newLoc);
        }
    }
    if (leftOrRight != location){
        swap(h, location, leftOrRight);
        heapifyDown(h, leftOrRight);
    }
}

void heap_remove(heap_t *h, int location){
    h->size--;
}




