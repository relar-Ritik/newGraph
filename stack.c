//
// Created by Ritik Anand Agrawal on 25-05-2020.
//

#include "stack.h"

void initStack(stack *a) {
    a->size = 0;
    a->top = NULL;
}

void pushStack(stack *a, int data) {
    a->size = a->size + 1;
    a->top = insertNode(a->top, data);
}

int popStack(stack *a) {
    int ret = -1;
    if(a->size > 0){
        ret = a->top->data;
        node *temp = a->top;
        a->top = a->top->next;
        free(temp);
        a->size = a->size - 1;
    }
    return ret;
}

