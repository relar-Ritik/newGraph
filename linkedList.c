//
// Created by ritik on 25/05/20.
//

#include "linkedList.h"

node *createNode(int data) {
    node *new = malloc(sizeof(node));
    new->data = data;
    new->next = NULL;
    return new;
}

node *insertNode(node *head,int data) {
    node *new = createNode(data);
    new->next = head;
    head = new;
    return head;
}

node *deleteNode(node *head, int data) {
    if(head != NULL){
        if(head->data == data){
            node *temp = head;
            head = head->next;
            free(temp);
        }
        else{
            node *prev = head;
            node *ptr = head->next;
            while (ptr!=NULL && ptr->data != data){
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

node *findInList(node *head, int data) {
    while (head !=NULL && head->data != data){
        head = head->next;
    }
    return head;
}
