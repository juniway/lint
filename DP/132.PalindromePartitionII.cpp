[LeetCode 132] Palindrome Partition II

Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.
For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.


分析：
整体的思路是一维DP。DP[i]表示长度为i的prefix：s[0: i-1]的min cut数量。
DP[i] = min (DP[j] + 1) ，对所有 0<=j<i，且s[j: i-1]为palindrome。
和I同样的技巧，用DP先计算存储一个palindrome判断矩阵isPal[i][j]，便于后面一维DP计算中能迅速判断s[j: i-1]是否为palindrome。

// 136ms
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        if(n <= 1) return 0;
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        for(int i = n - 1; i >= 0; i--) {
            for(int j = i; j < n; j++) {
                if((i + 1 > j - 1 || isPal[i + 1][j - 1]) && s[i] == s[j])
                    isPal[i][j] = true;
            }
        }

        vector<int> dp(n+1, INT_MAX);
        dp[0] = -1;
        for(int i = 1; i <= n; i++) {
            for(int j = i - 1; j >= 0; j--) {
                if(isPal[j][i - 1]) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[n];
    }
};

// 有一个更优的解法参考：
// https://oj.leetcode.com/discuss/9476/solution-does-not-need-table-palindrome-right-uses-only-space