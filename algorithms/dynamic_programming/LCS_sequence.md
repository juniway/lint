#### LCS 有两类题目：

- (1) 最长公共子序列，Longest Common Subsequence
- (2) 最长公共子串，Longest Common Substring

这两者的区别在于：**子序列不要求连续，而字串要求连续。**

#### 1、最长公共子序列

Given two strings, find the longest common subsequence (LCS).
Your code should return the length of LCS.

Example
For "ABCD" and "EDCA", the LCS is "A" (or "D", "C"), return 1.
For "ABCD" and "EACB", the LCS is "AC" (or "AC"), return 2.

Clarification
What's the definition of Longest Common Subsequence?

https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
http://baike.baidu.com/view/2020307.htm

#### 分析

求『最长』类的题目往往与动态规划有点关系，这里是两个字符串，故应为双序列动态规划。

使用动态规划求解这个问题，先寻找最优子结构。设 `X = <x1, x2, …, xm>` 和 `Y = <y1, y2, …, yn>` 为两个序列，LCS(X, Y) 表示序列 X 和 Y 的一个最长公共子序列，可以看出

    如果 xm = yn，则 LCS(X, Y) = xm + LCS(Xm-1, Yn-1)。
    如果 xm != yn，则 LCS( X,Y )= max{LCS(Xm-1, Y), LCS(X, Yn-1 )}

LCS 问题也具有重叠子问题性质：为找出 X 和 Y 的一个 LCS，可能需要找 X 和 Yn-1 的一个 LCS 以及 Xm-1 和 Y 的一个LCS。但这两个子问题都包含着找 Xm-1 和 Yn-1 的一个 LCS，等等.

DP最终处理的还是数值（极值做最优解），找到了最优值，就找到了最优方案；为了找到最长的LCS，我们定义 dp[i][j] 记录字符串 X的前 i 位和字符串 Y 的前 j 位的最长公共子序列长度，合法状态的初始值为当序列 X 的长度为 0 或 Y 的长度为 0 ，公共子序列 LCS 长度为 0，即 dp[i][j] = 0 ，状态转移方程为

    dp[i][j] = 0                                ，如果 i = 0 或 j = 0
    dp[i][j] = dp[i-1][j-1] + 1                 ，如果X[i-1] = Y[i-1]
    dp[i][j] = max{dp[i-1][j], dp[i][j-1]}    ，如果X[i-1] != Y[i-1]

求出了最长公共子序列的长度后，输出LCS就是输出dp的最优方案了，这在01背包中已经讲过，既可以用一个额外的矩阵存储路径，也可以直接根据状态转移矩阵倒推最优方案。

##### Solutions

动态规划

```cpp
#include <iostream>
using namespace std;

int lcs(vector<char> A, vector<char> B){
    int m = A.size(), n = B.size();
    if(m == 0 || n == 0)
        return 0;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 0; i <= m; ++i){
        for (int j = 0; j <= n; ++j) {
            if(i == 0 || j == 0)
                dp[i][j] = 0;
            else if (A[i - 1] == B[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // 以下代码是打印该LCS
    i = m, j = n;
    while(i && j) {
        if(A[i-1] == B[j-1] && dp[i][j] == dp[i-1][j-1] + 1) {
            // lcs[--k] = X[i-1];
            cout << A[i - 1];
            --i; --j;
        } else if(dp[i-1][j] > dp[i][j-1]) {
            --i;
        } else {
            --j;
        }
    }

    cout << endl;

    return dp[m][n];
}
```

优化，减少内存使用
// Reduced space complexity
// One disadvantage of the dynamic programming methods we've described,
// compared to the original recursion, is that they use a lot of space:
// O(mn) for the array L (the recursion only uses O(n+m)).
// But the iterative version can be easily modified to use less space --
// the observation is that once we've computed row i of array L, we no longer need the values in row i+1.

```cpp
int lcs(char * A, char * B) {
    for (i = m; i >= 0; i--) {
        for (j = n; j >= 0; j--) {
            if (A[i] == '\0' || B[j] == '\0') X[j] = 0;
            else if (A[i] == B[j]) X[j] = 1 + Y[j+1];
            else X[j] = max(Y[j], X[j+1]);
        }
        Y = X;
    }
    return X[0];
}
```

