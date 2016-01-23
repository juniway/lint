[LeetCode 64] Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom
right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
类似问题:
MCP: Minimum Cost Path
Given a cost matrix cost[][] and a position (m, n) in cost[][], write a function that returns
cost of minimum cost path to reach (m, n) from (0, 0). Each cell of the matrix represents a cost
to traverse through that cell. Total cost of a path to reach (m, n) is sum of all the costs
on that path (including both source and destination). You can only traverse down, right and diagonally
lower cells from a given cell, i.e., from a given cell (i, j), cells (i+1, j), (i, j+1) and (i+1, j+1)
can be traversed. You may assume that all costs are positive integers.

问题扩展：
(1) Maximum Path Sum, 只要把Min换成Max就行，思路和解法步骤一样
(2) 双线Min Path Sum，如果两个人同时从左上角出发，目的地是右下角，两个人的路线不能相交
	(即除了出发点和终点外，两个人不同通过同一个格子)，使得两条路径的和最大。
	（这和一个人先从左上角到右下角，再回到左上角是相同的问题）。

(3)

思路：
典型的动态规划问题。
设dp[i][j]表示从左上角到grid[i][j]的最小路径和。
那么dp[i][j] = grid[i][j] + min( dp[i-1][j], dp[i][j-1]);

下面的代码中，为了处理计算第一行和第一列的边界条件(即dp[i - 1][j] 这种情况, 因为不存在负索引)，
我们令dp[i][j]表示从左上角到grid[i-1][j-1]的最小路径和，最后dp[m][n]是我们所求的结果
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        int row = grid.size(), col;
        if(row == 0) return 0;
        else col = grid[0].size();
        vector<vector<int> >dp(row + 1, vector<int>(col + 1, INT_MAX));
        dp[0][1] = 0;
        for(int i = 1; i <= row; i++)
            for(int j = 1; j <= col; j++)
                dp[i][j] = grid[i - 1][j - 1] + min(dp[i][j - 1], dp[i - 1][j]);
        return dp[row][col];
    }
};

注意到上面的代码中dp[i][j] 只和上一行的dp[i-1][j]和上一列的dp[i][j-1]有关，
因此可以优化空间为O(N),(准确来讲空间复杂度可以是O(min(row,col)))
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        int row = grid.size(),col;
        if(row == 0)return 0;
        else col = grid[0].size();
        vector<int >dp(col + 1, INT_MAX);
        dp[1] = 0;
        for(int i = 1; i <= row; i++)
            for(int j = 1; j <= col; j++)
                dp[j] = grid[i - 1][j - 1] + min(dp[j], dp[j - 1]);
        return dp[col];
    }
};

// Analysis:
// dp[i][j] denotes the minimum path that reach (i, j)
// dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + a[i][j];
// Initial value:
// dp[0][0] = a[0][0];
// dp[0][j > 0] = dp[0][j - 1] + dp[0][j];
// dp[i > 0][0] = dp[i - 1][0] + dp[i][0];
// complexity: O(m * n)

// Solutions:
// 1. 2D array
class Solution{
public:
	int miniPathSum(vector<vector<int> &grid){
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>> dp(m, vector<int>(n));

		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				if(i == 0){
					if(j == 0) dp[i][j] = grid[i][j];
					else dp[i][j] = dp[i][j - 1] + grid[i][j];
				}
				else if(j == 0) dp[i][j] = dp[i - 1][j] + grid[i][j];
				else dp[i][j] = min(dp[i -1][j], dp[i][j-1]) + grid[i][j];
			}
		}

		return dp[m - 1][n -1];
	}
};

// 1D array
class Solution{
public:
	int miniPathSum(vector<vector<int> &grid){
		int m = grid.size();
		int n = grid[0].size();
		vector<int> dp(m);

		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				if(i == 0){
					if(j == 0) dp[j] = grid[i][j];
					else dp[j] = dp[j - 1] + grid[i][j];
				}
				else if(j == 0) dp[j] = dp[j] + grid[i][j];
				else dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
			}
		}
		return dp[n -1];
	}
};

