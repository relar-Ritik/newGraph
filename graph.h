//
// Created by ritik on 26/05/20.
//

#ifndef G2_GRAPH_H
#define G2_GRAPH_H
#define MAXSIZE 200
#include "linkedList.h"
#include "que.h"
#include "stack.h"
#include "edgeList.h"


typedef struct v_tag{
    int active;
    edge *edgeList;
}vertex;

typedef struct graph_type{
    int size;
    vertex vertices[MAXSIZE];
}graph;

void init_graph(graph *a);
void addVertex(graph *a, int V);
void addEdge(graph *a, int V1, int V2, int is_directed, int cost);
void depthFirstTraversal(graph *a, int origin);
void dfs(graph *a, int vertex,bool isVisited[MAXSIZE]);
void breadthFirstTraversal(graph *a);
void bfs(graph *a, Que *q, bool isVisited[MAXSIZE]);
void topologicalSort(graph *a);
void topoSort(graph *a, int vertexId ,stack *m, bool isVisited[MAXSIZE]);
bool isGraphConnected(graph *a);
int minIndex(int *a, int *closeSet);
int *dijkstra(graph *a, int origin, int **cost);


#endif //G2_GRAPH_H
