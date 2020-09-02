#include <iostream>
#include <pthread.h>
#include <vector>
#include <queue>
#include "graph.hpp"

using namespace std;

// directed graph
// BFS
bool hasCycle(int V, vector<int> adj[]) {
    vector<int> in_degree(V, 0);
    for(int i = 0; i < V; i++) {
        for (int node: adj[i])
            in_degree[node]++;
    }

    queue<int> q;
    for(int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    for (auto c : in_degree) {
        cout << c << ", ";
    }
    cout << endl;

    vector<int> res;
    while(!q.empty()) {
        auto v = q.front(); q.pop();
        res.push_back(v);
        for (auto n : adj[v]) {
            --in_degree[n];
            cout << "<< " <<  in_degree[n] << " >> "<< endl;
            if (in_degree[n] == 0)
                q.push(n);
        }
    }

    for (auto c : in_degree) {
        cout << c << ", ";
    }
    cout << endl;

    return res.size() != V;
}

void testHasCycle() {
    Graph g;
    g.BuildSimpleGraph();
    cout << boolalpha << hasCycle(8, g.edges) << endl;
}

int main(int argc, char *argv[]) {
    testHasCycle();
    return 0;
}
