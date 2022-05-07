#include <iostream>
#include <fstream>
#include "Graph.h"
#include "GraphTraversal.h"
#include <climits>
using namespace std;


void output_to_file(int total_collected, int total_pieces, std::vector<int>& pieces_collected_by_friend) {
    int f = pieces_collected_by_friend.size();
    std::ofstream file;
    file.open("output.txt", std::ios::app);
    file << "-----------------Execution start-------------------" << std::endl;
    if (total_collected == total_pieces) {
        file << "Mission Accomplished" << std::endl;
    } else {
        file << "Mission Impossible" << std::endl;
    }

    file << total_collected << " out of " << total_pieces << " pieces are collected" << std::endl;
    for (int fr = 0; fr < f; fr++) {
        file << fr << " collected " << pieces_collected_by_friend[fr] << " pieces" << std::endl;
    }
    file << "--------------Execution end---------------\n" << std::endl;
}

void solve_by_dfs(Graph& graph, int total_pieces,
    std::vector<int>& city_started_by_friend,
    std::vector<int>& pieces_in_city) {
    size_t f = city_started_by_friend.size();
    std::vector<int> pieces_collected_by_friend(f, 0);
    int total_collected = 0;

    DFS dfs(graph);

    // DFS by each friend from their starting city
    for (int fid = 0; fid < f; fid++) {
        dfs.dfs(city_started_by_friend[fid], fid);
    }

    for (int city = 0, fr; city < graph.getNumVertices(); city++) {
        if (dfs.is_marked(city)) {
            fr = dfs.vertex_visited_by(city);
            pieces_collected_by_friend[fr] += pieces_in_city[city];
            total_collected += pieces_in_city[city];
        }
    }

    output_to_file(total_collected, total_pieces, pieces_collected_by_friend);
}

void solve_by_bfs(Graph& graph, int total_pieces,
    std::vector<int>& city_started_by_friend,
    std::vector<int>& pieces_in_city) {
    size_t f = city_started_by_friend.size();
    std::vector<int> pieces_collected_by_friend(f, 0);
    int total_collected = 0;

    BFS bfs(graph);

    // BFS by each friend from their starting city
    for (int fid = 0; fid < f; fid++) {
        bfs.bfs(city_started_by_friend[fid], fid);
    }

    for (int city = 0, fr; city < graph.getNumVertices(); city++) {
        if (bfs.is_marked(city)) {
            fr = bfs.vertex_visited_by(city);
            pieces_collected_by_friend[fr] += pieces_in_city[city];
            total_collected += pieces_in_city[city];
        }
    }

    output_to_file(total_collected, total_pieces, pieces_collected_by_friend);
}

int main() {
    std::cout << "Solve by 1. DSF or 2. BFS?" << std::endl;
    std::cout << "Enter 1 or 2: ";
    int op;
    std::cin >> op;

    int c, r, l, f;
    std::cin >> c >> r >> l >> f;

    Graph graph(c);

    // cities connected by roads
    for (int i = 0, c1, c2; i < r; i++) {
        std::cin >> c1 >> c2;
        graph.addEdge(c1, c2);
    }

    std::vector<int> pieces_in_city(c, 0);
    int total_pieces = 0;

    // number of pieces in city
    for (int i = 0, cid, p; i < l; i++) {
        std::cin >> cid >> p;
        pieces_in_city[cid] = p;
        total_pieces += p;
    }

    std::vector<int> city_started_by_friend(f);

    // starting city of friend
    for (int i = 0, cid, fid; i < f; i++) {
        std::cin >> cid >> fid;
        city_started_by_friend[fid] = cid;
    }

    if (op == 1) {
        solve_by_dfs(graph, total_pieces, city_started_by_friend, pieces_in_city);
    } else if (op == 2) {
        solve_by_bfs(graph, total_pieces, city_started_by_friend, pieces_in_city);
    }

    return 0;
}
