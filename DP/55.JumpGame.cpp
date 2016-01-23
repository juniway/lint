[LeetCode 55] jump Game
Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.
For example:
A = [2, 3, 1, 1, 4], return true.
A = [3, 2, 1, 0, 4], return false.

分析：
注意题目中A[i]表示的是在位置i，“最大”的跳跃距离，而并不是指在位置i只能跳A[i]的距离。
所以当跳到位置i后，能达到的最大的距离至少是i+A[i]。
用greedy来解，记录一个当前能达到的最远距离maxIndex：

1. 能跳到位置i的条件：i<=maxIndex。
2. 一旦跳到i，则maxIndex = max(maxIndex, i+A[i])。
3. 能跳到最后一个位置n-1的条件是：maxIndex >= n-1

class Solution {
public:
    bool canJump(vector<int>& A) {
        int n = A.size();
        int maxCover = 0;
        for(int i = 0; i <= maxCover && i < n; i++)
        {
            maxCover = max(maxCover, i + A[i]);
            if(maxCover >= n-1) return true;
        }
        return false;
    }
};



Jump Game II

Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.
For example:
Given array A = [2,3,1,1,4]
The minimum number of jumps to reach the last index is 2. 
(Jump 1 step from index 0 to 1, then 3 steps to the last index.)

分析：
同样可以用greedy解决。
与I不同的是，求的不是对每个i，从A[0:i]能跳到的最远距离；而是计算跳了k次后能达到的最远距离，这里的通项公式为：

d[k] = max(i+A[i])     d[k-2] < i <= d[k-1]

/*
 * We use "last" to keep track of the maximum distance that has been reached
 * by using the minimum steps "step", whereas "curr" is the maximum distance
 * that can be reached by using "step + 1" steps. Thus,
 * curMax = max(i+A[i]) where 0 <= i <= last.

 before i exceed last value, step doesn't need to be updated, so it guarantees
 minimum step

 */
class Solution {
public:
    int jump(vector<int> A) {
    	int n = A.size();
        int step = 0;
        int last = 0;
        int curMax = 0;
        for (int i = 0; i < n; ++i) {
            if (i > last) {
            	if (curMax == last && last < n - 1) return -1;   // if no solution
                last = curMax;
                ++step;
            }
            curMax = max(curMax, i + A[i]);
        }

        return step;
    }
};

In DP, if you use an array to track the min step at [i], 
not only will you know the minimum steps needed to get to the destination, 
but also how to get there. With simple calculation on your array, 
you can find every optimal road to the end.

This unnecessary information lead to unnecessary cost.
What we really need to do is to calculate: with k steps, what is the furthest point I can reach.

class Solution {
public:
	int jump(vector<int> A){
		int n = A.size();
		
	    int minSteps = 0;
	    int furthest = 0;
	    int i = 0;
	    while(furthest < n - 1){
	        while(i <= furthest){
	            furthest = max(furthest, i + A[i]);
	            i++;
	        }
	        if(furthest == furthest) return -1; // this.time.furthest == last.time.furthest: we're trapped, which means the destination cannot be reached.
	        minSteps++;
	    }
	    return minSteps;
	}
};

In BFS, u can also find the optimal path using the resulting spanning tree, all in O(n). 
So I don't agree w/ your explanation of DP's higher time complexity, which is brought by redundant calculation to me.

class Solution {
    vector<int> opt;
public:
    int jump(int A[], int n) {
        opt.assign(n, -1);
        // set destination to be immediately available (0 step)
        opt[n - 1] = 0;
        return helper(A, n, 0);
    }

    int helper(int A[], int n, int index) {
        if (opt[index] == -1) {
            // max position we can reach jumping from index
            int max_pos = index + A[index];
            // one step to reach destination
            if (max_pos >= n - 1) opt[index] = 1;
            else { // DP
                for (int i = index + 1; i <= index + A[index]; i++) {
                    // Optimization: test if jump from start takes fewer steps
                    if (i + A[i] <= max_pos) continue;
                    int steps = helper(A, n, i);
                    if (steps != -1 && (opt[index] == -1 || steps + 1 < opt[index]))
                        opt[index] = steps + 1;
                }
            }
        }
        return opt[index];
    }
};


