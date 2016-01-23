[LeetCode 39] Combination Sums

Given a set of candidate numbers (C) and a target number (T), 
find all unique combinations in C where the candidate numbers sums to T.
The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set 2, 3, 6, 7 and target 7, 
A solution set is: 
[7]
[2, 2, 3]

分析：
每次把candidate当前元素push进去，直到最后target剩下得已经小于第一个值了，再弹出一个，
然后递归到i+1，现在i+1是当前元素了，把这个当前元素放进去，如果剩余的target又小于这个当前元素，
那么继续弹出一个，然后i+2，现在递归到i+2成为当前元素了，继续上面的判断

是一个bottom up的递归方式

// 16ms
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> result;
        vector<int> sol;
        sort(candidates.begin(), candidates.end());
        combinationSum(candidates, 0, target, sol, result);
        return result;
    }
    
    void combinationSum(vector<int> &candidates, int start, int target, vector<int> &sol, vector<vector<int>> &res){
        if(target == 0){
            res.push_back(sol);
            return;
        }
        
        for(int i = start; i < (int)candidates.size() && target >= candidates[i]; ++i){ // 只有当前candidates[i] < target 时才push
            sol.push_back(candidates[i]);
            combinationSum(candidates, i, target - candidates[i], sol, res); // 由于允许用重复元素，所以下一个还是从i开始
            sol.pop_back();
        }
    }
};

// 28ms
class Solution {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
	    vector<int> solution;
	    vector<vector<int>> result;
	    int sum = 0;
	    sort(candidates.begin(), candidates.end());
	    getCombineSum(sum, 0, target, solution, candidates, result);
	    return result;
	}

private:
	void getCombineSum(int &sum, int level,int target,
	                   vector<int> &solution,
	                   vector<int> &candidates,
	                   vector<vector<int>> &result
	                   ){
	    if(sum > target) return;
	    if(sum == target){
	        result.push_back(solution);
	        return;
	    }
	    for(int i = level; i < candidates.size(); i++){
	        sum += candidates[i];
	        solution.push_back(candidates[i]);
	        getCombineSum(sum, i, target, solution, candidates, result);
	        solution.pop_back();
	        sum -= candidates[i];
	    }

	}
};

