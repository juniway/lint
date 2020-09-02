// Problem:
// Find minimum insertions to form a palindrome
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 1. recursive approach
int findMinInsertionRec(string s, int left, int right) {
    if (left > right) return INT_MAX;
    if (left == right) return 0;
    if (left == right - 1) return s[left] == s[right] ? 0 :1;
    if (s[left] == s[right])
        return findMinInsertionRec(s, left + 1, right - 1);
    else
        return 1 + min(findMinInsertionRec(s, left, right - 1), findMinInsertionRec(s, left + 1, right));
}


// 2.memo, top down
// dp[left][right] represents the insertions need of substr(left to right) to become palindrom
int findMinInsertionMemo(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int> (n, 0));

    for (int len = 1; len < n; len++) { // len of substring
        for (int left = 0, right = len; right < n; left++, right++) {
            if (s[left] == s[right])
                dp[left][right] = dp[left + 1][right - 1];
            else
                dp[left][right] = 1 + min(dp[left][right - 1], dp[left + 1][right]);
        }
    }

    return dp[0][n - 1];
}

// 3. dp, bottom up
int findMinInsertionDp(string s) {
    int n = s.size();
    if (n == 0) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[j]) {
                if (j - i > 1)
                    dp[i][j] = dp[i + 1][j - 1];
            } else {
                dp[i][j] = 1;
                if (j - i > 1)
                    dp[i][j] = 1 + min(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1];
}

// 4. lcs
int lcs(string s1, string s2) {
    int n1 = s1.size(), n2 = s2.size();
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i -1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[n1][n2];
}

int findMinInsertionLcs(string s) {
    string s1 = s;
    reverse(begin(s1), end(s1));
    return s.size() - lcs(s, s1);
}

void testFindMinInsertions() {
    cout << findMinInsertionRec("abb", 0, 2) << endl;
    cout << findMinInsertionMemo("abb") << endl;
    cout << findMinInsertionDp("abcad") << endl;
    cout << findMinInsertionLcs("abcad") << endl;
}

int main(int argc, char *argv[]) {
    testFindMinInsertions();
    return 0;
}
