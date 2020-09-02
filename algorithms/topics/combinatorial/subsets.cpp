#include <iostream>
#include <vector>
using namespace std;

// vector<vector<int> > subsets(vector<int> &S) {
//     vector<vector<int> > res(1);
//     sort(S.begin(), S.end());
//     for (int i = 0; i < S.size(); ++i) {
//         int size = res.size();
//         for (int j = 0; j < size; ++j) {
//             res.push_back(res[j]);
//             res.back().push_back(S[i]);
//         }
//     }
//     return res;
// }

void dfs(vector<int>& nums, int start, vector<int>& sol, vector<vector<int>>& ans) {
    ans.push_back(sol);
    for (int i = start; i < nums.size(); i++) {
        sol.push_back(nums[i]);
        dfs(nums, i + 1, sol, ans);
        sol.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ans;
    vector<int> sol;
    dfs(nums, 0, sol, ans);
    return ans;
}


void testSubsets() {
    vector<int> nums = {1, 2, 3};
    subsets(nums);
}

int main(int argc, char *argv[]) {
    testSubsets();
    return 0;
}
