#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct BuildingBlock{
    int row, col, distance;
    BuildingBlock(int row, int col):row(row), col(col) {}
};

BuildingBlock findBikeBFS(vector<vector<int>> buildings, BuildingBlock&& bb, vector<vector<bool>>& visited) {
    int n = buildings.size();
    int m = buildings[0].size();

    if (bb.row < 0 || bb.row >= n \
            || bb.col < 0 || bb.col >= m || visited[bb.row][bb.col])
        return BuildingBlock(-1, -1);

    if (buildings[bb.row][bb.col] == 1) {
        bb.distance = 1;
        return bb;
    }

    visited[bb.row][bb.col] = true;

}

BuildingBlock findBike(vector<vector<int>> buildings, int start_row, int start_col) {
    int row_size = buildings.size();
    if (row_size == 0) return BuildingBlock(-1, -1);
    int col_size = buildings[0].size();
    if (col_size == 0) return BuildingBlock(-1, -1);

    vector<vector<bool>> visited(row_size, vector<bool>(col_size, false));

    return findBikeBFS(buildings, BuildingBlock(start_row, start_col));

}
