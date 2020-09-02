#include <iostream>
#include <vector>

using std::vector;
using std::cout;

struct Point {
    int x, y;
    Point(int x, int y):x(x), y(y) {}
};

void dfsRec(vector<vector<int>> grid, Point&& p, vector<vector<bool>>& visited) {
    int h = grid.size();
    if (h == 0) return;
    int l = grid[0].size();
    if (p.x < 0 || p.y < 0 || p.x >= h || p.y >= l || visited[p.x][p.y])
        return;

    visited[p.x][p.y] = true;
    cout << grid[p.x][p.y] << " ";

    dfsRec(grid, Point(p.x + 1, p.y), visited); // down
    dfsRec(grid, Point(p.x - 1, p.y), visited); // up
    dfsRec(grid, Point(p.x, p.y + 1), visited); // right
    dfsRec(grid, Point(p.x, p.y - 1), visited); // left
}

void dfs(vector<vector<int>> grid) {
    int h = grid.size();
    if (h == 0) return;
    int l = grid[0].size();
    vector<vector<bool>> visited(h, vector<bool>(l));

    cout << "dfs traversal: ";
    dfsRec(grid, Point(0, 0), visited);
    cout << "\n";
}

void testDfs() {
    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
    };

    dfs(grid);
}

int main(int argc, char *argv[]) {
    testDfs();
    return 0;
}
