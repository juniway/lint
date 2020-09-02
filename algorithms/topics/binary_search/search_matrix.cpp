#include <iostream>
#include <vector>

using namespace std;

bool searchArray(vector<int>& a, int x) {
    int left = 0, right = a.size() - 1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == x) {
            return true;
        } else if (a[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}

bool searchMatrix(vector<vector<int>>& mat, int x) {
    if (mat.size() == 0) return false;
    int top = 0, bottom = mat.size() - 1;
    while(top <= bottom) {
        int mid = top + (bottom - top) / 2;
        if (searchArray(mat[mid], x)) return true;
        if(x < mat[mid][0]) {
            bottom = mid - 1;
        } else {
            top = mid + 1;
        }
    }

    return false;
}

void testSearchMatrix() {
    vector<vector<int>> mat = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 50}
    };

    cout << boolalpha << searchMatrix(mat, 3) << endl;
    cout << boolalpha << searchMatrix(mat, 4) << endl;
}

int main(int argc, char *argv[]) {
    testSearchMatrix();
    return 0;
}
