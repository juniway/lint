// [LeetCode 64] Minimum Path Sum
/*
Question:
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
Note: You can only move either down or right at any point in time.


Analysis:
This is a very easy DP problem.

But this is not a boring question because I found a few interesting solutions.
*/

int min_path(vector<vector<int>> &grid){
	int m = grid.size(), n = grid[0].size();
	vector<vector<int>> dp(m, vector<int>(n));

	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			if(i == 0){
				if(j == 0)
					dp[i][j] = 0;
				else dp[i][j] = dp[i][j-1] + grid[i][j];
			}
			else{
				if(j == 0)
					dp[i][j] = dp[i - 1][j] + grid[i][j];
				else
					dp[i][j] = min(dp[i - 1][j], grid[i][j - 1]) + grid[i][j];
			}
		}
	}
	return dp[m - 1][n - 1];
}

// space reduced
int min_path(vector<vector<int>> &grid){
	int m = grid.size(), n = grid[0].size();
	vector<int> dp(n);

	for(int i = 0; i < m; ++i){
		for(int j = 0; j < n; ++j){
			if(i == 0){
				if(j == 0)
					dp[j] = 0;
				else dp[j] = dp[j-1] + grid[i][j];
			}
			else if(j == 0)
				dp[j] = dp[j] + grid[i][j];
			else
				dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
			}
		}
	}
	return dp[n - 1];
}
