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
 Project-wide Discussion (each .h file and main.c has it’s own mini discussion):
 
 The choice was pretty clear to me to use a heap for the max 32 values and a circular
 queue for the last 32. However, if we often need to access the sorted values a
 balanced search tree could be better choice. Walking the tree in sorted
 order is an O(n) operation instead of O(n log) for sorting the heap, but search trees 
 are a little more complicated to implement and more wasteful space wise. The space 
 advantage of the heap is becuase it's 'tree' is always complete.
 
 I played with the idea of creating a packed data format as every element in our
 structures have a wasted nibble, but decided against it here for the following reasons:
 - we have a total of 64 elements, so this adds up to only 32 bytes of wasted
   space between the queue and heap.
 - Accessing irregular offsets is highly inefficient. If this where infrequntly accessed
   storage it may be worth the cost, but these are fairly high turnover data structures.
 
 I made a switch (ON_HEAP) for putting the data structures on the heap (dynamic memory),
 but as these are pretty compact data structures I cannot see a good reason to do so. 
 I generally avoid the heap in embedded systems if I can help it.
 
 I had a lot of fun implementing these as there are a lot of little optimizations
 that can be done. The choice of 32 samples to track I'm sure was no accident.
 
 As a side note, I converted the provided .out files to unix formatting and corrected a typo ;)
*/


////* user configurable switches */////

// for debugging it's nice to not have to type in EVERY run
//#define SET_INPUT

// for SET_INPUT
//
#define FILENAME "/Users/apple/Documents/workspace/RandomGoodness/C/fitbit_project/fitbit_project/tests_provided/test1.bin"


// My inclination is to avoid the heap in an embeded device so I'm leaving this off, but options are nice ;)
//#define ON_HEAP

// per the specs of the question this should be 32, and the way I did the queue it needs to be a power of 2
#define DATASET 32


// This typedef is to allow the data type to be changed easily if we choose, although changing to a struct would require
// additional work in the code to make it work...
typedef unsigned short data_t;



#endif /* common_h */
