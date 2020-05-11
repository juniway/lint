// LeetCode Weekly Contest 28

// Continous Subarray Sum

Question

Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to the multiple of k, that is, sums up to n*k where n is also an integer.

Example 1:
Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
Example 2:
Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.

Note:
The length of the array won't exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.


分析：
i 遍历数组，并累加 sum，如果在 i 的位置, rem = sumAt(i) % k，rem 不为 0（也即不能整除），那么，假设从 i 的位置往回的方向存在一个 j 位置，也有一个 rem = sumAt(j) % k，
两个 rem 相等，那么说明，从 i 到 j 之间的元素是 k 的倍数，也即 nk。

基于上述分析，在一个 map 里面存 <rem, index> 即可，当遍历到位置 i 时，计算当前 rem，然后看看 map 里面是否存在这个 rem，如果存在，说明存在一个 j，其到 i 之间的元素满足时 k 的倍数。


class Solution {
public:
    bool checkSubarraySum(vector<int> &nums, int k) {
        int sum = 0;
        map<int, int> m;
        m[0] = -1;
        for (int i = 0; i < nums.length(); i++) {
            sum += nums[i];
            if (k != 0)
                sum = sum % k;
            if (m.find(sum) != m.end()) {
                if (i - map[sum] > 1)
                    return true;
            } else
                m[sum] = i;
        }
        return false;
    }
};