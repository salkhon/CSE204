//
// Created by Salman Khondker on 21-Apr-21.
//

#ifndef OFFLINE6_GRAPH_H
#define OFFLINE6_GRAPH_H

#include <vector>

class Graph {
    const int num_vertices;
    int num_edges;
    std::vector<std::vector<int>> adj;
public:
    Graph(int num_vertices);

    int getNumVertices() const;

    void addEdge(int v, int w);

    const std::vector<int>& adjacent(int v);
};

Graph::Graph(int num_vertices) :
    num_vertices(num_vertices), num_edges(0), adj(num_vertices) {}

void Graph::addEdge(int v, int w) {
    this->adj[v].push_back(w);
    this->adj[w].push_back(v);
    this->num_edges++;
}

const std::vector<int>& Graph::adjacent(int v) {
    return this->adj[v];
}

int Graph::getNumVertices() const {
    return num_vertices;
}


#endif //OFFLINE6_GRAPH_H
