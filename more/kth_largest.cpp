// [LeetCode 215] Kth Largest Element in an Array
// Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

// For example,
// Given [3,2,1,5,6,4] and k = 2, return 5.

// Note: 
// You may assume k is always valid, 1 ≤ k ≤ array's length.

// Credits: 
// Special thanks to @mithmatt for adding this problem and creating all test cases.

// Time:  O(n)
// Space: O(1)

class Solution {
public:
    /*
     * param k : description of k
     * param nums : description of array and index 0 ~ n-1
     * return: description of return
     */
    int kthLargestElement(vector<int> nums, int k) {
        int left = 0, right = nums.size() - 1;
        default_random_engine gen((random_device())());
        while (left <= right) {
            // Generates a random int in [left, right].
            uniform_int_distribution<int> dis(left, right);
            int pivot_idx = dis(gen);
            int new_pivot_idx = PartitionAroundPivot(nums, left, right, pivot_idx);
            if (new_pivot_idx == k - 1) {
                return nums[new_pivot_idx];
            } else if (new_pivot_idx > k - 1) {
                right = new_pivot_idx - 1;
            } else {  // new_pivot_idx < k - 1.
                left = new_pivot_idx + 1;
            }
        }
    }

    // Partition nums[left : right] around pivot_idx, returns the new index of the
    // pivot, new_pivot_idx, after partition. After partitioning,
    // nums[left : new_pivot_idx - 1] contains elements that are greater than the
    // pivot, and nums[new_pivot_idx + 1 : right] contains elements that are less
    // than the pivot.
    int PartitionAroundPivot(vector<int>& nums, int left, int right, int pivot_idx) {
        int pivot_value = nums[pivot_idx];
        int new_pivot_idx = left;
        swap(nums[pivot_idx], nums[right]);
        for (int i = left; i < right; ++i) {
            if (nums[i] > pivot_value) {
                swap(nums[i], nums[new_pivot_idx++]);
            }
        }
        swap(nums[right], nums[new_pivot_idx]);
        return new_pivot_idx;
    }
};

class Solution2 {
public:
    /*
     * param k : description of k
     * param nums : description of array and index 0 ~ n-1
     * return: description of return
     */
    int kthLargestElement(vector<int> nums, int k) {
        nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), greater<int>());
        return nums[k - 1];
    }
};