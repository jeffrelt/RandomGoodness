//
//  main.c
//  fitbit_project
//
//  Created by Jeffrey Thompson on 2/8/16.
//  Copyright © 2016 Jeffrey Thompson. All rights reserved.
//

#include "common.h"
#include "queue.h"
#include "heap.h"

#ifdef SET_INPUT
const char* filename = FILENAME;
#endif

/*
  I'll discuss here this code, overall design discussed in common.h
  
 
*/

int main(int argc, const char * argv[]) {
        // went with a union to aid in the unpacking
    union{
        unsigned char bytes[4];
        unsigned int whole;
    }packed;
    
        // initialize the heap and queue (notes about the choice below in common.h)
#ifdef ON_HEAP
    queue_t* q = initQueue(NULL);
    heap_t* h = initHeap(NULL);
#else
    queue_t queue;
    heap_t heap;
    queue_t* q = &queue;
    heap_t* h = &heap;
    initQueue(q);
    initHeap(h);
#endif
    
        // hard coding during testing is nice...
#ifdef SET_INPUT
    FILE *file_handle = fopen(filename,"r");
#else
        // Ensure the user sent at least one file, spash usage info if not
    if(argc < 2){
        printf("Must run with a command line parameters\nusage: 12bit data_file [output_file]\n");
        return -1;
    }
        // try opening the filename sent
    FILE *file_handle = fopen(argv[1], "r");
#endif
        // if we cannot open the file throw up errors and exit
    if( !file_handle ){
        perror(NULL);
        fprintf(stderr, "Could not open file %s for reading.",argv[1]);
        return -1;
    }
        //we unpack into the structure backwards due to endianess to get the right order
    int which = 2;
    data_t value;
        // Go until we find EOF
    while(!feof(file_handle)){
        packed.bytes[which] = fgetc(file_handle);
        --which;
            // read 3 bytes then process the two 12 bit values
        if(which < 0){
            which = 2;
                // for the first, shift it down (pushing off the other value)
            value.val = packed.whole >> 12;
                // put it in our structures
            pushQueue(q, value);
            pushHeap(h, value);
                // in the case of an odd number of samples we'll catch the EOF on that last byte, so check for that case
            if(feof(file_handle))
               break;
                // this one we use a mask to zero out the first vaue
            value.val = packed.whole & (1<<12)-1;
            pushQueue(q, value);
            pushHeap(h, value);
        }
    }
        // close the file (we reuse the handle) and convert the heap into a reverse sorted array
    fclose(file_handle);
    sortHeap(h);
    
        // check if a second filename was passed
    if(argc >= 3){
            // try to open it if so
        file_handle = fopen(argv[2], "w");
        if(!file_handle){
            perror(NULL);
            fprintf(stderr, "Could not open file %s for writing. Sending to stdout instead.\n\n",argv[2]);
            file_handle = stdout;
        }   // at this point we're spitting results somewhere!
    }
    else
        file_handle = stdout;
    
    fprintf(file_handle,"--Sorted Max 32 Values--\n");
    
        // work through the heap array backwards
    for(int i = DATASET-1; i >= DATASET - h->size; --i){
        fprintf(file_handle, "%i\n", h->array[i].val);
    }
    
    fprintf(file_handle,"--Last 32 Values--\n");
    
        // we can walk through the queue like it is a simple array
    for(unsigned int i=0; i < q->size; ++i){
        fprintf(file_handle, "%i\n", getIndexQueue(q,i).val);
    }
    
        // and we're done!
    fclose(file_handle);
#ifdef ON_HEAP
    free(q);
    free(h);
#endif
    
    return 0;
}
