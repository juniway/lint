/*
Trapping Rain Water Show result 

32% Accepted
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

Trapping Rain Water

Have you met this question in a real interview? Yes
Example
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

Challenge
O(n) time and O(1) memory

O(n) time and O(n) memory is also acceptable.

*/

Analysis:
对于每个柱子，找到其左右两边最高的柱子，该柱子能容纳的面积就是 min(max_left, max_right) - height。所以，
1. 从左往右扫描一遍，对于每个柱子，求取左边最大值； 
2. 从右往左扫描一遍，对于每个柱子，求最大右值；
3. 再扫描一遍，把每个柱子的面积合并累加。

也可以，
1. 扫描一遍，找到最高的柱子，这个柱子将数组分为两半； 
2. 处理左边一半；3. 处理右边一半。


class Solution {
public:
    /**
     * @param heights: a vector of integers
     * @return: a integer
     */
    int trapRainWater(vector<int> &heights) {
        // write your code here
        const int n = heights.size();
        auto max_left = vector<int>(n, 0);
        auto max_right = vector<int>(n, 0);
        
        for(int i = 1; i < n; ++i){
            max_left[i] = max(max_left[i - 1], heights[i - 1]); // dp
            max_right[n - 1 - i] = max(max_right[n - i], heights[n - i]);
        }
        
        int sum = 0;
        
        //左边最高的和右边最高的，取两者之间最小的
        for(int i = 0; i < n; ++i){
            int height = min(max_left[i], max_right[i]);
            if(height > heights[i])
                sum += height - heights[i];
        }
        return sum;
        
    }
};
