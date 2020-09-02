// Leetcode 200
#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

// 1. DFS
void dfs(vector<vector<char>>& grid, int i, int j) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != '1') return;
    grid[i][j] = '*';
    dfs(grid, i + 1, j); // down
    dfs(grid, i - 1, j); // up
    dfs(grid, i, j + 1); // right
    dfs(grid, i, j - 1); // left
}


// 2. BFS iteratively
void bfs(vector<vector<char>>& grid, int i, int j) {
    queue<pair<int, int>> q;
    q.push(make_pair(i, j));
    while(!q.empty()) {
        auto p = q.front(); q.pop();
        int y = p.first, x = p.second;
        if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size() || grid[y][x] == '*') continue;

        grid[y][x] = '*';
        q.push(make_pair(y + 1, x));
        q.push(make_pair(y - 1, x));
        q.push(make_pair(y, x + 1));
        q.push(make_pair(y, x - 1));
    }
}

// 3. BFS recursive
void bfs(vector<vector<char>>& grid, queue<pair<int,int>>& q) {
    while(!q.empty()) {
        int y = q.front().first, x = q.front().second; q.pop();
        if (y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size() || grid[y][x] == '*') continue;
        grid[y][x] = '*';
        q.push(make_pair(y + 1, x));
        q.push(make_pair(y - 1, x));
        q.push(make_pair(y, x + 1));
        q.push(make_pair(y, x - 1));
        bfs(grid, q);
    }
}

// 4. Union Find
class UnionFind {
public:
    UnionFind(int n) {
        ranks = vector<int> (n, 0);
        parents = vector<int> (n, 0);
        // iota(parents.begin(), parents.end(), 0);
        for (int i = 0; i < n; i++) {
            parents[i] = i;
            printf("parents[%d] = %d\n", i, i);
            printf("parents(%d, %d) = (%d, %d)\n", i / n, i % n, i / n, i % n);
        }

        num = n;
    }

    int Find(int u) {
        if (parents[u] != u) {
            parents[u] = Find(parents[u]); // path compression
        }
        return parents[u];
    }

    bool Union(int u, int v, int i, int j, int y, int x, int n) {
        int pu = Find(u), pv = Find(v);
        int ux1 = pu % n;
        int uy1 = pu / n;
        int vx1 = pv % n;
        int vy1 = pv / n;
        printf("before(original): (%d, %d) => (%d, %d)\n", i, j, uy1, ux1);
        printf("before(one step): (%d, %d) => (%d, %d)\n", y, x, vy1, vx1);
        if (pu == pv) return false;
        if (ranks[pv] > ranks[pu]) {
            parents[pu] = pv;
            printf("after(v>u): (%d, %d) => (%d, %d)\n", uy1, ux1, vy1, vx1);
        }
        else if (ranks[pv] < ranks[pu]) {
            parents[pv] = pu;
            printf("after(v<u): (%d, %d) => (%d, %d)\n", vy1, vx1, uy1, ux1);
        }
        else {
            parents[pv] = pu;
            printf("after(u==v): (%d, %d) => (%d, %d)\n", vy1, vx1, uy1, ux1);
            ranks[pu] += 1;
        }
        num--;
        return true;
    }

    int size() {
        return num;
    }

private:
    vector<int> parents;
    vector<int> ranks;
    int num;
};

int numIslands2(vector<vector<char>>& grid) {
    if (grid.size() == 0 || grid[0].size() == 0) return 0;
    int m = grid.size(), n = grid[0].size(), zeros = 0;
    int directions[2][2] = {{0, 1}, {1, 0}};
    UnionFind uf(m*n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '0') { zeros++; continue;  } // important!
            if (grid[i][j] == '1') {
                for (int k = 0; k < 2; k++) {
                    int y = i + directions[k][0];
                    int x = j + directions[k][1];
                    if (y < 0 || y >= m || x < 0 || x >= n || grid[y][x] != '1') continue;
                    uf.Union(i*n + j, y*n + x, i, j, y, x, n);
                }
            }
        }
    }

    return uf.size() - zeros;
}

int numIslands(vector<vector<char>>& grid) {
    int num = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '1') {
                num++;
                dfs(grid, i, j);
            }
        }
    }
    return num;
}

int numIslands1(vector<vector<char>>& grid) {
    int num = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '1') {
                num++;
                // bfs(grid, i, j);
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                bfs(grid, q);
            }
        }
    }
    return num;
}

void testNumIslands() {
    vector<vector<char>> input = {
        {'0', '1', '1', '1', '1'},
        {'0', '0', '1', '0', '0'},
        {'0', '1', '1', '0', '1'},
        {'0', '0', '0', '1', '1'}
    };

    // cout << numIslands(input) << endl;
    cout << numIslands2(input) << endl;
}

int main(int argc, char *argv[]) {
    testNumIslands();
    return 0;
}
