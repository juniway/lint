#include <iostream>
#include <stack>
#include <vector>

using std::stack;
using std::vector;
using std::cout;

struct Point {
    int x, y;
    Point(int x, int y):x(x), y(y) {}
};

void dfs(vector<vector<int>> grid) {
    int h = grid.size();
    if (h == 0) return;
    int l = grid[0].size();
    vector<vector<int>> visited(h, vector<int>(l));
    stack<Point> s;
    s.push(Point(0, 0));
    cout << "dfs traversal: ";
    while(!s.empty()) {
        Point p = s.top();
        s.pop();
        if (p.x < 0 || p.y < 0 || p.x >= h || p.y >= l || visited[p.x][p.y])
            continue;
        visited[p.x][p.y] = true;
        cout << grid[p.x][p.y] << " ";
        s.push(Point(p.x, p.y - 1)); // left
        s.push(Point(p.x, p.y + 1)); // right
        s.push(Point(p.x - 1, p.y)); // up
        s.push(Point(p.x + 1, p.y)); // down
    }
}

void testDfs() {
    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
    };

    dfs(grid);
    cout << "\n";
}

int main(int argc, char *argv[]) {
    testDfs();
    return 0;
}
