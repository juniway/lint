
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

                else if (d < 0) j++;
                else end--;
            }
        }

        return diff + target;
    }
};

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 3) return INT_MAX;
        int mindiff = INT_MAX;
        sort(nums.begin(), nums.end());

        for(int i = 0; i < n - 2; ++i){
            int a = nums[i], start = i + 1, end = n - 1;
            while(start < end){
                int b = nums[start], c = nums[end];
                int diff = (a + b + c) - target;

                if(abs(mindiff) > abs(diff)) mindiff = diff;
                if(diff == 0) {
                    mindiff = diff;
                    break;
                }
                if(diff < 0) ++start;
                if(diff > 0) --end;
            }
        }
        return target + mindiff;

    }
};

思路：

3sum问题的变种。一样的遍历每个数，对剩余数组进行双指针扫描。区别仅仅在于当：
sum = A[left] + A[right]
(1) sum = target时直接返回
(2) sum != target时，在相应移动left/right指针之前，先计算abs(sum-target)的值，并更新结果。

class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        if(num.size()<3) return INT_MAX;
        sort(num.begin(),num.end());
        int minDiff = INT_MAX;
        for(int i=0; i < num.size()-2; i++) {
            int left=i+1, right = num.size()-1;
            while(left<right) {
                int diff = num[i]+num[left]+num[right]-target;
                if(abs(diff)<abs(minDiff)) minDiff = diff;
                if(diff==0)
                    break;
                else if(diff<0)
                    left++;
                else
                    right--;
            }
        }
        return target+minDiff;
    }
};












class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int small = 0;

        sort(nums.begin(), nums.end());

        int i = 0, j = nums.size() - 1;
        while(i < j){
            int sum = nums[i] + nums[j];
            diff = target - sum;
            if(diff == 0) small = diff;
            if(diff < 0) ++i;
            if(diff > 0) --j;

            if(small > abs(diff)) small = abs(diff);
        }
        return small;

    }
};
