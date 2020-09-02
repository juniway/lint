#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<vector<int>>& M, int i, vector<bool>& visited) {
    visited[i] = true;
    for (int j = i + 1; j < M.size(); j++) {
        if (M[i][j] == 1 && !visited[j]) {
            visited[j] = true;
            dfs(M, j, visited);
        }
    }
}

int friendCircleNum(vector<vector<int>>& M) {
    int n = M.size(), count = 0;
    vector<bool> visited(n);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            dfs(M, i, visited);
        }
    }
    return count;
}

void testFriendCircleNum() {
    vector<vector<int>> M  = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    cout << friendCircleNum(M) << endl;
}

int main(int argc, char *argv[]) {
    testFriendCircleNum();
    return 0;
}
