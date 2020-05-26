//
// Created by ritik on 25/05/20.
//

#include "graph.h"
#define INF 0x7fffffff

void init_graph(graph *a) {
    a->size=0;
    for (int i = 0; i < MAXSIZE; ++i) {
        a->vertices[i].active= FALSE;
        a->vertices[i].edgeList =NULL;
    }
}

void addVertex(graph *a, int V) {
    a->size += 1;
    a->vertices[V].active = TRUE;
}

void addEdge(graph *a, int V1, int V2, int is_directed, int cost) {
    if(findInEdge(a->vertices[V1].edgeList, V2) == NULL){
        a->vertices[V1].edgeList = insertEdge(a->vertices[V1].edgeList, V2,cost);
    }
    if(is_directed  == 0){
        if(findInEdge(a->vertices[V2].edgeList, V1) == NULL){
            a->vertices[V2].edgeList = insertEdge(a->vertices[V2].edgeList, V1,cost);
        }
    }
}

void depthFirstTraversal(graph *a, int origin) {
    bool isVisited[MAXSIZE]={FALSE};
    dfs(a,origin ,isVisited);
    for (int i = 0; i < MAXSIZE; ++i) {
        if(a->vertices[i].active == TRUE){
            if(isVisited[i] == FALSE){
                dfs(a, i, isVisited);
            }
        }
    }
    printf("\n");
}

void dfs(graph *a, int vertex, bool isVisited[MAXSIZE]) {
    printf("%d ", vertex);
    isVisited[vertex] = TRUE;
    edge *alist = a->vertices[vertex].edgeList;
    while (alist !=NULL){
        if(isVisited[alist->vertex] == FALSE){
            dfs(a, alist->vertex, isVisited);
        }
        alist = alist->next;
    }
}

void breadthFirstTraversal(graph *a) {
    Que q;
    bool isVisited[MAXSIZE] = {FALSE};
    initQue(&q);
    for (int i = 0; i < MAXSIZE; ++i) {
        if(a->vertices[i].active == TRUE){
            if(isVisited[i] == FALSE){
                pushQue(&q, i);
                isVisited[i] = TRUE;
                bfs(a, &q, isVisited);
            }
        }
    }
    printf("\n");

}

void bfs(graph *a, Que *q, bool isVisited[MAXSIZE]) {
    while (q->size > 0){
        int vertexId = popQue(q);
        printf("%d ",vertexId);
        edge *list = a->vertices[vertexId].edgeList;
        while (list !=NULL){
            if(isVisited[list->vertex] == FALSE){
                pushQue(q, list->vertex);
                isVisited[list->vertex] = TRUE;
            }
            list = list->next;
        }
    }

}

void topologicalSort(graph *a) {
    stack m; initStack(&m);
    bool isVisited[MAXSIZE] = {FALSE};
    for (int i = 0; i < MAXSIZE; ++i) {
        if(a->vertices[i].active == TRUE){
            if(isVisited[i] == FALSE){

                topoSort(a, i, &m, isVisited);
            }
        }
    }
    while (m.size > 0){
        printf("%d ", popStack(&m));
    }

}

void topoSort(graph *a, int vertexId, stack *m, bool *isVisited) {
    isVisited[vertexId] = TRUE;
    edge *adj = a->vertices[vertexId].edgeList;
    while (adj != NULL){
        int vid = adj->vertex;
        if(isVisited[vid] == FALSE){
            topoSort(a,vid, m,isVisited);
        }
        adj = adj->next;
    }
    pushStack(m, vertexId);
}

bool isGraphConnected(graph *a) {
    bool ret = FALSE;
    bool isVisited[MAXSIZE] = {FALSE};
    int visited = 0;
    Que openSet;
    initQue(&openSet);
    pushQue(&openSet, 0);
    isVisited[0] = TRUE;
    while (openSet.size > 0){
        int vId = openSet.top->data;
        edge *adList = a->vertices[vId].edgeList;
        while (adList != NULL){
            if(isVisited[adList->vertex] == FALSE){
                isVisited[adList->vertex] = TRUE;
                pushQue(&openSet, adList->vertex);
            }
            adList = adList->next;
        }
        popQue(&openSet);
        visited++;
    }
    if (visited == a->size){
        ret = TRUE;
    }
    return ret;

}

int minIndex(int *a, int *closeSet) {
    int j=-1;
    int min = INF;
    for (int i = 0; i < MAXSIZE; ++i) {
        if(closeSet[i] == FALSE){
            if(min > a[i]){
                j=i;
                min = a[j];
            }
        }

    }
    return j;
}

int *dijkstra(graph *a, int origin, int **cost) {
    bool closeSet[MAXSIZE]={FALSE};
    int *path = malloc(MAXSIZE * sizeof(int));
    int *costTable = malloc(MAXSIZE * sizeof(int));
    for (int i = 0; i < MAXSIZE; ++i) {
        path[i] = -1;
        costTable[i] = INF;
    }
    costTable[origin] = 0;
    bool Flag = FALSE;
    while (!Flag){
        int v = minIndex(costTable, closeSet);
        if(v>-1){
            closeSet[v] = TRUE;
            edge *adj = a->vertices[v].edgeList;
            while (adj !=NULL){
                int vertex = adj->vertex;
                if(closeSet[vertex] == FALSE){
                    if(costTable[vertex] == INF){
                        costTable[vertex] = costTable[v] + adj->cost;
                        path[vertex] = v;
                    } else{
                        if(costTable[v] + adj->cost < costTable[vertex]){
                            costTable[vertex] = costTable[v] + adj->cost;
                            path[vertex] = v;
                        }
                    }
                }

                adj = adj->next;
            }
        } else{
            Flag = TRUE;
        }
    }
    *cost = costTable;
    return path;

}




