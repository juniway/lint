/*
 * Leetcode 63: Unique Path II
 */

#include <iostream>
#include <vector>
using namespace std;

int uniquePathsWithObstacles1(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 1));

    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            if(obstacleGrid[i][j] == 1) dp[i][j] = 0;
            else if (i == 0) dp[i][j] = (j-1) >= 0 ? dp[i][j-1]:1;
            else if (j == 0) dp[i][j] = (i-1) >= 1 ? dp[i-1][j]:1;
            else dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    return dp[n-1][m-1];
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    dp[1][0] = 1;

    int i, j;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            if(obstacleGrid[i - 1][j - 1] == 0)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    for(auto x:dp) {
        for(auto a:x) cout << a << " ";
        cout << endl;
    }

    return dp[n][m];
}

void testObstacles() {
    vector<vector<int>> grids = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    vector<vector<int>> grids1 = {
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 0}
    };

    // cout << uniquePathsWithObstacles(grids) << endl;
    cout << uniquePathsWithObstacles(grids1) << endl;
}

int main(int argc, char *argv[]) {
    testObstacles();
    return 0;
}
