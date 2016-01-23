/*
[LeetCode 53] Maximum Subarray 求最大子数组和

Find the contiguous subarray within an array (containing at least one number) 
which has the largest sum.

For example, given the array [−2,1,−3,4,−1,2,1,−5,4],
the contiguous subarray [4,−1,2,1] has the largest sum = 6.

More practice:
If you have figured out the O(n) solution, 
try coding another solution using the divide and conquer approach, 
which is more subtle.

*/


class Solution{
public:
	int maxSubArray(int A[], int n){
		int sum = A[0];
		int dpSum = A[0];

		for (int i = 1; i < n; ++i){
			if(sum < 0) sum = 0;
			else{
				sum += A[i];
				dpSum = max(dpSum, sum);
			}		
		}

		return dpSum;
	}
};

class Solution {
public:
    int maxSubArray(vector<int>& A) {
        int n = A.size();
        
        int endhere = A[0];
        int maxsum = A[0];
        for(int i = 1; i < n; ++i){
            endhere = max(endhere + A[i], A[i]);
            maxsum = max(endhere, maxsum);
        }
        return maxsum;
    }
};
