[LeetCode 28]  Search in Rotated Sorted Array
Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.

Difficulty: Hard

class Solution {
public:
    int search(vector<int>& A, int target) {
        int n = (int)A.size();
        int l = 0, r = n - 1;
        while(l <= r){
            int mid = l + (r - l)/2;
            if(target == A[mid]) return mid;
            if(A[mid] < A[l]){
                if(target > A[mid] && target <= A[r])
                    l = mid  + 1;
                else r = mid - 1;
            }
            else{
                if(target < A[mid] && target >= A[l])
                    r = mid - 1;
                else
                    l = mid + 1;
            }
        }
        return -1;
    }
};