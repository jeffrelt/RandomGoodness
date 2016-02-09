//
//  main.c
//  Merge_lists
//
//  Created by Jeffrey Thompson on 2/8/16.
//  Copyright © 2016 Jeffrey Thompson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define USE_RECURSION

struct node{
    int value;
    struct node* next;
};
typedef struct node Node;


Node* merge(Node* A, Node* B){
    Node anchor;
    anchor.next = NULL;
    Node* walker = &anchor;
    while(A && B){
        if( A->value <= B->value ){
            walker->next = A;
            A = A->next;
        }
        else{
            walker->next = B;
            B = B->next;
        }
        walker = walker->next;
    }
    if(A)
        walker->next = A;
    else if (B)
        walker->next = B;
    return anchor.next;
}

Node* mergeRec(Node* A, Node* B){
    if(A){
        if(B){
            if(A->value <= B->value){
                A->next = mergeRec(A->next,B);
                return A;
            }
            B->next = mergeRec(A,B->next);
            return B;
        }
        return A;
    }
    return B;
}


int main(int argc, const char * argv[]) {
    // insert code here...
#define A_SIZE 8
#define B_SIZE 6
    Node A[A_SIZE];
    Node B[B_SIZE];
    for(int i = 0; i <A_SIZE; ++i){
        A[i].value = i;
        A[i].next = &A[i+1];
    }
    A[A_SIZE-1].next = NULL;
    for(int i = 0; i <B_SIZE; ++i){
        B[i].value = i;
        B[i].next = &B[i+1];
    }
    B[B_SIZE-1].next = NULL;
#ifdef USE_RECURSION
    Node* c = mergeRec(A,B);
#else
    Node* c = merge(A,B);
#endif
    while(c){
        printf("%i ",c->value);
        c = c->next;
    }

    return 0;
}
