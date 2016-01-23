[LeetCode 215] kth Largest Element in an Array

// quick select algorithm:
// Time: O(n) Space: O(1) for in-place
// 4 ms
class Solution {
public:
    int findKthLargest(vector<int>& A, int k) {
        int n = A.size();
        int left = 0, right = n - 1;
        default_random_engine gen((random_device())());
        while (left <= right) {
            // Generates a random int in [left, right].
            uniform_int_distribution<int> dis(left, right);
            int rnd_idx = dis(gen); // a random index as pivot index
            int new_pivot_idx = PartitionAroundPivot(left, right, rnd_idx, A);
            if (new_pivot_idx == k - 1) {
                return A[new_pivot_idx];
            } else if (new_pivot_idx > k - 1) {
                right = new_pivot_idx - 1;
            } else {
                left = new_pivot_idx + 1;
            }
        }
    }
    int PartitionAroundPivot(int left, int right, int rnd_idx, vector<int>& A) {
        int pivot_value = A[rnd_idx];
        int new_pivot_idx = left;
        swap(A[rnd_idx], A[right]);
        for (int i = left; i < right; ++i) {
            if (A[i] > pivot_value) {
                swap(A[i], A[new_pivot_idx++]);
            }
        }
        swap(A[right], A[new_pivot_idx]);
        return new_pivot_idx;
    }
};