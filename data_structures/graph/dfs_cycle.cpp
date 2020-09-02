#include <iostream>
#include <vector>
#include <deque>
#include "graph.hpp"

using namespace std;

// undirected graph

// DFS
bool hasCycle(vector<int> adj[], int v, vector<bool>& visited, int parent) {
    visited[v] = true;
    for (auto it = adj[v].begin(); it < adj[v].end(); ++it) {
        if (!visited[*it]) {
            if (hasCycle(adj, *it, visited, v))
                return true;
        } else if (*it != parent) {
            return true;
        }
    }

    return false;
}

// BFS
bool isCycle(vector<int> adj[], int v, int N, vector<bool>& visited) {
    visited[v] = true;
    vector<int> parent(N, -1);
    deque<int> q;
    q.push_back(v);
    while (!q.empty()) {
        v = q.front(); q.pop_front();
        for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
            if (!visited[*it]) {
                visited[*it] = true;
                q.push_back(*it);
                parent[*it] = v;
            } else if (parent[*it] != v) {
                return true;
            }
        }
    }

    return false;
}

void testHasCycle() {
    Graph g;
    g.BuildSimpleGraph();

    bool has = false;
    vector<bool> visited(g.V, false);
    // for (int i = 0; i < N; i++) {
    //     if (!visited[i]) {
    //         if (hasCycle(adj, i, visited, -1)) {
    //             has = true;
    //             break;
    //         }
    //     }
    // }
    // has = hasCycle(g.edges, 0, visited, -1);
    // for (int i = 0; i < g.V; i++) {
    //     if (!visited[i] && isCycle(g.edges, i, g.V, visited))
    //         has = true;
    // }
    has = isCycle(g.edges, 0, g.V, visited);

    cout << boolalpha << has << endl;
}

int main(int argc, char *argv[]) {
    testHasCycle();
    return 0;
}
