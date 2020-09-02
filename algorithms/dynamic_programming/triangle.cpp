#include <iostream>
#include <vector>

using namespace std;

int minPathTriangle(vector<vector<int>> triangle, int row, int col) {
    int m = triangle.size();
    int n = triangle[0].size();
    if (row >= m || col < 0 || col >= n) return 0;
    int maxPath = triangle[row][col] + min(minPathTriangle(triangle, row + 1, col-1), minPathTriangle(triangle, row+1, col + 1));
    return maxPath;
}

int minPathTriangle(vector<vector<int>>& triangle, int i, int j, int n, int m) {
    if (i == n || j < 0 || j == m) return 0;
    return triangle[i][j] + min(minPathTriangle(triangle, i + 1, j, n, m), minPathTriangle(triangle, i + 1, j + 1, n, m));
}

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size(), m = triangle[0].size();
    return minPathTriangle(triangle, 0, 0, n, m);
}

// dp
// m[i][j] represent min at i, j
int minPathTri(vector<vector<int>> &triangle) {
    int n = triangle.size();
    int m = triangle[n-1].size();
    vector<vector<int>> sum(n, vector<int>(m+1, INT_MAX));
    for (int j = 0; j < m; j++) {
        sum[n-1][j] = triangle[n-1][j];
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j < triangle[i].size(); j++) {
            sum[i][j] = triangle[i][j] + min(sum[i + 1][j], sum[i+1][j+1]);
        }
    }

    return sum[0][0];
}

void testMinPathTriangle() {
    vector<vector<int>> tri{
        {0, 0, 0, 2, 0, 0, 0},
        {0, 0, 3, 0, 4, 0, 0},
        {0, 6, 0, 5, 0, 7, 0},
        {4, 0, 1, 0, 8, 0, 3},
    };

    // cout << minPathTriangle(tri, 0, 3) << endl;

    vector<vector<int>> tri1{
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3},
    };
    // cout << minimumTotal(tri1) << endl;
    cout << minPathTri(tri1) << endl;
}

int main(int argc, char *argv[]) {
    testMinPathTriangle();
    return 0;
}
