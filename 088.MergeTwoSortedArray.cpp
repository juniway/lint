Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) 
to hold additional elements from nums2. 
The number of elements initialized in nums1 and nums2 are m and n respectively.

分析：
考虑从后往前比较，这样就不会产生需要数据后移的问题了。时间复杂度O(n+m)

class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        int i = m - 1, j = n - 1;
        int k = m + n - 1;
        while(i >= 0 && j >= 0){
            if(A[i] > B[j]) A[k--] = A[i--];
            else A[k--] = B[j--];
        }
        if(i < 0) while(j >= 0) A[k--] = B[j--];
        if(j < 0) while(i >= 0) A[k--] = A[i--];
    }
};