#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/adjacency_matrix/adjacency_matrix.h"

int main() {
    int numberOfVertices;
    int** matrix;
    Arc arc;

    scanf("%d", &numberOfVertices);
    matrix = initGraph(numberOfVertices);

    while (scanf("%d %d\n", &arc.source, &arc.destination) != EOF) {
        insertArc(matrix, arc);
    }

    int* visitedDFSArray = (int*) malloc(numberOfVertices * sizeof(int));
    memset(visitedDFSArray, 0, numberOfVertices * sizeof(int));

    printf("DFS\n");
    depthFirstSearch(matrix, numberOfVertices, 0, visitedDFSArray);

    int* visitedBFSArray = (int*) malloc(numberOfVertices * sizeof(int));
    memset(visitedBFSArray, 0, numberOfVertices * sizeof(int));

    printf("BFS\n");
    breadthFirstSearch(matrix, numberOfVertices, visitedBFSArray);

    free(visitedDFSArray);
    free(visitedBFSArray);

    destroyGraph(matrix, numberOfVertices);

    return 0;
}