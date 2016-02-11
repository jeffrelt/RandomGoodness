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
 Min-heap utilizing a fix-sized array. Like the queue this structure lets
 you keep cramming in data without ever checking if it's full by swapping
 in the new value if it is greater than the smallest element in the heap.
 
 The choice to use a array as the base is good for space and computational
 efficiency vs linked list (tree) based. no need to allocate and free anything!
 
 Cool thing about a heap - sorted order IS a valid min heap! so after
 sorting we can continue to use it without needing to 'heapify' the array.
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
    // result is a valid min-heap
void sortHeap(heap_t* h);



#endif /* heap_h */
