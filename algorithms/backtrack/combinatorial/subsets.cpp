#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        vector<int> sol;
        dfs(nums, 0, sol, ans);
        return ans;
    }

    void dfs(vector<int>& nums, int start, vector<int> sol, vector<vector<int>>& ans) {
        ans.push_back(sol);
        for (int i = start; i < nums.size(); i++) {
            if (i > start && i > 0 && nums[i] == nums[i - 1]) continue;
            sol.push_back(nums[i]);
            dfs(nums, i + 1, sol, ans);
            sol.pop_back();
        }
    }
};

void testSubsets() {
    vector<int> a = { 1, 2, 2 };
    Solution sol;
    sol.subsetsWithDup(a);
}

int main(int argc, char *argv[]) {
    testSubsets();
    return 0;
}
