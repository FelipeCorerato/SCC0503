#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./adjacency_matrix.h"

#include "../queue/queue.h"

ADJACENCY_MATRIX initGraph(int size) {
    ADJACENCY_MATRIX graph = (ADJACENCY_MATRIX) malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        graph[i] = (int*) malloc(size * sizeof(int));
        memset(graph[i], 0, size * sizeof(int));
    }

    return graph;
}

int destroyGraph(ADJACENCY_MATRIX graph, int size) {
    for(int i = 0; i < size; i++) {
        free(graph[i]);
    }

    free(graph);

    return 0;
}

int insertArc(ADJACENCY_MATRIX matrix, Arc arc) {
    matrix[arc.source][arc.destination] = 1;
    matrix[arc.destination][arc.source] = 1;

    return 0;
}

int removeArc(ADJACENCY_MATRIX matrix, Arc arc) {
    matrix[arc.source][arc.destination] = 0;
    matrix[arc.destination][arc.source] = 0;

    return 0;
}

int printArcs(ADJACENCY_MATRIX matrix, int vertex, int size) {
    int isFirstPrinted = 1;
    for (int i = 0; i < size; i++) {
        if (matrix[vertex][i] == 1) {
            if (!isFirstPrinted) {
                printf(", ");
            } else {
                isFirstPrinted = 0;
            }

            printf("%d", i);
        }
    }

    return 0;
}

int printGraph(ADJACENCY_MATRIX matrix, int size) {
    for (int i = 0; i < size; i++) {
        printf("Vertex %d, arcs: ", i);

        printArcs(matrix, i, size);

        printf("\n");
    }

    return 0;
}

int getNumberOfArcs(ADJACENCY_MATRIX matrix, int size, int isBidirectional) {
    int ret = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 1) {
                ret++;
            }
        }
    }

    return isBidirectional ? ret : ret / 2;
}

int depthFirstSearch(ADJACENCY_MATRIX matrix, int size, int currentVertex, int* visited) {
    visited[currentVertex] = 1;
    printf("visited %d\n", currentVertex);

    for (int i = 0; i < size; i++) {
        if (matrix[currentVertex][i] && !visited[i]) {
            depthFirstSearch(matrix, size, i, visited);
        }
    }

    return 0;
}

int breadthFirstSearch(ADJACENCY_MATRIX matrix, int size, int* visited) {
    Queue queue;
    initializeQueue(&queue, size);

    int initialVertex = 0;

    visited[initialVertex] = 1;
    enqueue(&queue, initialVertex);

    while (!isQueueEmpty(&queue)) {
        int currentVertex = dequeue(&queue);
        printf("visited %d\n", currentVertex);

        for (int i = 0; i < size; i++) {
            if (matrix[currentVertex][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(&queue, i);
            }
        }
    }

    destroyQueue(&queue);

    return 0;
}