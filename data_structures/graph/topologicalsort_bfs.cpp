#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// bfs
vector<int> topologicalSort(vector<int> adj[], int N) {
    vector<int> indegree(N, 0);
    for (int i = 0; i < N; i++){
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) {
            indegree[*it]++;
        }
    }

    deque<int> q;
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0)
            q.push_back(i);
    }

    vector<int> res;
    int cnt = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop_front();
        res.push_back(u);
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            if (--indegree[*it] == 0)
                q.push_back(*it);
        }
        cnt++;
    }

    if (cnt != N)
        return res; // has a cycle
    return res;
}

void testTopologicalSort() {
    const int N = 6;
    vector<int> adj[N];
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[1].push_back(2);
    adj[4].push_back(3);
    adj[3].push_back(1);
    adj[4].push_back(0);

    auto res = topologicalSort(adj, N);
    for (auto x : res) cout << x << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testTopologicalSort();
    return 0;
}
