#include <stdlib.h>
#include <stdio.h>


struct node{
	int value;
	struct node* next;
};
typedef struct node Node;

Node* newNode(int value, Node* next){
	Node* new_node = malloc(sizeof(Node));
	new_node->value = value;
	new_node->next = next;
	return new_node;
}

Node* insertBeforeNode(Node* list, int value, unsigned int index){
		//if index > size of list node will got to end 
	Node anchor;
	anchor.next = list;
	Node* walker = &anchor;
	Node* next = NULL;
	int count = 0;
	while(walker->next){
		if(count == index){
			next = walker->next;
			break;
		}
		walker = walker->next;
		++count;
	}
	walker->next = newNode(value,next);
	return anchor.next;
}

void printList(Node* list){
	while(list){
		printf("%i ",list->value);
		list = list->next;
	}
}


int removeNode(Node* list, int value){
	Node anchor;
	anchor.next = list;
	Node* walker = &anchor;
	while(walker->next){
		if(walker->next->value == value){
			Node* hold = walker->next;
			walker = hold->next;
			free(hold);
			return 0;
		}
		walker = walker->next;
	}
	return -1;
}



