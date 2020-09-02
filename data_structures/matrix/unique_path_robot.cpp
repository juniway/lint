#include <iostream>
#include <vector>
using namespace std;

// class Solution {
// public:
//     vector<vector<int>> dir {{1, 0}, {0, 1}};
//     vector<vector<int>> res;
//     vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
//         int m = obstacleGrid.size(), n = obstacleGrid[0].size();
//         dfs(obstacleGrid, 0, 0, m, n);
//         return res;
//     }
//     void dfs(vector<vector<int>>& grid, int i, int j, int m, int n) {
//         if (i == m - 1 && j == n - 1) {
//             res.push_back({i, j});
//             return;
//         }
//         res.push_back({i, j});
//         for (auto d : dir) {
//             int y = i + d[0];
//             int x = j + d[1];
//             if (x >= 0 && x < m && y >= 0 && y < n && grid[y][x] == 0) {
//                 grid[y][x] = 1;
//                 dfs(grid, y, x, m, n);
//             }
//         }
//     }
// };

// class Solution1 {
// public:
//     vector<vector<int>> dir {{1, 0}, {0, 1}};
//     vector<vector<int>> res;
//     vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
//         int m = obstacleGrid.size(), n = obstacleGrid[0].size();
//         dfs(obstacleGrid, 0, 0, m, n);
//         return res;
//     }
//     bool dfs(vector<vector<int>>& grid, int i, int j, int m, int n) {
//         if (grid[i][j] == 0) {
//             if (i == m - 1 && j == n - 1) {
//                 res.push_back({i, j});
//                 return true;
//             }
//
//             res.push_back({i, j});
//             grid[i][j] = 1;
//             for (auto d : dir) {
//                 int y = i + d[0];
//                 int x = j + d[1];
//                 if (y < m && x < n) {
//                     if (dfs(grid, y, x, m, n)) return true;
//                 }
//             }
//         }
//
//         return false;
//     }
// };

class Solution {
public:
    vector<vector<int>> getPath(vector<vector<int>>& obstacleGrid, vector<vector<int>>& visited,  int i, int j, int&row, int& col ){

        if(i<0||i>=row||j<0||j>=col || obstacleGrid[i][j]>0 || visited[i][j]>0){
            return {};
        }
        if(obstacleGrid[i][j]==0 && (i==row-1) && (j==col-1)){
            return {{i, j}};
        }

        //向右找路径，有就返回不再向下找。
        vector<vector<int>> right = getPath(obstacleGrid, visited, i, j+1, row, col);
        if(right.size() > 0){
            right.push_back({i, j});
            return right;
        }

        //如果向右找路径找不到，则向下找。
        vector<vector<int>> down = getPath(obstacleGrid, visited,i+1, j, row, col);
        if(down.size()>0){
            down.push_back({i, j});
            return down;
        }

        //向右、向下都找不到，返回空。标记当前格子是那些“已被试过无法到达目标”的位置。
        visited[i][j]=1;
        return {};
    }
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
        int row = obstacleGrid.size(), col = obstacleGrid[0].size();
        vector<vector<int>> visited(row, vector<int>(col, 0));
        vector<vector<int>> res = getPath(obstacleGrid, visited, 0, 0, row, col);

        sort(res.begin(), res.end()); // 对结果排序。
        return res;
    }
};

void testPathWithObstacles() {
    // vector<vector<int>> grid = {
    //     {0,0,0},
    //     {0,1,0},
    //     {0,0,0}
    // };
    vector<vector<int>> grid = {
        {0,0},
    };

    Solution sol;
    sol.pathWithObstacles(grid);
}

int main(int argc, char *argv[]) {
    testPathWithObstacles();
    return 0;
}
