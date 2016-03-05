[LeetCode 40] Combination Sum II
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).
The solution set must not contain duplicate combinations.
For example, given candidate set  1, 1, 2, 5, 6, 7, 10 and target 8,
A solution set is: 
[1, 7] 
[1, 2, 5] 
[2, 6] 
[1, 1, 6] 

分析：
按顺序把元素依次加到combination里，如果发现剩余的target已经小于当前元素了，
则弹出一个，继续判断下一个元素，如果剩余的target还是小于，则继续弹出，并转到下个元素
如果判断过程中发现前后两个元素相等，则skip一个，继续下一个


class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> sol;
        combinationSum2(candidates, 0, target, sol, result);
        return result;
    }
    
    void combinationSum2(vector<int> &candidates, int start, int target, vector<int> &sol, vector<vector<int>> &result){
        if(target == 0){
            result.push_back(sol);
            return;
        }
        for(int i = start; i < (int)candidates.size() && target >= candidates[i]; ++i){
            if(i == start || candidates[i] != candidates[i - 1]){
                sol.push_back(candidates[i]);
                combinationSum2(candidates, i + 1, target - candidates[i], sol, result);
                sol.pop_back();
            }
        }
    }
};