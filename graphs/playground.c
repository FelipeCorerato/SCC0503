#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define Weight int
#define INVALID_WEIGHT (-1)

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct AdjacencyDirectedGraph {
    int numberOfVertices;
    int numberOfEdges;
    Node** adjacencyList;
} AdjacencyDirectedGraph;

void initializeGraph(AdjacencyDirectedGraph* graph, int numberOfVertices) {
    graph->numberOfVertices = numberOfVertices;
    graph->numberOfEdges = 0;

    graph->adjacencyList = (Node**) malloc(numberOfVertices * sizeof(Node*));

    for(int i = 0; i < numberOfVertices; i++) {
        graph->adjacencyList[i] = NULL;
    }
}

void printGraph(AdjacencyDirectedGraph* graph) {
    printf("Number of vertices: %d\n", graph->numberOfVertices);
    printf("Number of edges: %d\n", graph->numberOfEdges);

    for(int i = 0; i < graph->numberOfVertices; i++) {
        printf("%d ", graph->adjacencyList[i]->vertex);

        Node* actual = graph->adjacencyList[i]->next;
        while (actual != NULL) {
            printf("%d ", actual->vertex);
            actual = actual->next;
        }

        printf("\n");
    }
}

void freeGraph(AdjacencyDirectedGraph* graph){
    Node* actual, *deleted;
    for(int i = 0; i < graph->numberOfVertices; i++) {
        actual = graph->adjacencyList[i];
        while (actual != NULL) {
            deleted = actual;
            actual = actual ->next;
            free(deleted);
        }

        free(graph->adjacencyList[i]);
    }
    free(graph->adjacencyList);

    graph->numberOfVertices = 0;
    graph->numberOfEdges = 0;
    graph->adjacencyList = NULL;
}

void addEdge(AdjacencyDirectedGraph* graph, int source, int destination, int weight) {
    Node* actual = graph->adjacencyList[source];
    while(actual->next != NULL && actual->vertex < destination) {
        actual = actual->next;
    }

    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = destination;
    newNode->next = actual->next;
    newNode->weight = weight;

    actual->next = newNode;
    graph->numberOfEdges++;
}

void removeEdge(AdjacencyDirectedGraph* graph, int source, int destination) {
    Node* actual = graph->adjacencyList[source];
    while(actual->next != NULL && actual->vertex < destination) {
        actual = actual->next;
    }

    bool found = actual->next != NULL && actual->vertex == destination;
    if (found) {
        Node* temp = ;
    }

    graph->numberOfEdges--;
}

int aux(AdjacencyDirectedGraph* graph, int source) {
    Node* vertex = graph->adjacencyList[source];

    if(vertex == NULL || vertex->next == NULL) {
        return INVALID_WEIGHT;
    }

    vertex = vertex->next;

    int lightest = -1;
    while(vertex != NULL) {
        if (lightest == INVALID_WEIGHT) {
            lightest = vertex->weight;
            continue;
        }

        lightest = lightest < vertex->weight ? lightest : vertex->weight;
        vertex = vertex->next;
    }

    return lightest;
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

