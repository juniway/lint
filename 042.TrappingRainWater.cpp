[LeetCode 42] Trapping Rain Water
Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it is able to trap after raining.

For example,
Given [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1], return 6.

^
|
|                        __
|            __         |  |__    __
|   __    __|  |__    __|  |  |__|  |__
|__|__|__|__|__|__|__|_________________|

思路1:
对于每个柱子，分别找到其两边最高的柱子，该柱子能容纳的面积就是min(maxLeft, maxRigth) - height
所以，1) 从左往右扫描一遍，对于每个柱子，求取左边最大值 2) 从右往左再扫描一遍，求出每个柱子右边最大值
3)再扫描一遍，把每个柱子的面积合并累加
也可以：扫描一遍，找到最高柱子，这个柱子把数组分位两半，分别处理左边一半，和右边一半(分治)

算法1：
Time:O(n) Space:O(n)

class Solution{
public:
	int trapRainWater(const vector<int> &heights){
		const int n = heights.size();
		vector<int> max_left(n, 0);
		vector<int> max_right(n, 0);

		for(int i = 1; i < n; ++i){
			max_left[i] = max(max_left[i - 1], heights[i - 1]);
			max_right[n - 1 - i] = max(max_right[n - i], heights[n - i]);
		}
		int sum = 0;
		for(int i = 0; i < n; ++i){
			int height = min(max_left[i], max_right[i]);
			if(height > heights[i]){
				sum += height - heights[i];
			}
		}

		return sum;
	}
};

算法2:
Time: O(n) Space: O(1)
class Solution{
public:
	int trapRainWater(const vector<int> &heights){
		const int n = heights.size();
		int maxi = 0; // the highest height, separate the array into to two part
		for(int i = 0; i < n; ++i){
			if(heights[maxi] < heights[i]) maxi = i;
		}
		int water = 0;
		for(int i = 0, peak = 0; i < maxi; ++i){
			if(heights[i] > peak) peak = heights[i];
			else water += peak - heights[i];
		}
		for(int i = n - 1; peak = 0; i > maxi; --i){
			if(heights[i] > peak) peak = heights[i];
			else water += peak - heights[i];
		}
		return water;
	}
};

算法3:
用一个辅助栈，小与栈顶的元素压入，大于等于栈顶的就把栈里所有小于或等于当前值的元素全部出栈
Time: O(n) Space: O(n)

class Solution{
public:
	trap(const vector<int> &heights){
		const int n = heights.size();
		stack<pair<int, int>> s;
		int water = 0;
		for(int i = 0; i < n; ++i){
			int height = 0;
			while(!s.empty()){ // 将栈中比当前元素矮或等于的元素全部处理掉
				int bar = s.top().first;
				int pos = s.top().second;

				// bar, height, a[i] 三者夹成的凹陷
				water += (min(bar, heights[i] - height)) * (i - pos - 1);
				height = bar;

				if(heights[i] < bar) // 遇到了比当前元素高的，跳出循环
					break;
				else s.pop() // 弹出栈顶，因为该元素处理完了，不再需要了
			}
			s.push(make_pair(heights[i], i));
		}
		return water;
	}
}