http://bangbingsyb.blogspot.jp/2014/11/leetcode-longest-palindromic-substring.html
需要计算并记录任意s[i:j]是否是回文：
定义bool isPal[i][j]表示s[i:j]是否为回文，isPal[i][j] = true需要满足两个条件: 
1. s[i] ==s[j]
2. i+1>j-1 或 isPal[i+1][j-1] == true (即s[i+1 : j-1]是回文)

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.size()<=1) return s; 
        int start = 0, maxLen = 1, n = s.size();
        bool isPal[1000][1000] = {false};
        
        for(int i=n-1; i>=0; i--) {
            for(int j=i; j<n; j++) {
                if((i+1>j-1 || isPal[i+1][j-1]) && s[i]==s[j]) {
                    isPal[i][j] = true;
                    if(j-i+1>maxLen) {
                        maxLen = j-i+1;
                        start = i;
                    }
                }
            }
        }
        
        return s.substr(start,maxLen);
    }
};

// http://www.xuebuyuan.com/2158451.html
问题描述
回文序列(Palindromic sequence, Palindrome)是指正向遍历和反向遍历完全相同的序列，
例如字符串“AAAAA”显然是一个回文序列，又如字符串“ABC@CBA”也是一个回文序列。
现在，我们要在一个（字符）序列中找出最长回文子序列的长度。例如字符序列"BBABCBCAB"，
最长回文子序列是“BACBCAB”（可能不唯一），它的长度是7；
子序列"BBBBB"和"BBABB"虽然也是回文序列，但却不是最长的，因此不合题意。
分析与解
方法1：设Sp是序列S的最长回文子序列，又设ST是S的转置

#include <stdio.h>
#include <string.h>

#define MAXN 5010

int dp[2][MAXN];	//对应表格的最左边两列，自下而上，自左向右，滚动刷新
char inSeq[MAXN];
int FindLenLPS(int n){
	//Init
	for (int i=0; i<2; ++i){
		for (int j=0; j<n; ++j)
			dp[i][j]=0;
	}
	dp[0][0]=1;

	int refresh_col;	//这次该刷新dp的哪一列？
	int base_col;	//根据base_col刷新refresh_col
	for (int i=1; i<n; ++i){	//从第一列开始，共需更新n-1列(次);自左向右
		refresh_col=i%2;
		base_col=1-refresh_col;

		dp[refresh_col][i]=1;

		for (int j = i-1; j >= 0; --j){	//自下而上
			//应用状态转移方程
			if (inSeq[j] == inSeq[i]){
				dp[refresh_col][j]= 2 + dp[base_col][j+1];
			}
			else{
				dp[refresh_col][j] = max(dp[refresh_col][j+1], dp[base_col][j]);
			}
		}
	}

	return dp[(n-1)%2][0];	//这就是LPS的长度
}

int main()
{
	int n;
	scanf("%d", &n);
	scanf("%s", inSeq);

	printf("%d\n", n-FindLenLPS(n));

	return 0;
}


// poj 11151 - Longest Palindrome
题目大意：给出一个字符串，计算这个字符串的最长回文子串， 不同的是，它的子串可以不连续。
解题思路：刚开始把这道题当成普通的连续回文串来做了， 用了manachar算法， 一直WA， 
然后才发现原来子串可以不连续， 但是其实就是求当前这个字符串和其逆序的最长公共子序列。

#include <stdio.h>
#include <string.h>
const int N = 1005;
int max(int a, int b) { return a > b ? a : b; }

char a[N], b[N];
int dp[N][N], len;

int solve() {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
		    if (a[i - 1] == b[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
		    else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
    }
    return dp[len][len];
}

int main() {
    int cas;
    scanf("%d%*c", &cas);
    while (cas--) {
	gets(a);
	len = strlen(a);
	for (int i = 0; i < len; i++)
	    b[len - i - 1] = a[i];
	printf("%d\n", solve());
    }
}