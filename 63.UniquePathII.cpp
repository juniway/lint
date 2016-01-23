[LeetCode 63] Unique Path II
Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?
An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0, 0, 0],
  [0, 1, 0],
  [0, 0, 0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.

Analysis:
there is a little difference with the Unique Paths

DP functions
dp[i]][j] = dp[i-1][j] + dp[i][j-1]    if obstacle[i][j] == 0
          = 0                          if obstacle[i][j] == 1

class Solution{
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        int m = obstacleGrid.size();
        if(m == 0) return 0;
        int n = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1) return 0;

        vector<int> maxpath(n, 0);
        maxpath[0] = 1;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n;j++){
                if(obstacleGrid[i][j] == 1)
                    maxpath[j] = 0;
                else if(j > 0)
                    maxpath[j] = maxpath[j] + maxpath[j - 1];
            }
        }
        return maxpath[n-1];
    }
};