// in-place
class Solution{
public:
	int miniPathSum(vector<vector<int> &grid){
		int m = grid.size();
		int n = grid[0].size();
		for(int i = 0; i < m; ++i){
			for(int j = 0; j < n; ++j){
				if(i == 0){
					if(j == 0) grid[i][j] = grid[i][j];
					else grid[i][j]= grid[i][j - 1] + grid[i][j];
				}
				else if(j == 0) grid[i][j] = grid[i][i-1][j] + grid[i][j];
				else grid[i][j] = min(grid[i-1][j], grid[i][j-1]) + grid[i][j];
			}
		}
		return grid[m - 1][n -1];
	}
};

拓展:
(1)传纸条(双线DP)
解题思路：将题目转化成同时从（1,1）到（m，n）的两条线路，要求这两条线路无交点。
最开始想用四维来表示状态线路1和线路2的位置状态，但是看别人说这样容易超时，
于是定义成三维情况。用k来表示总共走了多少步，x1表示线路1走到的x坐标位置，x2表示线路2的，
则间接表示了两条线路的y坐标，即k-x1或k-x2。状态表示出来后，状态转移就能表示出来了。

(2)收集苹果
给定一个M行N列的矩阵(M*N个格子)，每个格子中放着一定数量的苹果。
你从左上角的格子开始，只能向下或向右走，目的地是右下角的格子。
你每走过一个格子，就把格子上的苹果都收集起来。
然后你从右下角走回左上角的格子， 每次只能向左或是向上走，同样的，走过一个格子就把里面的苹果都收集起来。
最后，你再一次从左上角走到右下角，每过一个格子同样要收集起里面的苹果 (如果格子里的苹果数为0，就不用收集)。
求你最多能收集到多少苹果。
注意：当你经过一个格子时，你要一次性把格子里的苹果都拿走。
如果我们只需要从左上角的格子走到右下角的格子一次，并且收集最大数量的苹果，
那么问题就退化为“中级”一节里的那个问题。将这里的问题规约为“中级”里的简单题，
这样一来会比较好解。让我们来分析一下这个问题，要如何规约或是修改才能用上DP。
首先，对于第二次从右下角走到左上角得出的这条路径， 我们可以将它视为从左上角走到右下角得出的路径，
没有任何的差别。 (即从B走到A的最优路径和从A走到B的最优路径是一样的)通过这种方式，
我们得到了三条从顶走到底的路径。对于这一点的理解可以稍微减小问题的难度。
于是，我们可以将这3条路径记为左，中，右路径。对于两条相交路径(如下图)：
在不影响结果的情况下，我们可以将它们视为两条不相交的路径：

这样一来，我们将得到左，中，右3条路径。此外，如果我们要得到最优解，路径之间不能相交(除了左上角和右下角必然会相交的格子)。
因此对于每一行y( 除了第一行和最后一行)，三条路径对应的x坐标要满足：x1[y] < x2[y] < x3[y]。
经过这一步的分析，问题的DP解法就进一步地清晰了。
让我们考虑行y， 对于每一个x1[y-1]，x2[y-1]和x3[y-1]，我们已经找到了能收集到最多苹果数量的路径。
根据它们，我们能求出行y的最优解。现在我们要做的就是找到从一行移动到下一行的方式。
令Max[i][j][k]表示到第y-1行为止收集到苹果的最大数量， 其中3条路径分别止于第i,j,k列。
对于下一行y，对每个Max[i][j][k] 都加上格子(y,i)，(y,j)和(y,k)内的苹果数量。因此，每一步我们都向下移动。
我们做了这一步移动之后，还要考虑到，一条路径是有可能向右移动的。
(对于每一个格子，我们有可能是从它上面向下移动到它， 也可能是从它左边向右移动到它)。
为了保证3条路径互不相交， 我们首先要考虑左边的路径向右移动的情况，然后是中间，最后是右边的路径。
为了更好的理解，让我们来考虑左边的路径向右移动的情况，对于每一个可能的j,k对(j<k)， 对每个i(i<j)，
考虑从位置(i-1,j,k)移动到位置(i,j,k)。处理完左边的路径， 再处理中间的路径，最后处理右边的路径。方法都差不多。

