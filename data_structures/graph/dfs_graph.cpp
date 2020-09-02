#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "graph.hpp"

using namespace std;

void dfs(list<int> adj[], int index, vector<bool>& visited, vector<int>& res) {
    res.push_back(index);
    visited[index] = true;
    for (auto it = adj[index].begin(); it != adj[index].end(); ++it) {
        if (!visited[*it])
            dfs(adj, *it, visited, res);
    }
}

void bfs(list<int> adj[], int index, vector<bool>& visited, vector<int>& res) {
    visited[index] = true;
    deque<int> q;
    q.push_back(index);
    res.push_back(index);
    while(!q.empty()) {
        index = q.front(); q.pop_front();
        for (auto it = adj[index].begin(); it != adj[index].end(); ++it) {
            if (!visited[*it]) {
                visited[*it] = true;
                res.push_back(*it);
                q.push_back(*it);
            }
        }
    }
}

void testDfsGraph() {
    Graph1 g1;
    g1.BuildSimpleGraph();

    vector<bool> visited(g1.V);
    vector<int> res;
    
    dfs(g1.edges, 0, visited, res);

    for (auto x : res) cout << x << " ";
    cout << endl;
}

void testBFSGraph() {
    Graph1 g1;
    g1.BuildSimpleGraph();

    vector<int> res;
    vector<bool> visited(g1.V, false);
    bfs(g1.edges, 0, visited, res);

    for (auto x : res) cout << x << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testDfsGraph();
    testBFSGraph();
    return 0;
}
