[LeetCode 78] SubSets
Given a set of distinct integers, nums, return all possible subsets.

Note:
Elements in a subset must be in non-descending order.
The solution set must not contain duplicate subsets.
For example,
If nums = [1, 2, 3], a solution is:

[
  [3],
  [1],
  [2],
  [1, 2, 3],
  [1, 3],
  [2, 3],
  [1, 2],
  []
]


方法1：经典方法 backtracking

与combination/combination sum I, II思路一样。
区别在于单层扫描时不用跳过重复数字，而在进入下一层递归前就需要把当前subset压入结集中。
注意：解这类排列问题都要先sort!

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& A) {
        vector<vector<int>> result;
        vector<int> sol;
        result.push_back(sol);
        sort(A.begin(), A.end());
        subsets(A, 0, sol, result);
        return result;
    }
    void subsets(vector<int>& A, int start, vector<int>& sol, vector<vector<int>>& result){
        for(int i = start; i < (int)A.size(); ++i){
            sol.push_back(A[i]);
            result.push_back(sol);
            subsets(A, i + 1, sol, result);
            sol.pop_back();
        }
    }
};

方法2：添加数字构建subset 

起始subset集为：[]
添加S0后为：[], ++++++++++ [S0]
添加S1后为：[], [S0], ++++++++++ [S1], [S0, S1]
添加S2后为：[], [S0], [S1], [S0, S1], ++++++++++ [S2], [S0, S2], [S1, S2], [S0, S1, S2]
红色subset为每次新增的。显然规律为添加Si后，新增的subset为克隆现有的所有subset，并在它们后面都加上Si。

class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int>> result;
        vector<int> sol;
        result.push_back(sol);
        sort(S.begin(), S.end());
        for(int i = 0; i < S.size(); i++) {
            int n = result.size();
            for(int j = 0; j < n; j++) {
                sol = result[j];
                sol.push_back(S[i]);
                result.push_back(sol);
            }
        }
        return result;
    }
};

方法3：bit manipulation

由于S[0: n-1]组成的每一个subset，可以看成是对是否包含S[i]的取舍。
S[i]只有两种状态，包含在特定subset内，或不包含。
所以subset的数量总共有2^n个。所以可以用0~2^n-1的二进制来表示一个subset。
二进制中每个0/1表示该位置的S[i]是否包括在当前subset中。

class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int>> allSets;
        sort(S.begin(), S.end());
        unsigned long long maxNum = pow(2, S.size()) - 1;
        for(unsigned long long i=0; i<=maxNum; i++) 
            allSets.push_back(num2subset(S, i));
        return allSets;
    }
    
    vector<int> num2subset(vector<int> &S, unsigned long long num) {
        vector<int> sol;
        int i=0;
        while(num) {
            if(num & 1) sol.push_back(S[i]);
            num >>= 1;
            i++;
        }
        return sol;
    }
};

