//
//  queue.c
//  fitbit_project
//
//  Created by Jeffrey Thompson on 2/9/16.
//  Copyright © 2016 Jeffrey Thompson. All rights reserved.
//

#include "queue.h"


queue_t* initQueue(queue_t* q){
    if(q == NULL)
        q = malloc(sizeof(queue_t));
    q->base = 0;
    q->size = 0;
    return q;
}

void pushQueue(queue_t* q, data_t add_this){
        // push in the data possibly overwriting the old data
        // note the use of the masks instead of modulo or an if statement
    q->array[(q->base+q->size)&MASKSET] = add_this;
        // if we were full just up the base index so the next oldest moves to the front
    if(q->size == DATASET)
        q->base = (q->base+1)&MASKSET;
        // else (we are not full up the size
    else
        ++q->size;
}


data_t popQueue(queue_t* q){
        // save the value and shrink
    data_t hold = q->array[(q->base+q->size-1)&MASKSET];
    --q->size;
    return hold;
}


data_t getIndexQueue(const queue_t* q, int index){
    return q->array[(q->base+index)&MASKSET];
}