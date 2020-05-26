//
// Created by ritik on 26/05/20.
//

#ifndef G2_EDGELIST_H
#define G2_EDGELIST_H
#include "linkedList.h"
typedef struct ed_tag{
    int vertex;
    int cost;
    struct ed_tag *next;
}edge;

edge *createEdge(int vertex, int cost);
edge *insertEdge(edge *head,int vertex, int cost);
edge *deleteEdge(edge *head, int vertex);
edge *findInEdge(edge *head, int vertex);

#endif //G2_EDGELIST_H
