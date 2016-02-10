//
//  queue.h
//  fitbit_project
//
//  Created by Jeffrey Thompson on 2/9/16.
//  Copyright © 2016 Jeffrey Thompson. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include "common.h"


/*
Curcular array based Queue which silently overwrites the oldest values once full
DATASET is assumed to be a power of 2 (allows a few nice optimizations)
*/

struct queue{
    data_t array[DATASET];
    unsigned char base;
    unsigned char size;
};
typedef struct queue queue_t;

    // initialize the values - if passed NULL allocates the memory
queue_t* initQueue(queue_t* q);

    //push and keep pushing, overwrites the oldest items in the queue if needed
void pushQueue(queue_t* q, data_t add_this);

    // assumes the queue does actually hold something so check the size first
data_t popQueue(queue_t* q);

    // assumes the element does exist, so check first that index exists
    // index is relative to oldest element (which is at index 0)
    // allows array like access
data_t getIndexQueue(const queue_t* q, int index);



#endif /* queue_h */
