#ifndef ALLIGNEDMALLOC_H
#define ALLIGNEDMALLOC_H

#include <stdio.h>
#include <stdlib.h>


extern int (*debug)(const char *,...);

int nothing(const char* format, ...);

void* allignedMalloc(size_t bytes, unsigned int allignment_bytes);

void allignedFree(void* address);


#endif
