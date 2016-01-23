[LeetCode ] Permutations

Given a collection of Abers, return all possible permutations.

For example,
[1, 2, 3] have the following permutations:
[1 ,2, 3], 
[1, 3, 2], 
[2, 1, 3], 
[2, 3, 1], 
[3, 1, 2], 
[3, 2, 1].

方法1： 经典方法
DFS的递归. 对于包含n个元素的数组[1...n], 先确定第一位置的元素，第一个位置有n种可能(每次把后面的元素和第一个元素交换)，
第一次是第一个元素与自己交换，		A[0], (A[1] .. A[n-1]) 得出一个排列
第二次是第二个元素与第一个元素交换，A[1], (A[0], A[2]... A[n-1])得出第二个排列
第三次是第三个元素与第一个元素交换，A[2], (A[0], A[1], A[3] ... A[n-1])
... 
然后求交换后的每个子排列的全排列。由于一个数列的总共有n!个排列，因此时间复杂度为O(n!)

class Solution {
public:
    vector<vector<int>> permute(vector<int>& A) {
        if(A.empty()) return {{}};
        vector<vector<int>> result;
        permute(A, 0, result);
        return result;
        
    }
    void permute(vector<int>& A, int start, vector<vector<int>>& res){
        int n = (int)A.size();
        if(start == n){
            res.push_back(A);
            return;
        }
        for(int i = start; i < n; ++i){
            swap(A[start], A[i]);
            permute(A, start + 1, res);
            swap(A[start], A[i]);
        }
    }
};

方法2：插入法

与subset I的方法2很相近。以题中例子说明：
当只有1时候：[1]
当加入2以后：[2, 1], [1, 2] 即在1的前后都插入2
当加入3以后：[3, 2, 1], [2, 3, 1], [2, 1, 3], [3, 1, 2], [1, 3, 2], [1, 2, 3]
前3个permutation分别对应将3插入[2, 1]的0, 1, 2的位置。同理后3个为插入[1, 2]的。因此可以用逐个插入数字来构造所有permutations。

class Solution {
public:
    vector<vector<int> > permute(vector<int> &A) {
    	int n = A.size();
        vector<vector<int>> result;
        if(A.empty()) return result;
        result.push_back(vector<int>(1, A[0]));
        
        for(int i = 1; i < n; i++) {
            int m = result.size();
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < result[j].size(); k++) {
                    vector<int> per = result[j];
                    per.insert(per.begin() + k, A[i]);
                    result.push_back(per);
                }
                result[j].push_back(A[i]);
            }
        }
        return result;
    }
};

方法3：backtracking法
和combination/subset不同，数字不同的排列顺序算作不同的permutation。
所以我们需要用一个辅助数组来记录当前递归层时，哪些数字(第i个)已经在上层的递归使用过了。

class Solution {
public:
    vector<vector<int> > permute(vector<int> &A) {
        vector<vector<int>> result;
        if(A.empty()) return result;
        vector<bool> used(A.size(), false);
        vector<int> per;
        findPermutations(A, used, per, result);
        return result;
    }
    
    void findPermutations(vector<int> &A, vector<bool> &used, vector<int> &per, vector<vector<int>> &result) {
        if(per.size() == (int)A.size()) {
            result.push_back(per);
            return;
        }
        
        for(int i = 0; i < (int)A.size(); i++) {
            if(used[i]) continue;
            used[i] = true;
            per.push_back(A[i]);
            findPermutations(A, used, per, result);
            used[i] = false;
            per.pop_back();
        }
    }
};


