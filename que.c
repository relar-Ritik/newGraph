//
// Created by ritik on 25/05/20.
//

#include "que.h"

void initQue(Que *A) {
    A->top = NULL;
    A->tail=NULL;
    A->size = 0;
}

void pushQue(Que *A, int data) {
    node *new = createNode(data);
    if(A->size == 0){
        A->top=new;
        A->tail=new;
        A->size = 1;
    } else{
        A->tail->next = new;
        A->tail = new;
        A->size = A->size + 1;
    }
}

int popQue(Que *A) {
    int ret = -1;
    if(A->size > 0){
        node *temp = A->top;
        A->top = A->top->next;
        ret = temp->data;
        if(A->size == 1){
            A->tail = NULL;
        }
        free(temp);
        A->size = A->size - 1;
    }
    return ret;
}

void deleteQue(Que *A) {
    while (A->top != NULL){
        node *temp = A->top;
        A->top = temp->next;
        free(temp);
    }
    A->size=0;
    A->top=NULL;
    A->tail = NULL;
}
