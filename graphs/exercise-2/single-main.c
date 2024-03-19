#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Queue {
    int size;
    int lastIndex;
    int* array;
} Queue;

void initializeQueue(Queue* queue, int size) {
    queue->size = size;
    queue->array = (int*) malloc(size * sizeof(int));
    queue->lastIndex = -1;
}

void enqueue(Queue* queue, int value) {
    queue->array[queue->lastIndex + 1] = value;

    queue->lastIndex = queue->lastIndex + 1;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    int ret = queue->array[0];

    for (int i = 0; i <= queue->lastIndex; i++) {
        queue->array[i] = queue->array[i+1];
    }

    queue->lastIndex = queue->lastIndex - 1;
    queue->size = queue->size - 1;

    return ret;
}

int isQueueEmpty(Queue* queue) {
    return queue->lastIndex == -1;
}

void destroyQueue(Queue* queue) {
    free(queue->array);
}

#define ADJACENCY_MATRIX int**

typedef struct {
    int source;
    int destination;
} Arc;

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

int getNumberOfArcs(ADJACENCY_MATRIX matrix, int size) {
    int ret = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 1) {
                ret++;
            }
        }
    }

    return ret / 2;
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