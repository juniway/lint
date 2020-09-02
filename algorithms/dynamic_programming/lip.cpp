// Problem:
// Find longest increasing path

#include <iostream>
#include <vector>
using namespace std;

// dfs + dp
vector<vector<int>> directions = {
    {0, 1}, {0, -1}, // right/left
    {1, 0}, {-1, 0}, // down/up
};

int dfs(vector<vector<int>>& mat, int i, int j, vector<vector<int>>& dp) {
    if(dp[i][j] != 0) return dp[i][j];
    int maxPath = 1;
    for (auto dir : directions) {
        int x = i + dir[0], y = j + dir[1];
        if(x < 0 || x >= mat.size() || y < 0 || y > mat[0].size() || mat[x][y] <= mat[i][j]) continue;
        int len = 1 + dfs(mat, x, y, dp);
        maxPath = max(maxPath, len);
    }

    return dp[i][j] = maxPath;
}

int findLip(vector<vector<int>>& mat) {
    if (mat.size() == 0) return 0;
    int n = mat.size(), m = mat[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    int maxPath = 1;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int len = dfs(mat, i, j, dp);
            maxPath = max(maxPath, len);
        }
    }
    return maxPath;
}


// geeks: longest increasing path from (0, 0) to (m, n)
int dfsLip(vector<vector<int>>& mat, int i, int j, vector<vector<int>>& dp) {
    int n = mat.size(), m = mat[0].size();
    if (dp[i][j] < 0) {
        if (i == n - 1 && j == m - 1) return dp[i][j] = 1;
        int res = 0;
        if (i == n - 1 || j == m - 1) res = 1;
        if (mat[i][j] < mat[i + 1][j]) {
            res = 1 + dfsLip(mat, i + 1, j, dp);
        }
        if (mat[i][j] < mat[i][j + 1])
            res = max(res, 1 + dfsLip(mat, i, j + 1, dp));
        dp[i][j] = res;
    }
    return dp[i][j];
}

int findLip1(vector<vector<int>>& mat) {
    if (mat.size() == 0) return 0;
    int n = mat.size(), m = mat.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    int res =  dfsLip(mat, 0, 0, dp);
    for (auto x:dp) {
        for (auto a: x) cout << a << " ";
        cout << endl;
    }

    return res;
}

void testFindLip() {
    vector<vector<int>> mat = {
		{ 1, 2, 3, 4 },
        { 2, 2, 3, 4 },
        { 3, 2, 3, 4 },
        { 4, 5, 6, 7 },
    };
    cout << findLip1(mat) << endl;
}

int main(int argc, char *argv[]) {
    testFindLip();
    return 0;
}
