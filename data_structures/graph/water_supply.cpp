#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int bfs(vector<int> adj[], vector<int>& cities, int N, int k, vector<bool>& visited) {
    visited[k] = true;
    int count = 0;
    queue<int> q;
    q.push(k);
    while (!q.empty()) {
        int p = q.front(); q.pop();
        for (int i = 0; i < adj[p].size(); i++) {
            if (!visited[adj[p][i]]) {
                if (adj[p][i] == 0) {
                    count++;
                    visited[p] = true;
                } else if (adj[p][i] == 1) {
                    count++;
                }
            }
        }
    }
    return count + 1;
}

int waterSupply(vector<int> adj[], vector<int>& cities, int N) {
    vector<bool> visited(N, false);
    int maxCnt = 1, res;

    for (int i = 0; i < N; i++) {
        if (cities[i] == 0 && !visited[i]) {
            res = bfs(adj, cities, N, i, visited);
            if (maxCnt < res) maxCnt = res;
        }
    }

    return maxCnt;
}

void testWaterSupple() {
    const int N = 4;
    vector<int> cities = {0, 1, 1, 0};
    vector<int> adj[N];
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);

    cout << waterSupply(adj, cities, N) << endl;
}

int main(int argc, char *argv[]) {
    testWaterSupple();
    return 0;
}
