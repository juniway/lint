// Problem : Longest Increasing subsequence

/*

The Longest Increasing Subsequence problem is to find the longest increasing subsequence 
of a given sequence. Given a sequence S= {a1 , a2 , a3, a4, ............., an-1, an } 
we have to find a longest subset such that for all j and i,  j < i in the subset a[j] < a[i].
First of all we have to find the value of the longest subsequences(LS[i]) at every index i 
with last element of sequence being a[i]. Then largest LS[i] would be the longest subsequence 

in the given sequence. To begin, LS[i] is assigned to be one since a[i] is an element of the sequence(Last element). 
Then for all j such that j<i and a[j] < a[i] ,we find Largest LS[j] and add it to LS[i]. 
Then algorithm take O(n^2) time.

Pseudo-code for finding the length of the longest increasing subsequence:
This algorithms complexity could be reduced by using better data structure rather than array. 
Storing predecessor array and variable like largest_sequences_so_far and its index would save a lot time.
Similar concept could be applied in finding longest path in Directed acyclic graph.

注：
(1) 不要求递增子序列的元素是连续的
(2) LS[i] 表示以第i个元素为结尾的最长递增子序列
*/

/*
分析:
(1) 第一种算法：转化为LCS问题求解

设序列X=<b1,b2,…,bn>是对序列L=<a1,a2,…,an>按递增排好序的序列。
那么显然X与L的最长公共子序列即为L的最长递增子序列。这样就把求最长递增子序列的问题转化为求最长公共子序列问题LCS了。

(2)    第二种算法：动态规划法

设f(i)表示L中以ai为末元素的最长递增子序列的长度。则有如下的递推方程：
这个递推方程的意思是，在求以ai为末元素的最长递增子序列时，找到所有序号在L前面且小于ai的元素aj，即j<i且aj<ai。
如果这样的元素存在，那么对所有aj,都有一个以aj为末元素的最长递增子序列的长度f(j)，把其中最大的f(j)选出来，
那么f(i)就等于最大的f(j)加上1，即以ai为末元素的最长递增子序列，
等于以使f(j)最大的那个aj为末元素的递增子序列最末再加上ai；如果这样的元素不存在，
那么ai自身构成一个长度为1的以ai为末元素的递增子序列。
*/

 

#include <iostream>
#include <vector>
 
using namespace std;

int LIS(const vector<int>& a){
	int n = a.size();
	vector<int> LS(n, 1);

	// Compute optimized LIS values in bottom up manner 
	for(int i = 1; i <= n - 1; ++i){
        for(int j = 0; j <= i - 1; ++j){
            if (a[i] > a[j] && LS[i] < LS[j] + 1)
                LS[i] = LS[j] + 1;
        }
	}


	// return maximum of all LIS values 
	int largest = -1;
	for(int i = 1; i <= n - 1; ++i){
		if (largest < LS[i])
            largest = LS[i];
	}
	return largest;
}

int main(){
	vector<int> vec = {1, 9, 3, 8, 11, 4, 5, 6, 4, 1, 9, 7, 1, 7};
	cout << "LIS:" << LIS(vec) << endl;
}



// http://www.cnblogs.com/lonelycatcher/archive/2011/07/28/2119123.html
2. 对第二种算法的改进
在第二种算法中，在计算每一个f(i)时，都要找出最大的f(j)(j<i)来，由于f(j)没有顺序，
只能顺序查找满足aj<ai最大的f(j)，如果能将让f(j)有序，就可以使用二分查找，这样算法的时间复杂度就可能降到O(nlogn)。
于是想到用一个数组B来存储“子序列的”最大递增子序列的最末元素，
即有 B[f(j)] = aj
在计算f(i)时，在数组B中用二分查找法找到满足j<i且B[f(j)]=aj<ai的最大的j,并将B[f[j]+1]置为ai。
下面先写出代码，再证明算法的证明性。实现的代码如下：
void LIS_improve(vector<int> a)
{
    int n = a.size();
	vector<int> LS(n, 1);

    vector<int> B(a);
    B[0] = -1;			// 把B[0]设为最小，假设任何输入都大于-10000；
    B[LS[0]] = a[0];	// 初始时，最大递增子序列长度为1的最末元素为a1
    int p, r, mid;		// p, r, mid 分别为二分查找的上界，下界和中点:
    for(int i = 1; i < n; i++)
    {
        p = 0;
        r = LS[i - 1];
        while(p <= r)		// 二分查找最末元素小于ai+1的长度最大的最大递增子序列；
        {
           mid = (p + r)/2;
           if(B[mid] < L[i])
           		p = mid + 1;
           else r = mid - 1;
        }
        B[p] = L[i];		// 将长度为p的最大递增子序列的当前最末元素置为ai+1;
        if(p > LS[i]) LS[i]++;	// 更新当前最大递增子序列长度；
       
       
    }
    System.out.println(curLIS);
}
