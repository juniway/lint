def uniquePaths(m, n):
    if not m or not n:
        return 0
    dp = [[1 for i in range(m)] for i in range(n)]
    for i in range(1, n):
        for j in range(1, n):
            dp[i][j] = dp[i-1][j] + dp[i][j-1]
    return dp[-1][-1]
