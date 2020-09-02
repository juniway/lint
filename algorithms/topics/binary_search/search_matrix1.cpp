#include <iostream>
#include <vector>
using namespace std;

bool searchMatrix(vector<vector<int>>& mat, int x) {
    int rowLow = 0, rowHigh = mat.size() - 1;
    int colLeft = 0, colRight = mat[0].size() - 1;

    while(rowLow <= rowHigh && colLeft <= colRight) {
        if (x == mat[rowLow][colRight]) return true;
        if (x > mat[rowLow][colRight]) {
            rowLow++;
        } else {
            colRight--;
        }
    }
    return false;
}

void testSearchMatrix() {
    vector<vector<int>> mat = {
        {10, 20, 30, 40, 45},
        {15, 25, 35, 45, 49},
        {27, 29, 37, 55, 59},
        {32, 33, 39, 56, 66}
    };

    cout << boolalpha << searchMatrix(mat, 32) << endl;
    cout << boolalpha << searchMatrix(mat, 34) << endl;
    cout << boolalpha << searchMatrix(mat, 56) << endl;
    cout << boolalpha << searchMatrix(mat, 67) << endl;
}

int main(int argc, char *argv[]) {
    testSearchMatrix();
    return 0;
}
