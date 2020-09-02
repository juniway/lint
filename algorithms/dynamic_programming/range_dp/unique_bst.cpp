#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> dp;

int rec(int begin, int end) {
    if (dp[begin][end] != -1) return dp[begin][end];

    int cnt = 0;
    for(int k = begin; k < end; k++) {
        cnt += rec(begin, k) * rec(k + 1, end);
    }

    return dp[begin][end] = cnt;
}

int uniqueBsts(int n) {
    dp = vector<vector<int>> (n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    return rec(0, n - 1);
}

int main(int argc, char *argv[]) {
    cout << uniqueBsts(3) << endl;
    return 0;
}
