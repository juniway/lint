
/*

Given an array S of n integers, find three integers in S such that 
the sum is closest to a given number, target. Return the sum of the three integers.

Example
For example, given array S = {-1 2 1 -4}, and target = 1. 
The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

Note
You may assume that each input would have exactly one solution.

Challenge
O(n^2) time, O(1) extra space
*/

class Solution {
public:    
    /**
     * @param numsbers: Give an array numsbers of n integer
     * @param target: An integer
     * @return: return the sum of the three integers, the sum closest target.
     */
    int ThreeSumClosest(vector<int> nums, int target) {
        // write your code here
        const int n = nums.size();
        
        sort (nums.begin(), nums.end());
        int diff = nums[0] + nums[1] + nums[2] - target;
        for (int i = 0; i < n - 2; i++) {
            int start = i + 1, end = n - 1;
            
            while (start < end) {
                int d = nums[i] + nums[start] + nums[end] - target;
                if (d == 0) return target;
                
                if (abs(d) < abs(diff)) diff = d;
                
                if (d < 0) j++;
                else end--;
            }
        }
        
        return diff + target;
    }
};

