[LeetCode 121] Best Time to Buy and Sell Stock III

Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction
(ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.


这道题求进行一次交易能得到的最大利润。
如果用brute force的解法就是对每组交易都看一下利润，取其中最大的，总用有n*(n-1)/2个可能交易，所以复杂度是O(n^2)。
其实这是一道动态规划的题目，跟Maximum Subarray非常类似，用“局部最优和全局最优解法”。
思路是维护两个变量，一个是到目前为止最好的交易，另一个是在当天卖出的最佳交易（也就是局部最优）。
递推式是：
local[i+1] = max(local[i] + prices[i+1] - price[i], 0),
global[i+1] = max(local[i+1],global[i])。
这样一次扫描就可以得到结果，时间复杂度是O(n)。而空间只需要两个变量，即O(1)。
代码如下：
public int maxProfit(int[] prices) {
    if(prices==null || prices.length==0)
        return 0;
    int local = 0;
    int global = 0;
    for(int i=0;i<prices.length-1;i++)
    {
        local = Math.max(local+prices[i+1]-prices[i],0);
        global = Math.max(local, global);
    }
    return global;
}


思路相同, 每次更新当前的minprice, 找到遍历到当天时所有价格的最低价，然后更新全局最大利润
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int maxpro = 0;
        int minprice = std::numeric_limits<int>::max();

        for(int i = 0; i < prices.size(); ++i){
            if(prices[i] <= minprice) minprice = prices[i];
            else{
                maxpro = max(maxpro, prices[i] - minprice);
            }
        }

        return maxpro;
    }
};

这种题目的解法非常经典，不过是比较简单的动态规划。这道题目还有两个变体，
Best Time to Buy and Sell Stock II和Best Time to Buy and Sell Stock III，
虽然题目要求比较像，但是思路却变化比较大，Best Time to Buy and Sell Stock II可以交易无穷多次，思路还是比较不一样，
而Best Time to Buy and Sell Stock III则限定这道题交易两次，其实还可以general到限定交易k次