问题扩展思路：
这是双线程动态规划问题：
假设网格为grid，dp[k][i][j]表示两个人都走了k步，第一个人向右走了i步(在第i-1列)，(我们假设在起始位置时就已经走了一步)
第二个人向右走了j步时的最大路径和（只需要三个变量就可以定位出两个人的位置 grid[k-i][i-1] 、 grid[k-j][j-1]），
那么:
dp[k][i][j] = max(dp[k-1][i-1][j-1], dp[k-1][i][j], dp[k-1][i-1][j], dp[k-1][i][j-1]) + grid[k-i][i-1] + grid[k-j][j-1]
                         |                  |              |                |
                         v                  v              v                v
                      都向右走          都向下走    i向右走，j向下走  i向下走，向右走

这个方程的意思是从第k-1步到第k步，可以两个人(1)都向右走，(2)都向下走，(3)第一个向右第二个向下，(4)第一个向下第二个向右。
这四种走法中选择上一步中路径和最大的。

由于要保证两条路线不能相交，即两个人走的过程中，有一个人向右走的步数永远大于另一个人向右走的步数，
我们不妨设第二个人向右走的步数较大，即dp[k][i][j]中j > i才是有效的状态。走到终点的步数为：网格的行数+网格的列数-1

需要注意的是：当走了k步时，某个人向右走的步数必须 > k - 网格的行数，
如果向右走的步数 <= k-行数，那么向下走的步数 = k-向右走的步数 >= 行数，此时超出了网格的范围。
由于我们假设了 j > i,因此只要保证 i > k-网格行数即可。

int max2PathSum(vector<vector<int> > grid){
    int row = grid.size(), col = grid[0].size();
    vector<vector<vector<int>>> dp(row + col, vector<vector<int> >(col+1, vector<int>(col+1, 0)));
    for(int step = 2; step <= row + col - 2; ++step)
        for(int i = max(1, step - row + 1); i <= step && i <= col; ++i)
            for(int j = i + 1; j <= step && j <= col; ++j){
                dp[step][i][j] = max(max(dp[step-1][i][j], dp[step-1][i-1][j-1]), max(dp[step-1][i-1][j], dp[step-1][i][j-1]));
                dp[step][i][j] += (grid[step-i][i-1] + grid[step-j][j-1]);
            }
    return dp[row + col-2][col-1][col] + 2*grid[row-1][col-1] + 2*grid[0][0];
}

我们最终的目标是:
dp[row+col-1][col][col] = max{ dp[row+col-2][col-1][col-1], dp[row+col-2][col][col],
				dp[row+col-2][col-1][col], dp[row+col-2][col][col-1]} + 2*grid[row-1][col-1]

由于dp[row+col-2][col-1][col-1], dp[row+col-2][col][col], dp[row+col-2][col][col-1]都是无效的状态（dp[k][i][j]中j > i才是有效的状态），
所以dp[row+col-1][col][col]  = dp[row+col-2][col-1][col] + 2*grid[row-1][col-1]，代码中最后结果还加上了所在起点的的网格值。

由以上可知，循环中最多只需要求到了dp[row + col - 2][][]。

nyoj中 传纸条（一）就是这个问题，可以在这一题中测试上述函数的正确性，
测试代码如下：
int main(){
    int n;
    scanf("%d",&n);
    for(int i = 1; i <= n; i++){
        int row, col;
        scanf("%d%d", &row, &col);
        vector<vector<int> >grid(row, vector<int>(col));
        for(int a = 0; a < row; a++)
            for(int b = 0; b < col; b++)
                scanf("%d", &grid[a][b]);
        printf("%d\n", max2PathSum(grid));
    }
    return 0;
}
这个问题还可以使用最小费用流来解决，具体可以参考http://acm.nyist.net/JudgeOnline/articles/?p=48#more-48