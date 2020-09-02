#include <iostream>
#include <string>
#include <vector>
using namespace std;

// https://www.gohired.in/2019/10/10/leetcode-edit-distance/
int editDistanceRec(string a, string b, int i, int j) {
    if (i == a.size()) return b.size() - j;
    if (j == b.size()) return a.size() - i;

    int res;
    if (a[i] == b[j]) 
        res = editDistanceRec(a, b, i+1, j+1);
    else {
        int insert = editDistanceRec(a, b, i, j + 1);
        int del = editDistanceRec(a, b, i + 1, j);
        int replace = editDistanceRec(a, b, i + 1, j + 1);
        res = min(min(insert, del), replace) + 1;
    }

    return res;
}

vector<vector<int>> memo;
int editDistanceMemo(string a, string b, int i, int j) {
    if (i == a.size()) return b.size() - j;
    if (j == b.size()) return a.size() - i;
    if (memo[i][j] != -1) return memo[i][j];

    if (a[i] == b[j]) {
        memo[i][j] = editDistanceMemo(a, b, i + 1, j + 1);
    } else {
        int insert = editDistanceMemo(a, b, i, j + 1);
        int del = editDistanceMemo(a, b, i + 1, j);
        int replace = editDistanceMemo(a, b, i + 1, j + 1);
        memo[i][j] = min(insert, min(del, replace)) + 1;
    }
    return memo[i][j];
}

// consider prefix m and n chars
int editDistanceDp(string a, string b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0));
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int i = 0; i <= n; i++) dp[0][i] = i;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else {
                dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
            }
        }
    }
    return dp[m][n];
}

int editDistance(string a, string b) {
    int m = a.size(), n = b.size();
    memo = vector<vector<int>> (m + 1, vector<int> (n + 1, -1));

    // return editDistanceRec(a, b, 0, 0);
    return editDistanceMemo(a, b, 0, 0);
}

void testEditDistance() {
    cout << editDistance("horse", "ros") << endl;
    cout << editDistanceDp("horse", "ros") << endl;
    cout << minDistance("horse", "ros") << endl;
}

int main(int argc, char *argv[]) {
    testEditDistance();
    return 0;
}
