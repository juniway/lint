#include <iostream>
#include <vector>
using namespace std;

int minSquares(int m, int n) {
    vector<vector<int>> dp (m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
                continue;
            }
            if (i == j) {
                dp[i][j] = 1;
                continue;
            }

            if (m % n == 0) {
                dp[m][n] = m/n;
                continue;
            }
            if (n % m == 0) {
                dp[m][n] = n/m;
                continue;
            }

            int smaller = min(i, j);
            int minv = INT_MAX;
            for (int k = 1; k <= smaller; k++) {
                int minK = min(dp[i-k][j] + dp[k][j-k], dp[i][j-k] + dp[i-k][k]);
                minv = min(minv, minK);
            }
            dp[i][j] = 1 + minv;
        }
    }

    return dp[m][n];
}

void testFindMinSquares() {
    cout << minSquares(5, 6) << endl;
    cout << minSquares(11, 13) << endl;
}

int main(int argc, char *argv[]) {
    testFindMinSquares();
    return 0;
}

