[LeetCode 120] Triangle
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.


思路：
这题用到了一点DP的思路，即存储每一层的结果，来计算下一层。关键点在于要用O(n) space。
用两个数组prePath和curPath分别存储上一层和本层的每个坐标的min path sum。如果已知prePath，则可以计算curPath：

1. 对第j层 (j = 0 ~ n-1)，一共有j+1个数：0:j。而上一层有j个数：0:j-1
2. 除去头尾两个数外，curPath[i] = min(prePath[i-1], prePath[i]) + triangle[j][i]
3. 头尾的特殊情况：curPath[0] = prePath[0] + triangle[j][0]；curPath[j] = prePath[j-1] + triangle[j][j]
4. 在计算下一层前，需要交换curPath和prePath。
5. 在最后一层curPath计算结束后，在其中找一个最小值即为整个树的min path sum。

额外存储空间是2n。尽管通过滚动数组也可以事先n，但代码要复杂很多，面试短时间内容易出错。



Analysis:
DP problem,
Transaction function: A[n][i] = A[n][i] + min(a[n-1][i], a[n-1][i-1]).
Note that in this problem, "adjacent" of a[i][j] means a[i-1][j] and a[i-1][j-1], if available(not out of bound), while a[i-1][j+1] is not "adjacent" element.
If we do this from up to down, it is complicated. While from down to up, we could use only one array to scan every row to get result

// 12 ms
int minimumTotal(vector<vector<int> > &triangle) {
    int row = triangle.size();
    if(row == 0) return 0;
    vector<int> minV(triangle[row - 1].size());
    for(int i = row - 1; i >= 0; i--){
        int col = triangle[i].size();
        for(int j = 0; j < col; j++){
            if(i == row - 1){
                minV[j] = triangle[i][j];
                continue;
            }
            minV[j] = min(minV[j], minV[j + 1]) + triangle[i][j];
        }
    }
    return minV[0];
}


class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        if(triangle.empty()) return 0;
        int n = triangle.size();
        vector<int> curPath(n,INT_MAX);
        vector<int> prePath(n,INT_MAX);
        curPath[0] = triangle[0][0];
        
        for(int j = 1; j<n; j++) {
            prePath = curPath;
            curPath[0] = prePath[0] + triangle[j][0];
            curPath[j] = prePath[j-1] + triangle[j][j];
            for(int i = 1; i < j; i++)
                curPath[i] = min(prePath[i-1], prePath[i]) + triangle[j][i];
        }
        
        int minPath = INT_MAX;
        for(int i=0; i<n; i++) 
            minPath = min(minPath, curPath[i]);
        
        return minPath;
    }
};

