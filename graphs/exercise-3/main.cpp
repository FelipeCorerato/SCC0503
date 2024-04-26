#include <iostream>
#include <vector>

#include "./lib/graph/Graph.h"

void printPath(int v, const std::vector<int>& predecessor) {
    if (predecessor[v] == -1) {
        std::cout << v;
        return;
    }

    printPath(predecessor[v], predecessor);
    std::cout << " -> " << v;
}

int main() {
    int numberOfVertices;
    std::cin >> numberOfVertices;
    Graph graph(numberOfVertices);

    int source, destination, weight;
    while (std::cin >> source >> destination >> weight) {
        Arc arc(source, destination, weight);
        graph.insertArc(arc);
    }

    for (int i = 0; i < numberOfVertices; ++i) {
        std::vector<int> predecessor;
        std::vector<int> distances = graph.dijkstra(i, predecessor);

        std::cout << "Node " << i << ":\n";
        for (int dest = 0; dest < numberOfVertices; ++dest) {
            std::cout << "Distance from " << i << " to " << dest << " = ";
            if (distances[dest] == std::numeric_limits<int>::max()) {
                std::cout << "infinity\n";
            } else {
                std::cout << distances[dest] << "\n";

                if (distances[dest] > 0) {
                    std::cout << "Path: ";
                    printPath(dest, predecessor);
                    std::cout << "\n";
                }
            }
        }

        if (i < numberOfVertices - 1) {
            std::cout << "\n";
        }
    }

    return 0;
}