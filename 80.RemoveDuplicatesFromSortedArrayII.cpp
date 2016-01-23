// 
[LeetCode 80] Remove Duplicates from Sorted Array II
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?
For example,
Given sorted array A = [1, 1, 1, 2, 2, 3],
Your function should return length = 5, and A is now [1,1,2,2,3].



Analysis:
和I一样的思路, 区别仅仅在于当A[end-1] = A[end] = A[i]时, A[i]为重复元素需跳过。
而实际只需要比较A[end-1]和A[i], 因为当A[end-1] = A[i]时, 根据sorted arry特性必然也有A[end]=A[end-1]。

A = [1, 1, 1, 2, 2, 3]
		   ^     ^
		   end

class Solution {
public:
    int removeDuplicates(vector<int>& A) {
    	const int n = A.size();
        if(n < 3) return n;
        int end = 2;
        for(int i = 2; i < n; i++) {
            if(A[i] != A[end - 2]) 
                A[end++] = A[i];
        }
        return end;
    }
};
