#include <iostream>
#include <vector>

using namespace std;

const int MAX = 100;

// scan from rightmost column to left
int getMaxGold(int gold[][MAX], int m, int n) {
    vector<vector<int>> gt(m, vector<int>(n));
    for (int col = n -1; col >= 0; col--) {
        for (int row = 0; row < m; row++) {
            int right = (col == n - 1) ? 0 : gt[row][col+1];
            int right_up = (row == 0 || col == n - 1) ? 0:gt[row-1][col+1];
            int right_down = (row == m - 1 || col == n - 1)?0:gt[row+1][col+1];
            gt[row][col] = gold[row][col] + max(right, max(right_up, right_down));
        }
    }

    int res = gt[0][0];
    for (int i = 1; i < m; i++)
        res = max(res, gt[i][0]);
    return res;
}

void testGold() {
    int gold[MAX][MAX] = {
        {1, 3, 3},
        {2, 1, 4},
        {0, 6, 4}
    };

    cout << getMaxGold(gold, 3, 3) << endl;
}

int main(int argc, char *argv[]) {
    testGold();
    return 0;
}
