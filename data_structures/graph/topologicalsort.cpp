#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// DFS fashion
void topo(vector<int> adj[], int v, vector<bool>& visited, stack<int>& s) {
    visited[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!visited[*it]) {
            topo(adj, *it, visited, s);
        }
    }
    s.push(v);
}

vector<int> topologicalSort(vector<int> adj[], int N) {
    vector<bool> visited(N, false);
    stack<int> s;
    for (int i = 0; i < N; i++) {
        if (!visited[i])
            topo(adj, i, visited, s);
    }

    vector<int> res;
    while (!s.empty()) {
        res.push_back(s.top());
        s.pop();
    }

    return res;
}

void testTopologicalSort() {
    const int N = 6;
    vector<int> adj[N];
    adj[2].push_back(1);
    adj[3].push_back(1);
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[0].push_back(4);
    adj[4].push_back(3);
    auto res = topologicalSort(adj, N);
    for (auto x : res) cout << x << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testTopologicalSort();
    return 0;
}
