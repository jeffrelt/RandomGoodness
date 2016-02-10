//
//  heap.h
//  fitbit_project
//
//  Created by Jeffrey Thompson on 2/9/16.
//  Copyright © 2016 Jeffrey Thompson. All rights reserved.
//

#include "heap.h"

void heap_down(heap_t* h);
void heap_up(heap_t* h);
void swap_heap(heap_t* h, unsigned int ia, unsigned int ib);

heap_t* initHeap(heap_t* h){
    if(h == NULL)
        h = malloc(sizeof(heap_t));
    h->size = 0;
    return h;
}

data_t peekHeap(const heap_t* h){
    return h->array[0];
}

void pushHeap(heap_t* h, data_t add_this){
        // if full we check if the value is higher than the min
        // then swap it in if so
    if(h->size == DATASET){
        if(add_this.val > h->array[0].val)
            swapHeap(h,add_this);
        return;
    }
        // othersize put it at the back and heapup
    h->array[h->size++] = add_this;
    heap_up(h);
}

data_t popHeap(heap_t* h){
        // pop off the "root" then move the last up front and heap it down
    data_t hold = h->array[0];
    h->array[0] = h->array[--h->size];;
    heap_down(h);
    return hold;
}


data_t swapHeap(heap_t* h, data_t swap_this){
        // like popHeap then pushHeap, but is a little more efficient done at once
    data_t hold = h->array[0];
    h->array[0] = swap_this;
    heap_down(h);
    return hold;
}

void sortHeap(heap_t* h){
        // basicly pop everything off and put it at the back ending up in reverse order
    unsigned int target = DATASET-1;
        // pop until empty
    while(h->size){
        h->array[target] = popHeap(h);
        target-=1;
    }
        // recover our size
    h->size = DATASET - target - 1;
}

void reHeap(heap_t* h){
        // if we are completely full no need to move things to the front,
        // just up the size and heap_up like a push was done
    if(h->size == DATASET){
        h->size = 0;
        while(h->size < DATASET){
            ++h->size;
            heap_up(h);
        }
    }
        // otherwise we assume everything is at the back of the array after a sortHeap,
        // so start at the element closest to the front so nothing gets overlaped
    unsigned int target = DATASET - h->size;
    h->size = 0;
    while( target < DATASET){
        pushHeap(h, h->array[target]);
        ++target;
    }
}


///// helper functions /////

void swap_heap(heap_t* h, unsigned int ia, unsigned int ib){
    data_t hold = h->array[ia];
    h->array[ia] = h->array[ib];
    h->array[ib] = hold;
}

void heap_down(heap_t* h){
        // bubble down until we either get to the edge or we find the right place (after a pop)
    unsigned int target = 0;
    unsigned int child1 = 1;
    unsigned int child2 = 2;
        // it could be that the left child (child1) is within the boundry and the other is not
    while(child1 < h->size ){
            // if the right child is within bound check if it is the smaller child
        if(child2 < h->size && h->array[child1].val > h->array[child2].val)
            child1 = child2; //swap if so
            // if order is good just stop
        if( h->array[target].val < h->array[child1].val )
            break;
            //swap then find the next set of children to buble down to
        swap_heap(h,target,child1);
        target = child1;
        child1 = (target<<1)+1;
        child2 = child1+1;
    }
}

void heap_up(heap_t* h){
        // bubble up from the last node (after a push)
    int target = h->size -1;
        // I love I can navigate around in an array based tree!
    int parent = (target-1)>>1;
        // keep going until we reach the root
    while(target > 0){
            //if it looks good stop
        if( h->array[target].val >= h->array[parent].val )
            break;
            //else keep going
        swap_heap(h,target,parent);
        target = parent;
        parent = (parent-1)>>1;
    }
}