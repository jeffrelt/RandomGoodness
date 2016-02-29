#include <stdio.h>
#include <stdlib.h>



void* allignedMalloc(size_t bytes, unsigned int allignment_bytes){
	printf("requesting %i bytes\n", bytes+allignment_bytes+sizeof(void*));
	char* address = malloc(bytes+allignment_bytes+sizeof(void*) );
	printf("Recieved address 0x%x from malloc\n", (size_t)address);
	int offset = (size_t)address % allignment_bytes;
	while( offset < sizeof(void*) )
		offset+=allignment_bytes;
	*(void**)(address+offset-sizeof(void*))=address;
	return address+offset;
}

void allignedFree(void* address){
	printf("freeing address 0x%x\n", (size_t)((void**)address)[-1]);
	free( ((void**)address)[-1] );
}




int main(int argc, const char ** argv){
	int bytes, allignment;
	if( argc < 3 || !sscanf(argv[1], "%d",&bytes) || !sscanf(argv[2],"%d",&allignment) 
		|| bytes < 0 || allignment < 1){
		printf("Usage: ./test <bytes to allocate> <bytes to allign to>\n");
		return -1;
	}
	printf("Recieved the parameters %u %u\n", bytes,allignment);
	void* a = allignedMalloc(bytes,allignment);
	printf("Recieved address 0x%x from allignedMalloc\n", (size_t)a);
	allignedFree(a);
}
