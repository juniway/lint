#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using std::vector;
using std::cout;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

void bfs(vector<vector<int>> grid) {
    int h = grid.size();
    if (h == 0) return;
    int l = grid[0].size();
    vector<vector<int>> visited(h, vector<int>(l));

    queue<Point> q;
    q.push(Point(0, 0));
    cout << "BFS Traversal: ";
    while(!q.empty()) {
        Point p = q.front();
        q.pop();

        if (p.x < 0 || p.y < 0 || p.x >= h || p.y >= l || visited[p.x][p.y])
            continue;

        visited[p.x][p.y] = true;
        cout << std::to_string(grid[p.x][p.y]) + " ";
        q.push(Point(p.x, p.y - 1));
        q.push(Point(p.x, p.y + 1));
        q.push(Point(p.x - 1, p.y));
        q.push(Point(p.x + 1, p.y));
    }
}

void testBfs() {
    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
    };

    bfs(grid);
    cout << "\n";
}

int main(int argc, char *argv[]) {
    testBfs();
    return 0;
}
