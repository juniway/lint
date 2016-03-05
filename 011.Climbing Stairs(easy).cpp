/*
Climbing Stairs

39% Accepted
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Have you met this question in a real interview? Yes
Example
Given an example n=3 , 1+1+1=2+1=1+2=3

return 3
*/

Analysis:

设 f(n) 表示爬 n 阶楼梯的不同方法数，为了爬到第 n 阶楼梯，有两个选择： 
• 从第 n - 1 阶前进 1 步；
• 从第 n - 2 阶前进 2 步； 
因此，有 f(n) = f(n - 1) + f(n - 2)。

这是一个斐波那契数列。方法 1，递归，太慢；方法 2，迭代。
方法 3，数学公式。斐波那契数列的通项公式为 An = 1 / sqrt(5)[((1 + sqrt(5) / 2)^n -((1 - sqrt(5) / 2)^n]


// Time: O(n), Space: O(1)

class Solution {
public:
	int climbStairs(int n) {
		int prev = 0;
		int cur = 1;
		for(int i = 1; i <= n ; ++i){
			int tmp = cur; 
			cur += prev; 
			prev = tmp;
		}
		return cur;
	}
};

