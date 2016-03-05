[LeetCode 48] Rotate Image
You are given an n x n 2D matrix representing an image.
Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?

算法1:
(1) 先转置(沿主对角线翻转)，再沿垂直线左右翻转
1    2        1  |  3        3    1
   \    --->     |     --->
3    4        2  |  4        4    2

(2) 沿副对角线翻转，再沿水平线上下翻转
1    2        4     2        3    1
   /    --->  ———————      --->
3    4        3     1        4    2

class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();
        //转置
        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++)
                swap(matrix[i][j] , matrix[j][i]);
        //左右翻转
        for(int i = 0; i < n; i++)
            for(int j = 0; j < (n>>1); j++)
                swap(matrix[i][j], matrix[i][n-j-1]);
    }
};

算法2:

1   2   3   4
5   6   7   8
9   10  11  12
13  14  15  16

可以见矩阵看成多个环组成，如下4*4的矩阵包括两个环，
外环为1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 1，内环为6, 7, 11, 10。

旋转一个矩阵，相当于把每一个环都旋转。如何旋转一个环呢？以最外层的环举例:

旋转前:
1   2   3   4      |1         4 | |     2      |  |        3     |
5           8      |            | |           8|  |5             |
9           12     |            | |9           |  |            12|
13  14  15  16     |13        16| |         15 |  |    14        |

旋转后:
13  9   5   1
14          2
15          3
16  12  8   4

我们把环分成3组：{1, 4, 16, 13}，{2, 8, 15, 9}，{3, 12, 14, 5}，
每一组中：旋转后相当于把原来的数字移动到同组中下一个数字的位置
对于一个n*n的矩阵可以分成n/2（向上取整）个环来旋转；
对于边长为len的环，可以分成len-1组来旋转。
class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();
        if(n == 0)return;
        for(int i = 0, len = n; i < n/2; i++, len -= 2){
        // n/2 为旋转的圈数，len为第i圈中正方形的边长
            int m = len - 1;
            for(int j = 0; j < m; j++){
                int tmp = matrix[i][i+j];
                matrix[i][i+j] = matrix[i+m-j][i];
                matrix[i+m-j][i] = matrix[i+m][i+m-j];
                matrix[i+m][i+m-j] = matrix[i+j][i+m];
                matrix[i+j][i+m] = tmp;
            }
        }
    }
};
