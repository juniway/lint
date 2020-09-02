#include <iostream>
#include <vector>
using namespace std;

int mcp(vector<vector<int>>& cost, int i, int j) {
    if (i == cost.size() && j == cost[0].size()) return 0;
    else if(i == cost.size() || j == cost[0].size()) return INT_MAX;
    return cost[i][j] + min(mcp(cost, i+1, j+1), min(mcp(cost, i, j+1), mcp(cost, i+1, j)));
}

int mcp(vector<vector<int>>& cost) {
    int n = cost.size();
    if (n == 0) return 0;
    int m = cost[0].size();
    if(m == 0) return 0;

    return mcp(cost, 0, 0);
}

int minCostPath(vector<vector<int>>& cost) {
    int n = cost.size();
    if(n == 0) return 0;
    int m = cost[0].size();

    vector<vector<int>> d(n, vector<int>(m, 0x3f3f3f3f));
    d[0][0] = cost[0][0];

    // first row
    for (int j = 1; j < m; j++) {
        d[0][j] = d[0][j-1] + cost[0][j];
    }

    // first column
    for (int i = 1; i < n; i++) {
        d[i][0] = d[i-1][0] + cost[i][0];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            d[i][j] = min(d[i-1][j-1], min(d[i-1][j], d[i][j-1])) + cost[i][j];
        }
    }

    return d[n-1][m-1];
}

void testMCP() {
    vector<vector<int>> cost = {
        {1, 2, 3},
        {4, 8, 2},
        {1, 5, 3}
    };

    cout << minCostPath(cost) << endl;
    // cout << mcp(cost) << endl;
}

int main(int argc, char *argv[]) {
    testMCP();
    return 0;
}
