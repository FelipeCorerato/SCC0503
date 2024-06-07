#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define Weight int
#define INVALID_WEIGHT (-1)

typedef struct AdjacencyDirectedGraph {
    int numberOfVertices;
    int numberOfEdges;
    Weight** adjacencyMatrix;
} AdjacencyDirectedGraph;

void initializeGraph(AdjacencyDirectedGraph* graph, int numberOfVertices) {
    graph->numberOfVertices = numberOfVertices;
    graph->numberOfEdges = 0;

    graph->adjacencyMatrix = (Weight**) malloc(numberOfVertices * sizeof(Weight*));
    for(int i = 0; i < numberOfVertices; i++) {
        graph->adjacencyMatrix[i] = (Weight*) malloc(numberOfVertices * sizeof(Weight));

        for(int j = 0; j < numberOfVertices; j++) {
            graph->adjacencyMatrix[i][j] = INVALID_WEIGHT;
        }
    }
}

void printGraph(AdjacencyDirectedGraph* graph) {
    printf("Number of vertices: %d\n", graph->numberOfVertices);
    printf("Number of edges: %d\n", graph->numberOfEdges);

    for(int i = 0; i < graph->numberOfVertices; i++) {
        for(int j = 0; j < graph->numberOfVertices; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void freeGraph(AdjacencyDirectedGraph* graph){
    for(int i = 0; i < graph->numberOfVertices; i++) {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);

    graph->numberOfVertices = 0;
    graph->numberOfEdges = 0;
    graph->adjacencyMatrix = NULL;
}

void addEdge(AdjacencyDirectedGraph* graph, int source, int destination, int weight) {
    if (graph->adjacencyMatrix[source][destination] == INVALID_WEIGHT) {
        graph->numberOfEdges++;
    }

    graph->adjacencyMatrix[source][destination] = weight;
}

void removeEdge(AdjacencyDirectedGraph* graph, int source, int destination) {
    graph->adjacencyMatrix[source][destination] = INVALID_WEIGHT;
    graph->numberOfEdges--;
}

bool edgeExists(AdjacencyDirectedGraph* graph, int source, int destination) {
    return graph->adjacencyMatrix[source][destination] != INVALID_WEIGHT;
}

int getNumberOfVertices(AdjacencyDirectedGraph* graph) {
    return graph->numberOfVertices;
}

int getNumberOfEdgesInMemory(AdjacencyDirectedGraph* graph) {
    return graph->numberOfEdges;
}

int getNumberOfEdgesByCalculating(AdjacencyDirectedGraph* graph) {
    int counter = 0;
    for (int i = 0; i < graph->numberOfEdges; i++) {
        for (int j = 0; j < graph->numberOfEdges; j++) {
            if (graph->adjacencyMatrix[i][j] != INVALID_WEIGHT) {
                counter++;
            }
        }
    }

    return counter;
}

int getVertexDegree(AdjacencyDirectedGraph* graph, int vertex) {
    int counter = 0;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] != INVALID_WEIGHT) {
            counter++;
        }

        if (graph->adjacencyMatrix[i][vertex] != INVALID_WEIGHT) {
            counter++;
        }
    }

    return counter;
}

bool hasNeighbors(AdjacencyDirectedGraph* graph, int vertex) {
    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] != INVALID_WEIGHT) {
            return true;
        }
    }

    return false;
}

