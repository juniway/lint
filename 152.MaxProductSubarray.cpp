[LeetCode 152] Maximum Product Subarray

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

class Solution {
public:
    int maxProduct(vector<int>& A) {
        int n = A.size();

        int curMax = A[0], curMin = A[0];
        for(int i = 1; i < n; ++i){
        	int tmpMax = curMax;
        	curMax = max(max(curMax*A[i], curMin*A[i]), A[i]);
        	curMin = min(min(curMax*A[i], curMin*A[i]), A[i]);
        }

        return max(curMax, curMin);
	    
	        
	}
};

Maximum Product Subarray其实只需要不断地记录两个值，max和min。
max是到当前为止最大的正product，min是到当前为止最小的负product，或者1。

public int maxProduct(int[] A) {
    int x = 1;
    int max = 1;
    int min = 1;
    for (int i = 0; i < A.length; i++) {
        if (A[i] == 0) {
            max = 1;
            min = 1;
        } else if (A[i] > 0) {
            max = max * A[i];
            min = Math.min(min * A[i], 1);
        } else {
            int temp = max;
            max = Math.max(min * A[i], 1);
            min = temp * A[i];
        }
        if (max > x)
            x = max;
    }
    return x;
}