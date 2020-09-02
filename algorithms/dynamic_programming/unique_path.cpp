/* Leetcode 62: Unique Paths
 *
 * */
#include <iostream>
#include <vector>

using namespace std;

int uniquePathsRec(int m, int n, int i, int j) {
    if (i == m - 1 || j == n - 1) return 1;
    return uniquePathsRec(m, n, i+1, j) + uniquePathsRec(m, n, i, j+1);
}

// dp
int uniquePaths(int m, int n) {
    vector<vector<int>> path(m, vector<int> (n, 0));
    int i, j;
    for (i = 1; i < m; ++i) {
        for (j = 1; j < n; ++j) {
            path[i][j] = path[i - 1][j] + path[i][j - 1];
        }
    }

    return path[m-1][n-1];
}

void testUnique() {
    cout << uniquePathsRec(3, 2, 0, 0) << endl;
    cout << uniquePaths(3, 2) << endl;
}

int main(int argc, char *argv[]) {
    testUnique();
    return 0;
}
