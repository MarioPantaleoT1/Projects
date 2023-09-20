#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "charHeap.h"


int charCompare(charNode_t n1, charNode_t n2){
    if (n1.moveTime > n2.moveTime){
        return 1;
    }
    if (n1.moveTime == n2.moveTime){
        if (n1.id > n2.id) {
            return 1;
        }
        return 0;
    }
    return 0;
}

int charHeap_min(charHeap_t *h, int i, int j){
    if (charCompare(h->charHeapArray[i], h->charHeapArray[j]) == 0){
        return i;
    }
    return j;
}

void charSwap(charHeap_t *h, int a, int b){    
    charNode_t temp = h->charHeapArray[a];                           
    h->charHeapArray[a] = h->charHeapArray[b];      
    h->charHeapArray[b] = temp;   
}

int charParent(charHeap_t *h, int i){
    if (i != 0){
        return (i - 1) /2;
    }
    return -1;
}

void charHeap_init(charHeap_t *h){
    char c[9] = {'@', 'h', 'r', 'p', 'P', 'w', 'e', 'm', '\0'};
    for (int i = 0; i < 8; i++){
        charNode_t temp;
        temp.id = i;
        temp.moveTime = 0;
        temp.symbol = c[i];
        h->charHeapArray[i] = temp;
    }
    h->size = 8;
}

//when popped may want to assign them to respective map in actual pokemon
charNode_t charHeap_pop(charHeap_t *h){
    charNode_t top = h->charHeapArray[0];
    charSwap(h, 0, h->size - 1);
    charHeap_remove(h, h->size - 1);
    charHeapifyDown(h, 0);
    return top;
}

void charHeap_add(charHeap_t *h, charNode_t node){
    h->charHeapArray[h->size] = node;
    charHeapifyUp(h, h->size);
    h->size++;
}

int charHeap_isEmpty(charHeap_t *h){
    return h->size;
}

charNode_t charHeap_peek(charHeap_t *h){
    return (h->charHeapArray[0]);
}

void charHeapifyUp(charHeap_t *h, int location){
    if (location == 0){
        return;
    }
    //child greater than charParent
    if (charCompare(h->charHeapArray[location], h->charHeapArray[charParent(h, location)]) == 1){
        return;
    }
    charSwap(h, location, charParent(h, location));
    charHeapifyUp(h, charParent(h, location));
}

void charHeapifyDown(charHeap_t *h, int location){
    int leftOrRight = location;
    for (int i = 1; i < 3; i++){
        int newLoc = location * 2 + i;
        if (newLoc > h->size){
            return;
        }
        //if current place is bigger than left child
        if (charCompare(h->charHeapArray[leftOrRight], h->charHeapArray[newLoc]) == 1){
            leftOrRight = charHeap_min(h, leftOrRight, newLoc);
        }
    }
    if (leftOrRight != location){
        charSwap(h, location, leftOrRight);
        charHeapifyDown(h, leftOrRight);
    }
}

void charHeap_remove(charHeap_t *h, int location){
    h->size--;
}




