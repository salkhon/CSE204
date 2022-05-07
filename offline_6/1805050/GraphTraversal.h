//
// Created by Salman Khondker on 21-Apr-21.
//

#ifndef OFFLINE6_GRAPHTRAVERSAL_H
#define OFFLINE6_GRAPHTRAVERSAL_H

#include "Graph.h"
#include <vector>
#include <queue>

class DFS {
    std::vector<bool> marked;
    std::vector<int> visited_by;
    Graph& graph;

public:
    DFS(Graph& graph);

    void dfs(int source, int visit_id);

    bool is_marked(int v);

    int vertex_visited_by(int v);

private:
    void dfs_recur(int v, int visit_id);
};

DFS::DFS(Graph& graph) :
    marked(graph.getNumVertices(), false),
    visited_by(graph.getNumVertices()),
    graph(graph) {}

void DFS::dfs(int source, int visit_id) {
    if (!this->marked[source]) {
        this->marked[source] = true;
        this->visited_by[source] = visit_id;
        dfs_recur(source, visit_id);
    }
}

void DFS::dfs_recur(int v, int visit_id) {
    for (int adj : this->graph.adjacent(v)) {
        if (!this->marked[adj]) {
            this->marked[adj] = true;
            this->visited_by[adj] = visit_id;
            dfs_recur(adj, visit_id);
        }
    }
}

bool DFS::is_marked(int v) {
    return this->marked[v];
}

int DFS::vertex_visited_by(int v) {
    return this->visited_by[v];
}

class BFS {
    Graph graph;
    std::vector<bool> marked;
    std::vector<int> visited_by;

public:
    BFS(Graph& graph);

    void bfs(int source, int visit_id);

    bool is_marked(int vertex);

    int vertex_visited_by(int vertex);

private:
    void visit(int vertex, std::queue<int>& vertex_q, int visit_id);
};

BFS::BFS(Graph& graph) :
    graph(graph),
    marked(graph.getNumVertices(), false),
    visited_by(graph.getNumVertices()) {}

void BFS::bfs(int source, int visit_id) {
    std::queue<int> vertex_q;
    vertex_q.push(source);
    int v;
    while (!vertex_q.empty()) {
        v = vertex_q.front();
        vertex_q.pop();
        visit(v, vertex_q, visit_id);
    }
}

void BFS::visit(int vertex, std::queue<int>& vertex_q, int visit_id) {
    if (!this->marked[vertex]) {
        this->marked[vertex] = true;
        this->visited_by[vertex] = visit_id;
        for (int adj : this->graph.adjacent(vertex)) {
            if (!this->marked[adj]) {
                vertex_q.push(adj);
            }
        }
    }
}

bool BFS::is_marked(int vertex) {
    return this->marked[vertex];
}

int BFS::vertex_visited_by(int vertex) {
    return this->visited_by[vertex];
}


#endif //OFFLINE6_GRAPHTRAVERSAL_H
