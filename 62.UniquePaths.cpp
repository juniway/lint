[LeetCode 62] Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time.
The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
How many possible unique paths are there?

Above is a 3 x 7 grid. How many possible unique paths are there?
Note: m and n will be at most 100.

Analysis:
DP, transction function is DP[i][j] = DP[i-1][j] + DP[i][j-1];

this could be implemented in one dimension DP

滚动数组:
如果按行遍历，则用maxpath[n] 来表示到第j列某个位置时，这个位置一共有多少种走法

class Solution {
public:
	int uniquePaths(int m, int n) {
	    vector <int> maxpath(n, 0);
	    maxpath[0] = 1;
	    for(int i = 0; i< m; i++){
	        for(int j = 1; j < n; j++){
	            maxpath[j] = maxpath[j - 1] + maxpath[j];
	        }
	    }
	    return maxpath[n - 1];
	}
};