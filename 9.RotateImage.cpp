/*
You are given an n x n 2D matrix representing an image. Rotate the image by 90 degrees (clockwise).

Have you met this question in a real interview? Yes
Example
Given a matrix

[
    [1,2],
    [3,4]
]
rotate it by 90 degrees (clockwise), return

[
    [3,1],
    [4,2]
]
Challenge
Do it in-place.
*/


class Solution {
public:
    /**
     * @param matrix: A list of lists of integers
     * @return: Void
     */
     
     // time: o(n^2), space: o(1)
    void rotate(vector<vector<int> > &matrix) {
        // write your code here
        const int n = matrix.size();
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n - i; ++j)
                swap(matrix[i][j], matrix[n - 1 -j][n - 1 - i]);
        }
        for(int i = 0; i < n / 2; ++i)
            for(int j = 0; j < n; ++j)
                swap(matrix[i][j], matrix[n - 1 - i][j]);
    }
};
