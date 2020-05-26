//
// Created by Ritik Anand Agrawal on 25-05-2020.
//

#include "edgeList.h"

edge *createEdge(int vertex, int cost) {
    edge *new = malloc(sizeof(edge));
    new->vertex = vertex;
    new->cost = cost;
    new->next = NULL;
    return new;
}

edge *insertEdge(edge *head, int vertex, int cost) {
    edge *new = createEdge(vertex, cost);
    new->next = head;
    head = new;
    return head;
}

edge *deleteEdge(edge *head, int vertex) {
    if(head != NULL){
        if(head->vertex == vertex){
            edge *temp = head;
            head = head->next;
            free(temp);
        }
        else{
            edge *prev = head;
            edge *ptr = head->next;
            while (ptr!=NULL && ptr->vertex != vertex){
                prev = ptr;
                ptr = ptr->next;
            }
            if(ptr != NULL){
                prev->next = ptr->next;
                free(ptr);
            }
        }
    }
    return head;
}

edge *findInEdge(edge *head, int vertex) {
    while (head !=NULL && head->vertex != vertex){
        head = head->next;
    }
    return head;
}

