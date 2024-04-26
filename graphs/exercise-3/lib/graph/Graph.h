#ifndef SCC0503_ADJACENCY_MATRIX_H
#define SCC0503_ADJACENCY_MATRIX_H

#include <vector>
#include <limits>
#include <iostream>

class Arc {
public:
    int source;
    int destination;
    int weight;
    Arc(int src, int dest, int w) : source(src), destination(dest), weight(w) {}
};

class Graph {
private:
    std::vector<std::vector<int> > matrix;
    int size;

public:
    Graph(int size);
    void insertArc(const Arc& arc);
    void removeArc(const Arc& arc);
    void printArcs(int vertex) const;
    void printGraph() const;
    int getNumberOfArcs(bool isBidirectional) const;
    void depthFirstSearch(int currentVertex, std::vector<bool>& visited) const;
    void breadthFirstSearch(std::vector<bool>& visited) const;
    std::vector<int> dijkstra(int source, std::vector<int>& predecessor);
};

#endif