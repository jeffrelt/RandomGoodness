#include "allignedMalloc.h"


int main(int argc, const char ** argv){
	int bytes, allignment;
	if( argc < 3 || !sscanf(argv[1], "%d",&bytes) || !sscanf(argv[2],"%d",&allignment) 
		|| bytes < 0 || allignment < 1){
		printf("Usage: ./test <bytes to allocate> <bytes to allign to>\n");
		return -1;
	}
	debug = printf;
	
	debug("Recieved the parameters %u %u\n", bytes,allignment);
	void* a = allignedMalloc(bytes,allignment);
	debug("Recieved address 0x%x from allignedMalloc\n", (size_t)a);
	allignedFree(a);
}
