## Longest Common Substring

Given two strings, find the longest common substring.
Return the length of it.
The characters in substring should occur continuously in original string. This is different with subsequence.

Have you met this question in a real interview? Yes
Example
Given A = "ABCD", B = "CBCE", return 2.

Challenge 
O(n x m) time and memory.

#### 分析
这道题很简单，与 Longest Common Subsequence 不同的是，必须是连续的。
主要有两种思路，一种是，遍历字符串 A 和 B，直接判断 A 以 i 和 B 以 j 位置开始的最长公共字串。
另外一种是动态规划的思路，用一个二维表去保存最长公共后缀。


##### Solutions

1. 遍历

```cpp
class Solution {
public:    
    int longestCommonSubstring(string &A, string &B) {
        int maxLen = 0, maxIndex = 0;
        for (int i = 0; i < A.length(); ++i) {
            for (int j = 0; j < B.length(); ++j) {
                int len = comLen(A.substr(i), B.substr(j));
                if (maxLen < len) {
                    maxLen = len;
                    maxIndex = i;
                }
            }
        }
        return maxLen;
    }
    
    int comLen(string p, string q) {
        int len = 0;
        for (unsigned int i = 0; i < p.length() && i < q.length(); ++i) {
            if (p[i] == q[i]) ++len;
            else break;
        }
        return len;
    }
};
```

2. 动态规划
其实就是把解法 1 中，遍历的结果保存下来。

Create a table to store lengths of longest common suffixes of substrings.
Note that LCSuff[i][j] contains length of longest common suffix of X[0..i-1] and Y[0..j-1]. 
The first row and first column entries have no logical meaning, they are used only for simplicity of program.

```cpp
int lcstr(string X, string Y){
    int m = (int)X.length(), n = (int)Y.length();
    if (m == 0 || n == 0) return 0;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    int result = 0;
    for (int i = 1; i <= m; i++){   // Build LCSuff[m+1][n+1] in bottom up fashion.
        for (int j = 1; j <= n; j++){
            if (X[i-1] == Y[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
                result = max(result, dp[i][j]);
            }
            else LCSuff[i][j] = 0;
        }
    }
    return result;
}
```