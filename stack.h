//
// Created by ritik on 26/05/20.
//

#ifndef G2_STACK_H
#define G2_STACK_H
#include "linkedList.h"

typedef struct stack_type{
    int size;
    node *top;
}stack;

void initStack(stack *a);
void pushStack(stack *a, int data);
int popStack(stack *a);


#endif //G2_STACK_H
