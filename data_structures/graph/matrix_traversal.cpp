#include <iostream>
#include <vector>

using namespace std;

// main diagnal
void left_bottom_triangle(vector<vector<int>> &mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j <= i - 1; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void right_top_triangle(vector<vector<int>> &mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = i + 1; j < mat[i].size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

// sub diagnal
void right_bottom_triangle(vector<vector<int>>& mat) {
    int n = mat.size();
    for (int i = 0; i < mat.size(); i++) {
        for (int j = n - i; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void left_top_triangle(vector<vector<int>>& mat) {
    int n = mat.size();
    for (int i = 0; i < mat.size(); i++)  {
        for (int j = 0; j < n - 1 -i; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

void testTriangle() {
    vector<vector<int>> mat = {
        {0, 1, 2, 3, 4},
        {5, 6, 7, 8, 9},
        {10, 11, 12, 13, 14},
        {15, 16, 17, 18, 19},
        {20, 21, 22, 23, 24},
    };

    left_bottom_triangle(mat);
    right_top_triangle(mat);
    left_top_triangle(mat);
    right_bottom_triangle(mat);
}

int main(int argc, char *argv[]) {
    testTriangle();
    return 0;
}
