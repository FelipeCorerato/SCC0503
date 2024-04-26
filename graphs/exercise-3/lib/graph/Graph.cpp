#include "Graph.h"
#include <queue>
#include <vector>
#include <iostream>
#include <limits>

Graph::Graph(int size) : size(size) {
    matrix.resize(size, std::vector<int>(size, std::numeric_limits<int>::max()));
    for (int i = 0; i < size; ++i) {
        matrix[i][i] = 0;
    }
}

void Graph::insertArc(const Arc& arc) {
    matrix[arc.source][arc.destination] = arc.weight;
}

void Graph::removeArc(const Arc& arc) {
    matrix[arc.source][arc.destination] = 0;
    matrix[arc.destination][arc.source] = 0;
}

void Graph::printArcs(int vertex) const {
    bool isFirstPrinted = true;
    for (int i = 0; i < size; i++) {
        if (matrix[vertex][i] == 1) {
            if (!isFirstPrinted) {
                std::cout << ", ";
            } else {
                isFirstPrinted = false;
            }

            std::cout << i;
        }
    }
}

void Graph::printGraph() const {
    for (int i = 0; i < size; i++) {
        std::cout << "Vertex " << i << ", arcs: ";
        printArcs(i);
        std::cout << "\n";
    }
}

int Graph::getNumberOfArcs(bool isBidirectional) const {
    int count = 0;
    for (const auto& row : matrix) {
        count += std::count(row.begin(), row.end(), 1);
    }
    return isBidirectional ? count : count / 2;
}

void Graph::depthFirstSearch(int currentVertex, std::vector<bool>& visited) const {
    visited[currentVertex] = true;
    std::cout << "visited " << currentVertex << "\n";

    for (int i = 0; i < size; i++) {
        if (matrix[currentVertex][i] && !visited[i]) {
            depthFirstSearch(i, visited);
        }
    }
}

void Graph::breadthFirstSearch(std::vector<bool>& visited) const {
    std::queue<int> queue;
    queue.push(0);
    visited[0] = true;

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        std::cout << "visited " << currentVertex << "\n";

        for (int i = 0; i < size; i++) {
            if (matrix[currentVertex][i] && !visited[i]) {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
}

std::vector<int> Graph::dijkstra(int source, std::vector<int>& predecessor) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > pq;
    std::vector<int> dist(size, std::numeric_limits<int>::max());
    predecessor.assign(size, -1);

    pq.push(std::make_pair(0, source));
    dist[source] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < size; ++v) {
            if (matrix[u][v] != std::numeric_limits<int>::max()) {
                int alt = dist[u] + matrix[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    predecessor[v] = u;
                    pq.push(std::make_pair(dist[v], v));
                }
            }
        }
    }

    return dist;
}
