#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, const char** argv){
	Node* root = insertBeforeNode(NULL,2,0);
	root = insertBeforeNode(root,1,0);
	root = insertBeforeNode(root,3,99);
	root = insertBeforeNode(root,0,0);
	printList(root);
	
}
