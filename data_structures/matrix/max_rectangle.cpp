#include <iostream>
#include <vector>

using namespace std;

int maxRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    int maxArea = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) dp[i][j] = (matrix[i][j] == '1') ? 1 : 0;
            else
                dp[i][j] = (matrix[i][j] == '1') ? dp[i - 1][j] + 1 : 0;

            int min = dp[i][j];
            for (int k = j; k >= 0; k--) {
                if (min == 0) break;
                if (min > dp[i][k]) min = dp[i][k];
                maxArea = max(maxArea, min * (j - k + 1));
            }
        }
    }

    return maxArea;
}
