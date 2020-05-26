//
// Created by ritik on 26/05/20.
//

#ifndef G2_LINKEDLIST_H
#define G2_LINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {FALSE, TRUE} bool;

typedef struct node_tag{
    int data;
    struct node_tag *next;
}node;

node *createNode(int data);
node *insertNode(node *head,int data);
node *deleteNode(node *head, int data);
node *findInList(node *head, int data);


#endif //G2_LINKEDLIST_H
