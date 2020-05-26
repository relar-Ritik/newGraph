//
// Created by ritik on 26/05/20.
//

#ifndef G2_QUE_H
#define G2_QUE_H
#include "linkedList.h"

typedef struct q_type{
    node *top;
    node *tail;
    int size;
}Que;

void initQue(Que *A);
void pushQue(Que *A, int data);
int popQue(Que *A);
void deleteQue(Que *A);



#endif //G2_QUE_H
