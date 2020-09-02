#include <iostream>
#include <vector>

using namespace std;

vector<int> printMatrixDiagonal(vector<vector<int>>& mat, int n) {
    vector<int> res (n*n, 0);
    int i = 0, j = 0;
    bool goUp = true;
    for (int k = 0; k < n*n;) {
        if (goUp) {
            for (; i >= 0 && j < n; i--, j++) {
                res[k++] = mat[i][j];
            }
            if (i < 0 && j <= n - 1) {
                i = 0;
            }
            if (j == n) {
                i += 2;
                j--;
            }
        }
        else {
            for (; j >= 0 && i < n; i++, j--) {
                res[k++] = mat[i][j];
            }
            if (j < 0 && i <= n - 1)
                j = 0;
            if (i == n) {
                j += 2;
                i--;
            }
        }
        goUp = !goUp;
    }

    for (auto x : res) cout << x << " ";
    cout << endl;

    return res;
}

int main() {
    // int mat[MAX][MAX] = { { 1, 2, 3 },
    //                       { 4, 5, 6 },
    //                       { 7, 8, 9 } };

    vector<vector<int>> mat = { { 1, 2, 3, 4},
                          { 5, 6, 7, 8 },
                          { 9, 10, 11, 12 },
                          { 13, 14, 15, 16 } };
    int n = 4;
    printMatrixDiagonal(mat, n);
    return 0;
}
