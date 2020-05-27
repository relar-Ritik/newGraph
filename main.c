#include <stdio.h>
#include "graph.h"
#include "stack.h"
int main() {

    graph A;
    init_graph(&A);
    for (int i = 0; i < 7; ++i) {
        addVertex(&A, i);
    }
    addEdge(&A,0,1,1,5);
    addEdge(&A, 0,2,1,5);
    addEdge(&A, 1,3,1,5);
    addEdge(&A, 3,4,1,5);
    addEdge(&A, 2,4,1,6);
    addEdge(&A, 2,3,1,7);
    addEdge(&A, 5,6,1,8);
    addEdge(&A, 4,5,1,9);
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




    return 0;
}