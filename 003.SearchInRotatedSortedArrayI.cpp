/*
[lintcode 3] Search in Rotated Sorted Array
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search.
If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.



Example
For [4, 5, 1, 2, 3] and target=1, return 2.
For [4, 5, 1, 2, 3] and target=0, return -1.

Challenge
O(logN) time

*/

// Analysis:
// compare the target with mid, first, last element of the array
// a rotated array can only have two forms:
// 1) A[first] < A[mid]: 4 5 6 7 0 1 2  or A[first] <= A[mid] 4 4 4 4 0 1 2
// 2) A[first] > A[mid]: 5 6 7 2 3 4 5  or A[first] >
// in both cases: target in [first, mid), mid, (mid, last]

// mid = (first + last) / 2
// when first == last, jump out the loop, return either first or last

class Solution{
public:
	int search(vector<int> &A, int target){
		int first = 0, last = A.size();
		while(first != last){
			const int mid = first + (last - first) / 2;
			if(A[mid] == target)
				return mid;
			if(A[first] <= A[mid]){
				if(A[first] <= target && target < A[mid])
					last = mid;
				else
					first = mid + 1;
			}
			else{
				if(A[mid] < target && target < A[last])
					first = mid + 1;
				else last = mid;
			}
		}
		return first;
	}
};

/*
[lintcode]
Follow up for "Search in Rotated Sorted Array II":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Write a function to determine if a given target is in the array.
*/

Analysis:
如果A[m] >= A[l],那么[l,m]为递增序列的假设就不能成立了，

如果A[m] >= A[l]不能确定递增，那就把它拆分成两个条件
1. A[m] > A[l]  递增
2. A[m] == A[l] 确定不了，那就l++，往下看一步即可。

class Solution
{
public:
	int search(vector<int> &A, int target){
		        // write your code here
        int start = 0;
		int end = A.size() - 1;

		// In this case: [2, 2, 2, 3, 1], target = 1;
		// start will iterate to the last element, which means start == end
		// and then target 1 will be found

		while(start <= end){
			const int mid = start + (end - start) /2;
			if(A[mid] == target) return true;

			if(A[start] < A[mid]){
				if(A[start] <= target && target < A[mid]){
					end = mid;
				}
				else{
					start = mid + 1;
				}
			}
			else if(A[start] > A[mid]){
				if(A[mid] < target && target <= A[end]){
					start = mid + 1;
				}
				else end = mid;
			}
			else
				start++;
		}
		return false;
	}
};

