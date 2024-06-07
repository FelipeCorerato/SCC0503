#include <stdlib.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

typedef struct AdjacencyGraph {
    int numberOfVertices;
    int numberOfEdges;
    bool** adjacencyMatrix;
} AdjacencyGraph;

void initializeGraph(AdjacencyGraph* graph, int numberOfVertices) {
    graph->numberOfVertices = numberOfVertices;
    graph->numberOfEdges = 0;

    graph->adjacencyMatrix = (bool**) malloc(numberOfVertices * sizeof(bool*));
    for(int i = 0; i < numberOfVertices; i++) {
        graph->adjacencyMatrix[i] = (bool*) malloc(numberOfVertices * sizeof(bool));

        for(int j = 0; j < numberOfVertices; j++) {
            graph->adjacencyMatrix[i][j] = false;
        }
    }
}

void printGraph(AdjacencyGraph* graph) {
    printf("Number of vertices: %d\n", graph->numberOfVertices);
    printf("Number of edges: %d\n", graph->numberOfEdges);

    for(int i = 0; i < graph->numberOfVertices; i++) {
        for(int j = 0; j < graph->numberOfVertices; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void freeGraph(AdjacencyGraph* graph){
    for(int i = 0; i < graph->numberOfVertices; i++) {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);

    graph->numberOfVertices = 0;
    graph->numberOfEdges = 0;
    graph->adjacencyMatrix = NULL;
}

void addEdge(AdjacencyGraph* graph, int source, int destination) {
    graph->adjacencyMatrix[source][destination] = true;
    graph->adjacencyMatrix[destination][source] = true;
    graph->numberOfEdges++;
}

void removeEdge(AdjacencyGraph* graph, int source, int destination) {
    graph->adjacencyMatrix[source][destination] = false;
    graph->adjacencyMatrix[destination][source] = false;
    graph->numberOfEdges--;
}

bool edgeExists(AdjacencyGraph* graph, int source, int destination) {
    return graph->adjacencyMatrix[source][destination] == true;
}

int getNumberOfVertices(AdjacencyGraph* graph) {
    return graph->numberOfVertices;
}

int getNumberOfEdgesInMemory(AdjacencyGraph* graph) {
    return graph->numberOfEdges;
}

int getNumberOfEdgesByCalculating(AdjacencyGraph* graph) {
    int counter = 0;
    for (int i = 0; i < graph->numberOfEdges; i++) {
        for (int j = 0; j < graph->numberOfEdges; j++) {
            if (graph->adjacencyMatrix[i][j] == true) {
                counter++;
            }
        }
    }

    return counter;
}

int getVertexDegree(AdjacencyGraph* graph, int vertex) {
    int counter = 0;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] == true) {
            counter++;
        }
    }

    return counter;
}

bool hasNeighbors(AdjacencyGraph* graph, int vertex) {
    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] == true) {
            return true;
        }
    }

    return false;
}

bool hasNeighborsByVertexDegree(AdjacencyGraph* graph, int vertex) {
    return getVertexDegree(graph, vertex) > 0;
}
