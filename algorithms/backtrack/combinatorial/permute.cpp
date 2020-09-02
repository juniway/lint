#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// 47. Permutations II
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int> >res;
        permute(nums, 0, res);
        return res;
    }

    void permute(vector<int> nums, int start, vector<vector<int>> &res) {
        if (start == nums.size() - 1) {
            res.push_back(nums);
            return;
        }
        for (int i = start; i < nums.size(); i++) {
            if (i != start && nums[i] == nums[start]) continue;
            swap(nums[start], nums[i]);
            permute(nums, start + 1, res);
        }
    }
};

// class Solution {
// public:
//     vector<vector<int>> permuteUnique(vector<int>& nums) {
//         vector<vector<int>> ans;
//         permute(nums, 0, ans);
//         return ans;
//     }
//
//     void permute(vector<int>& nums, int start, vector<vector<int>>& ans) {
//         if (start == nums.size()) {
//             ans.push_back(nums);
//             return;
//         }
//         unordered_set<int> map;
//         for (int i = start; i < nums.size(); i++) {
//             if (!map.count(nums[i])) {
//                 map.insert(nums[i]);
//                 swap(nums[i], nums[start]);
//                 permute(nums, start + 1, ans);
//                 swap(nums[i], nums[start]);
//             }
//         }
//     }
// };

// class Solution {
// public:
//     vector<vector<int>> permute(vector<int>& nums) {
//         vector<vector<int>> ans;
//         permute(nums, 0, ans);
//         return ans;
//     }
//
//     void permute(vector<int>& nums, int start, vector<vector<int>>& ans) {
//         if (start == nums.size()) {
//             ans.push_back(nums);
//             return;
//         }
//         for (int i = start; i < nums.size(); i++) {
//             swap(nums[i], nums[start]);
//             permute(nums, start + 1, ans);
//             swap(nums[i], nums[start]);
//         }
//     }
// };
