[LeetCode 77]  Combinations
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:
[
  [2, 4],
  [3, 4],
  [2, 3],
  [1, 2],
  [1, 3],
  [1, 4],
]

思路：采用深度优先搜索策略

// 代码一：比较经典的递归写法
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > result;
        vector<int> path;
        combine(n, k, 1, 0, path, result); // 1, 2, 3, 4
        return result;
    }
  
private:
    // start，开始的数, cur，已经选择的数目
    static void combine(int n, int k, int start, int cur,
        vector<int> &path, vector<vector<int> > &result){
        if (cur == k) // 可以用result.size() == k 代替
            result.push_back(path);

        for (int i = start; i <= n; ++i){
            path.push_back(i);
            combine(n, k, i + 1, cur + 1, path, result);
            path.pop_back();
        }
    }
};

// 代码二：
class Solution {
public:
  vector<vector<int> > combine(int n, int k) {
    vector<vector<int>> result;
    if(n < k || k <= 0) return result;
    
    return combine_helper(1, n, k);
  }
  
private:
  vector<vector<int>> combine_helper(int start, int end, int k){
    vector<vector<int>> result;
    
    if(k == 1){
      for(int i = start; i <= end; i++){
        vector<int> temp;
        temp.push_back(i);
        result.push_back(temp);
      }
      return result;
    }
    
    for(int i = start; i <= end - k + 1; i++){
      vector<vector<int>> temp;
      temp = combine_helper(i + 1, end, k - 1);
      for(int j = 0; j < temp.size(); j++){
        temp[j].insert(temp[j].begin(), i);
        result.push_back(temp[j]);   
      }
    }
    
    return result;
  }
};



class Solution{
public:
  vector<vector<int> > combine(int n, int k) {
    vector<int> solution;
    vector<vector<int>> result;
    getCombine(n, k, 1, solution, result);
    return result;
  }

private:
  void getCombine(int n, int k, int level, vector<int> &solution,
                vector<vector<int>> &result){
    if(solution.size() == k){
        result.push_back(solution);
        return;
    }
    for(int i = level; i<=n; i++){
        solution.push_back(i);
        getCombine(n,k,i+1,solution,result);
        solution.pop_back();
    }
  }
};


