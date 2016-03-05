[LeetCode 35] Search Insert Position
Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1, 3, 5, 6], 5 → 2
[1, 3, 5, 6], 2 → 1
[1, 3, 5, 6], 7 → 4
[1, 3, 5, 6], 0 → 0

Difficulty: Medium

思路：

Binary search的变种。如果target存在于数组中，则binary search就能找到。关键在于target不在数组中，当binary search结束时：start > end时，究竟应该如何获得插入位置。这里考察的是对base case的分析。定义insertion index为p，两种base case情况：

1. start = end = mid：
a. target < A[mid]，则我们知道p = mid。
binary search下一步会搜索A[start = mid : end = mid-1]而终止，在这一步应该返回start。
b. 反之target > A[mid]，则我们知道p = mid+1。
binary search下一步会搜索A[start = mid+1 : end = mid]而终止，这一步我们仍旧应该返回start。

2. start = end-1 = mid：
a. target < A[mid]，则我们知道p = mid。
同1a情况，查找结束start > end时，返回start
b. target > A[mid]，则我们知道p = mid+1或mid+2
binary search下一步会搜索A[start = mid+1 : end = mid+1]，即base case 1的情况。

综上所述，该问题的解法思路如下：
1. Binary search整个数组，如果在start <= end时找到了target，返回mid
2. 如果查找失败，即start > end，返回start即可。

class Solution {
public:
    int searchInsert(vector<int>& A, int target) {
    	int n = A.size();
        int start = 0, end = n-1;
        while(start <= end){
            int mid = start + (end-start)/2;
            if(target == A[mid]) 
                return mid;
            else if(target<A[mid])
                end = mid-1;
            else
                start = mid+1;
        }
        return start;
    }
};

或者：
跟经典的二分查找相比，只是多了一个条件：if(mid > left && A[mid]>target && A[mid-1]<target)
int searchInsert(vector<int>& A, int target) {  
	int l = 0, r = n-1;  
	while(l <= r){  
	int mid = (l + r) / 2;  
	if(A[mid] == target) return mid;  
	if(mid>l && A[mid] > target && A[mid - 1] < target ) return mid;
		if(A[mid] > target){
			r = mid-1;
		}
		else{
			l = mid + 1;
		}
	}  
	return l;
}

或者最简单，直接顺序遍历
class Solution {
public:
    int searchInsert(vector<int>& A, int target) {
        int n = A.size();
        for(int i = 0; i < n; i++){
            if(A[i] == target) return i;
            if(A[i] > target)
                return i;
        }
        return n;
        
    }
};