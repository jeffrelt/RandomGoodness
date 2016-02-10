//
//  common.h
//  fitbit_project
//
//  Created by Jeffrey Thompson on 2/9/16.
//  Copyright © 2016 Jeffrey Thompson. All rights reserved.
//

#ifndef common_h
#define common_h

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/*
   The choice was obvious for me use a heap for the max 32 values and a queue for the last 32.
   I had a lot of fun implimenting these as there are a lot of little optimizations that can be done. 
   The choice of 32 samples to track I'm sure was no accident ;)
 
   The only realy tradeoffs to be 
*/

////* user configurable switches */////

// for debugging
//#define SET_INPUT

// for SET_INPUT
// as a side note, I converted my .out files to unix formatting and corrected a typo ;)
#define FILENAME "tests_provided/test3.bin"


// My inclination is to avoid the heap in an embeded device so I'm leaving this off, but options are nice ;)
//#define ON_HEAP

// extended note below
//#define USE_BIT_FIELDS

// per the specs of the question this should be 32, and the way I did the queue it needs to be a power of 2
#define DATASET 32

////* Common stuff amongt the queue and heap */////

#define MASKSET DATASET-1

/*The struct is to allow the bit field. The idea is to reduce memory usage by 1/4, but at least my compiler is not
  cooperating. The issue is accessing the odd indexes are rather innefficent so it decied to add padding in the array...
  The only real way to do this would be to roll it manually. I could (and I have a though on how to do it fairly 
  efficiently) but we are talking about a combined 32 bytes here betwen the heap and queue. There is a high probability
  the added overhead to do the more complex accessing would outway any savings.
*/
struct data{
#ifdef USE_BIT_FIELDS
    unsigned short val:12;
#else
    unsigned short val;
#endif
};

typedef struct data data_t;



#endif /* common_h */
