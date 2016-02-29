#include "allignedMalloc.h"

int nothing(const char* format, ...){}

int (*debug)(const char *,...) = nothing;


void* allignedMalloc(size_t bytes, unsigned int allignment_bytes){
	debug("requesting %i bytes\n", bytes+allignment_bytes+sizeof(void*));
	char* address = malloc(bytes+allignment_bytes+sizeof(void*) );
	debug("Recieved address 0x%x from malloc\n", (size_t)address);
	int offset = (size_t)address % allignment_bytes;
	while( offset < sizeof(void*) )
		offset+=allignment_bytes;
	*(void**)(address+offset-sizeof(void*))=address;
	return address+offset;
}

void allignedFree(void* address){
	debug("freeing address 0x%x\n", (size_t)((void**)address)[-1]);
	free( ((void**)address)[-1] );
}





