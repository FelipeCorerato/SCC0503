#include <stdio.h>

#include "./lib/adjacency_matrix.h"

int main() {
    int numberOfVertices;
    int** matrix;
    Arc arc;

    scanf("%d", &numberOfVertices);
    matrix = initGraph(numberOfVertices);

    while (scanf("%d %d\n", &arc.source, &arc.destination) != EOF) {
        insertArc(matrix, arc);
    }

    int numberOfArcs = getNumberOfArcs(matrix, numberOfVertices);
    printf("Total of vertices: %d, total of arcs: %d\n", numberOfVertices, numberOfArcs);

    printGraph(matrix, numberOfVertices);

    destroyGraph(matrix, numberOfVertices);

    return 0;
}
