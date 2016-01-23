[LeetCode 217] Contain Duplicates

Given an array of integers, find if the array contains any duplicates. 
Your function should return true if any value appears at least twice in the array, 
and it should return false if every element is distinct.

// time: O(n)
// space: O(n)
class Solution {
  public:
    bool containsDuplicate(vector<int>& nums) {
        return set<int>(nums.begin(), nums.end()).size() < nums.size();
    }
};

// sort, then compare neighbor elements
class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); ++i)
            if (nums[i] == nums[i - 1])
                return true;
        return false;
    }
};