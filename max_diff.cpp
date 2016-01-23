
/*
Problem:
数组中，数字减去它右边（不要求相邻）的数字得到一个数对之差。求所有数对之差的最大值。
例如：数组{2, 4, 1, 16, 7, 5, 11, 9}, 数对之差的最大值是11，是16-5的结果。

分析：
我们还可以动态的考虑这个问题，我们可以假想这个数组是不断地往一个已知数组的前面加一个数字组成的，
如果我们已经知道了已知数组的maxdiff，和已知数组的最小值，我们要怎么求解新数组的maxdiff呢，
对了，我们只要用新加入的这个数组减去已知的最小值和maxdiff比较，取其较大者，同时和已知的最小值比较，
取其较小者，更新最小值即可。

最初最初的问题是什么？只有一个数字！最小值是它本身，maxdiff = 0。
根据这种思路我们可以写出如下的简洁代码：
*/

#include <iostream>
#include <vector>
using namespace std;

int max_diff(vector<int> a){
	int n = a.size();
	if(n <= 0) return 0;

	int min = a[n - 1];
	int maxdif = 0;

	for(int i = n - 2; i >=0; --i){
		int dp = a[i] - min;
		if(maxdif < dp){
			maxdif = dp;
		}

		if(min > a[i])
			min = a[i];
	}

	return maxdif;
}


int main(){
	vector<int> vec = {2, 4, 1, 16, 7, 5, 11, 9};

	cout << max_diff(vec) << endl;
}

