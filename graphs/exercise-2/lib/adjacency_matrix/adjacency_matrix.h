#ifndef SCC0503_ADJACENCY_MATRIX_H
#define SCC0503_ADJACENCY_MATRIX_H

#define ADJACENCY_MATRIX int**

typedef struct {
    int source;
    int destination;
} Arc;

ADJACENCY_MATRIX initGraph(int size);
int destroyGraph(ADJACENCY_MATRIX graph, int size);
int insertArc(ADJACENCY_MATRIX matrix, Arc arc);
int removeArc(ADJACENCY_MATRIX matrix, Arc arc);
int printArcs(ADJACENCY_MATRIX matrix, int vertex, int size);
int printGraph(ADJACENCY_MATRIX matrix, int size);
int getNumberOfArcs(ADJACENCY_MATRIX matrix, int size, int isBidirectional);
int depthFirstSearch(ADJACENCY_MATRIX matrix, int size, int currentVertex, int* visited);
int breadthFirstSearch(ADJACENCY_MATRIX matrix, int size, int* visited);

#endif
