#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// DFS: directed graph
bool dfs(vector<int> adj[], int v, vector<bool>& visited, vector<bool>& recStack) {
    if (!visited[v]) {
        for (auto n : adj[v]) {
            visited[v] = true, recStack[v] = true;
            if (!visited[n] && dfs(adj, n, visited, recStack)) {
                return true;
            } else if (recStack[n])
                return true;
        }
    }
    recStack[v] = false;
    return false;
}

bool isCyclic(vector<int> adj[], int N) {
    vector<bool> visited(N, false);
    vector<bool> recStack(N, false);
    for (int i = 0; i < N; i++) {
        if (dfs(adj, i, visited, recStack))
            return true;
    }

    return false;
}

void testDfsCyclic() {
    const int N = 4;
    vector<int> adj[N];
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[3].push_back(2);
    adj[3].push_back(0);

    cout << boolalpha << isCyclic(adj, N) << endl;
}

int main(int argc, char *argv[]) {
    testDfsCyclic();
    return 0;
}
