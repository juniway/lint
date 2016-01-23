[LeetCode 11] Container With Most Water

Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai).
n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0).
Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container.

Difficulty: medium
Related Problems: [LeetCode 42]Trapping Rain Water


算法1：时间复杂度O（n），两个指针i, j分别从前后向中间移动，两个指针分别表示容器的左右边界。
每次迭代用当前的容量更新最大容量，然后把高度小的边界对应的指针往中间移动一位。

正确性证明：由于水的容量是有较小的那个边界决定的，因此某次迭代中，假设height[i] < height[j]，
那么j 减小肯定不会使水的容量增大，只有i 增加才有可能使水的容量增大。
但是会不会有这种可能：当前的i 和 某个k (k > j)是最大容量, 这也是不可能的，
因为按照我们的移动规则，既然右指针从k 移动到了j，说明i 的左边一定存在一个边界 m，使m > k，
那么[m, k]的容量肯定大于[i, k]，所以[i,k]不可能是最大容量。
参考:https://leetcode.com/discuss/1074/anyone-who-has-a-o-n-algorithm
Any pairs of indexs which are wider than the current traversing pair, must be traversed before. Greedy!

class Solution {
public:
    int maxArea(vector<int> &height) {
        int n = (int)height.size(), area = 0;
        int i = 0, j = n - 1;
        while(i < j){
            area = max(area, (j - i) * min(height[i], height[j]));
            if(height[i] < height[j]) ++i;
            else --j;
        }
        return area;
    }
};

算法2：
时间复杂度O（nlogn）。
构建结构体包含height和height在原数组中的位置
struct Node{
    int height;
    int index;
};

对该结构体数组按照height的值递增排序，假设排序后的数组为vec.
假设f[i] 表示数组vec[i,i+1,…]内所有height按照原来的位置顺序排列好以后的最大水量
那么f[i-1]可以在O（1）时间内计算出来：因为vec[i-1].height 小于vec[i,i+1,…]内的所有height，
所以以vec[i-1].index为边界的容器高度为vec[i-1].height，最大水量只需要分别计算vec[i,i+1,…]内
按原始位置排列最前面和最后面的height，取两者的较大值。即下图中，黑色是最低的，
要计算以黑色为边界的容器的最大水量，只需要分别和第一个和最后一个计算，去两者较大值

class Solution {
    struct Node{
        int height;
        int index;
        Node(int h, int i):height(h),index(i){}
        Node(){}
        bool operator < (const Node &a)const{
            return height < a.height;
        }
    };
public:
    int maxArea(vector<int> &height) {
        int res = 0, n = height.size();
        if(n <= 1)return 0;
        vector<Node>vec(n);
        for(int i = 0; i < n; i++){
            vec[i].index = i;
            vec[i].height = height[i];
        }
        sort(vec.begin(), vec.end());

        int start = vec[n-1].index, end = start;//记录已经处理完的height的原始位置的左右端点
        for(int i = n-2; i >= 0 ; i--){
            start = min(start, vec[i].index);
            end = max(end, vec[i].index);
            res = max(res, max(vec[i].height*(vec[i].index - start), vec[i].height*(end - vec[i].index)));
        }
        return res;
    }
};