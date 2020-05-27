#include <stdio.h>
#include "graph.h"
#include "stack.h"
int main() {

    graph A;
    init_graph(&A);
    for (int i = 0; i < 9; ++i) {
        addVertex(&A, i);
    }
    addEdge(&A,0,1,0,4);
    addEdge(&A,0,7,0,8);
    addEdge(&A,1,7,0,11);
    addEdge(&A,1,2,0,8);
    addEdge(&A,2,8,0,2);
    addEdge(&A,2,3,0,7);
    addEdge(&A,2,5,0,4);
    addEdge(&A,3,4,0,9);
    addEdge(&A,3,5,0,14);
    addEdge(&A,5,4,0,10);
    addEdge(&A,6,5,0,2);
    addEdge(&A,6,8,0,6);
    addEdge(&A,7,6,0,1);
    addEdge(&A,7,8,0,7);


    depthFirstTraversal(&A, 0);
    int *cost;
    int *path = dijkstra(&A, 0, &cost);
    int **c;
    int **p = allPairShortestPath(&A, &c);
    displayPathToAllVertices(path,cost,0);
    breadthFirstTraversal(&A);
    topologicalSort(&A);
    int n = isGraphConnected(&A);
    printf("\n%d\n", n);


    graph B;
    init_graph(&B);
    addVertex(&B, 0);
    addVertex(&B, 1);
    addVertex(&B, 2);
    addVertex(&B, 3);

    addEdge(&B, 0,1,0,1);
    addEdge(&B,1,2,0,1);
    addEdge(&B,3,2,0,1);
    addEdge(&B,0,2,0,1);

    bool cy = isCyclePresent(&B);

    printf("is Cycle: %d", cy);

    int *parent = MST(&A);
    int nm=45;

    return 0;
}