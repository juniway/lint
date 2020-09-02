#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct BuildingBlock{
    int row, col, distance;
    BuildingBlock() : distance(-1){}
    BuildingBlock(int row, int col, int distance = 0):row(row), col(col), distance(distance) {}
};

bool validMove(int n, int m, int x, int y, const vector<vector<bool>>& visited) {
    return (x >= 0 && x < n && y >= 0 && y < m && !visited[x][y]);
}

BuildingBlock findBike(vector<vector<int>> buildings, int start_row, int start_col) {
    BuildingBlock invalidBb;
    int row_size = buildings.size();
    if (row_size == 0) return invalidBb;
    int col_size = buildings[0].size();
    if (col_size == 0) return invalidBb;

    vector<vector<bool>> visited(row_size, vector<bool>(col_size, false));

    queue<BuildingBlock> q;

    q.push(BuildingBlock(start_row, start_col));
    visited[start_row][start_col] = true;

    while(!q.empty()) {
        BuildingBlock bb = q.front();
        q.pop();
        int d = bb.distance + 1;

        BuildingBlock b_up(bb.row - 1, bb.col, d);
        if (validMove(row_size, col_size, b_up.row, b_up.col, visited)) {
            if (buildings[b_up.row][b_up.col] == 1) return b_up;
            q.push(b_up);
            visited[b_up.row][b_up.col] = true;
        }


        BuildingBlock b_down(bb.row + 1, bb.col, d);
        if (validMove(row_size, col_size, b_down.row, b_down.col, visited)) {
            if (buildings[b_down.row][b_down.col] == 1) return b_down;
            q.push(b_down);
            visited[b_down.row][b_down.col] = true;
        }

        BuildingBlock b_left(bb.row, bb.col - 1, d);
        if (validMove(row_size, col_size, b_left.row, b_left.col, visited)) {
            if (buildings[b_left.row][b_left.col] == 1) return b_left;
            q.push(b_left);
            visited[b_left.row][b_left.col] = true;
        }

        BuildingBlock b_right(bb.row, bb.col + 1, d);
        if (validMove(row_size, col_size, b_right.row, b_right.col, visited)) {
            if (buildings[b_right.row][b_right.col] == 1) return b_right;
            q.push(b_right);
            visited[b_right.row][b_right.col] = true;
        }
    }

    return invalidBb;

}

void testNearestBuilding() {
    vector<vector<int>> buildings = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0},
    };

    int start_row = 0, start_col = 3;
    BuildingBlock res = findBike(buildings, start_row, start_col);
    cout << "the nearest building is: \n"
        << res.row << ", " << res.col << "\n" \
        << res.distance << "\n";
}

int main(int argc, char *argv[]) {
    testNearestBuilding();
    return 0;
}
