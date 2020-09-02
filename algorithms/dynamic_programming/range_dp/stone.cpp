#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int minCostMergeStone(vector<int>& piles) {
    int n = piles.size();
    vector<int> sum(piles.size(), 0);
    sum[0] = piles[0];
    for (int i = 1; i < piles.size(); i++) {
        sum[i] = sum[i - 1] + piles[i];
    }

    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    for(int i = 0; i < n; i++) dp[i][i] = 0;

    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j] , dp[i][k] + dp[k + 1][j] + sum[j] - sum[i] + piles[i]);
            }
        }
    }

    return dp[0][n - 1];
}

void testMinCostMergeStones() {
    vector<int> piles = {1, 2, 3, 4};
    cout << minCostMergeStone(piles) << endl; // expected: 19
}

int main(int argc, char *argv[]) {
    testMinCostMergeStones();
    return 0;
}
