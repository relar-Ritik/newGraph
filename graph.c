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

int minIndex(int *a, bool *closeSet) {
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

void displayPathToAllVertices(int *path, int *cost, int origin) {
    for (int i = 0; i < MAXSIZE; ++i) {
        if(i != origin && cost[i] != INF){
            printf("cost: %d\n", cost[i]);
            printf("%d-->", i);
            int j = path[i];
            while (j!=origin){
                printf("%d-->", j);
                j = path[j];
            }
            printf("%d\n", j);
        }
    }
}

int** allPairShortestPath(graph *a, int ***cost) {
    int **costMatrix = malloc(MAXSIZE * sizeof(int*));
    int **pathMatrix = malloc(MAXSIZE * sizeof(int*));
    for (int i = 0; i < MAXSIZE; ++i) {
        costMatrix[i] = malloc(MAXSIZE * sizeof(int));
        pathMatrix[i] = malloc(MAXSIZE * sizeof(int));
        for (int j = 0; j < MAXSIZE; ++j) {
            costMatrix[i][j] = INF;
            pathMatrix[i][j] = -1;
        }
    } //allocate memory for the matrix as well as set them to INF
    for (int j = 0; j < MAXSIZE; ++j) {
        if(a->vertices[j].active == TRUE){
            edge *adj = a->vertices[j].edgeList;
            while (adj !=NULL){
                int vertex = adj->vertex;
                costMatrix[j][vertex] = adj->cost;
                pathMatrix[j][vertex] = j;
                adj = adj->next;
            }
        }

    } //init costMatrix and pathMatrix
    for (int k = 0; k < MAXSIZE; ++k) {
        if(a->vertices[k].active == TRUE){
            for (int i = 0; i < MAXSIZE; ++i) {
                if(a->vertices[i].active == TRUE){
                    for (int j = 0; j < MAXSIZE; ++j) {
                        if(a->vertices[j].active == TRUE){
                            if ( costMatrix[i][k] != INF &&
                                 costMatrix[k][j] != INF &&
                                 costMatrix[i][k] + costMatrix[k][j] < costMatrix[i][j]
                                    ){
                                costMatrix[i][j] = costMatrix[i][k] + costMatrix[k][j];
                                pathMatrix[i][j] = k;
                            }


                        }
                    }
                }

            }
        }

    }
    *cost = costMatrix;
    return pathMatrix;
}

bool isCyclePresent(graph *a) {
    bool ret = FALSE;
    bool isVisited[MAXSIZE] = {FALSE};
    for (int i = 0; i < MAXSIZE; ++i) {
        if(a->vertices[i].active == TRUE){
           if(isVisited[i] == FALSE){
               isVisited[i] = TRUE;
               edge *adj  = a->vertices[i].edgeList;
               while (adj != NULL){
                   int child = adj->vertex;
                   if(isCyclerecur(a, child,isVisited, i) ==  TRUE){
                       return TRUE;
                   }
                   adj = adj->next;
               }
           }
        }
    }
    return ret;
}

bool isCyclerecur(graph *a, int vertex, bool *isVisited, int parent) {
    if(isVisited[vertex] == TRUE){
        return TRUE;
    }
    bool ret = FALSE;
    isVisited[vertex] = TRUE;
    edge *adj = a->vertices[vertex].edgeList;
    while (adj != NULL){
        if(adj->vertex != parent){
            ret = isCyclerecur(a,adj->vertex,isVisited,vertex);
            if(ret == TRUE){
                return TRUE;
            }
        }
        adj = adj->next;
    }

    return FALSE;
}

int* MST(graph *a) {
    int *parent = malloc(MAXSIZE*sizeof(int));
    for (int i = 0; i <MAXSIZE ; ++i) {
        parent[i]=-1;
    }

    int start = -1;
    for (int j = 0; j < MAXSIZE && start == -1; ++j) {
        if(a->vertices[j].active==TRUE) start = j;
    }
    parent[start] = start;
    int counter = 1;
    while (counter < a->size){
        int nextVertex = getMinEdge(a, parent, &start);
        parent[nextVertex] = start;
        counter++;
    }
    return parent;

}

int getMinEdge(graph *a, int *parent, int *start) {
    int index = -1;
    int min = INF;
    for (int i = 0; i < MAXSIZE; ++i) {
        if(parent[i] != -1){
            edge *adj = a->vertices[i].edgeList;
            while (adj != NULL){
                if(parent[adj->vertex] == -1 && min > adj->cost){
                    index = adj->vertex;
                    min = adj->cost;
                    *start = i;
                }
                adj = adj->next;
            }
        }
    }
    return index;
}




