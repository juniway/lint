#include <iostream>
#include <vector>
using namespace std;

int minPathSum(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();

    vector<vector<int>> ps(n, vector<int> (m, INT_MAX));
    ps[0][0] = grid[0][0];

    // first row
    int i,j;
    for (j = 1; j < m; ++j) {
        ps[0][j] = ps[0][j-1] + grid[0][j];
    }
    for (i = 1; i < n; ++i) {
        ps[i][0] = ps[i - 1][0] + grid[i][0];
    }

    for (i = 1; i < n; ++i) {
        for (j = 1; j < m; ++j) {
            ps[i][j] = grid[i][j] + min(ps[i-1][j], ps[i][j-1]);
        }
    }

    for (auto x:ps) {
        for(auto a:x) cout << a << "  ";
        cout << endl;
    }
    return ps[n-1][m-1];
}

void testMinPathSum() {
    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1},
    };
    cout << minPathSum(grid) << endl;
}

int main(int argc, char *argv[]) {
    testMinPathSum();
    return 0;
}
