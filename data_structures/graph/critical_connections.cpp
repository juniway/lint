#include <iostream>
#include <vector>
#include <map>

using namespace std;

int dfs(vector<vector<int>>& adj, int pre, int cur, int depth, vector<int>& depths, vector<vector<int>>& res) {
    depths[cur] = depth;
    int min_depth = depth;
    for (auto &neighbor : adj[cur]) {
        if (neighbor == pre) continue;
        int tmp_depth = depths[neighbor];
        if (tmp_depth == -1)
            tmp_depth = dfs(adj, cur, neighbor, depth + 1, depths, res);
        if (tmp_depth > depth)
            res.push_back({cur, neighbor});
        else
            min_depth = min(min_depth, tmp_depth);
    }
    depths[cur] = min_depth;

    return min_depth;
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> adj;
    for (auto &e : connections) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    vector<vector<int>> res;
    vector<int> depths(n, -1);

    dfs(adj, -1, 0, 0, depths, res);
    return res;
}
