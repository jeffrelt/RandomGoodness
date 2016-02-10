//
//  heap.h
//  fitbit_project
//
//  Created by Jeffrey Thompson on 2/9/16.
//  Copyright © 2016 Jeffrey Thompson. All rights reserved.
//

#ifndef heap_h
#define heap_h

#include "common.h"

/*
 Min heap utilizing a array.
 */

struct heap{
    data_t array[DATASET];
    unsigned char size;
};
typedef struct heap heap_t;

    // initialize the values - if passed NULL allocates the memory
heap_t* initHeap(heap_t* h);

    // returns the minimum value
data_t peekHeap(const heap_t* h);

    // push a value into the heap until it is full
    // after full it will swap the value if it is greater than the prior min
void pushHeap(heap_t* h, data_t add_this);

    // assumes the heap does actually hold something so check the size first
data_t popHeap(heap_t* h);

    // swap the min value for the sent value (again assumes not empty)
data_t swapHeap(heap_t* h, data_t swap_this);

    // converts the heap into a sorted array (accessable in h->array)
    // node the result will be reversed sorted order
void sortHeap(heap_t* h);

    // called after heapSort to go back to a heap
void reHeap(heap_t* h);


#endif /* heap_h */
