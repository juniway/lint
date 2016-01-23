// [LeetCode 287] Find the Duplicate Number

// Given an array A containing n + 1 integers where each integer is between 1 and n (inclusive),
// prove that at least one duplicate number must exist. Assume that there is only one duplicate number,
// find the duplicate one.

// Note:
// You must not modify the array (assume the array is read only).
// You must use only constant, O(1) extra space.
// Your runtime complexity should be less than O(n2).
// There is only one duplicate number in the array, but it could be repeated more than once.

// http://www.cnblogs.com/grandyang/p/4843654.html

// 分析：
// 这道题给了我们n+1个数，所有的数都在[1, n]区域内，首先让我们证明必定会有一个重复数，
// 这不禁让我想起了小学华罗庚奥数中的抽屉原理(又叫鸽巢原理), 即如果有十个苹果放到九个抽屉里，
// 如果苹果全在抽屉里，则至少有一个抽屉里有两个苹果，这里就不证明了，直接来做题吧。

// 题目要求我们不能改变原数组，即不能给原数组排序，又不能用多余空间，那么哈希表神马的也就不用考虑了，
// 又说时间小于O(n^2)，也就不能用brute force的方法，那我们也就只能考虑用二分搜索法了，
// 我们在区间[1, n]中搜索，首先求出中点mid，然后遍历整个数组，统计所有小于等于mid的数的个数，
// 如果个数大于mid，则说明重复值在[mid+1, n]之间，反之，重复值应在[1, mid-1]之间，
// 然后依次类推，直到搜索完成，此时的low就是我们要求的重复值，


// Diffyculty: Hard

class Solution {
public:
    int findDuplicate(vector<int>& A) {
    	int n = A.size();
        int low = 1, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int cnt = 0;
            for (auto i : A) { // count the number of element that are smaller than mid
                if (i <= mid) ++cnt;
            }
            if (cnt <= mid) low = mid + 1;
            else high = mid - 1;
        }
        return low;
    }
};

这题想清楚了就不难，想不清楚就麻烦。

假设数组A长度是n, 里面存储1到n的整数，那么很清楚，我们可以在按照A[i] = i+1，进行排序。
但是现在有n+1个整数，而且至少有一个数字存在冗余。
如果我们仍然按照A[i] = i+1来排序数组的话，那么当发现A[i]上已经是i+1的值时，说明我们已经找到了冗余数了。

举个例子，
i
3    1    2    1   ----->   2    1    3    1    ----->    1    2    3    1    ---->
A[0] != 1                    still A[0] != 1              now A[0] == 1
swap(A[0], A[A[0]])         swap(A[0], A[A[0]])           move to next

1    2    3    1   ----->   1    2    3    1    ----->    1    2    3    1
A[1] == 2                    A[2] == 3                     A[3] != 4, need to swap(A[3], A[A[3]])
move to next                 move to next                  but A[A[3]] alread has right value, so A[3] is the duplicate number

简单的说，就是遍历数组的同时，某个元素应该放在这个元素值所在的坐标上去，
也即按照A[i]应该放到A[A[i]]原则，进行swap，第一个无法swap的数字就是所求。

class Solution {
public:
    int findDuplicate(vector<int>& A) {
        int length = A.size();
        for(int i = 0; i< length; i++) {
            if(A[i] != i + 1){
                int oldIndex = i;
                int newIndex = A[i] - 1; // newIndex 表示将要放到这个位置上去
                while(A[oldIndex] != oldIndex + 1 ) {
                    if(A[newIndex] == A[oldIndex]) return A[oldIndex];
                    swap(A[newIndex], A[oldIndex]);
                    newIndex = A[oldIndex] -1;
                }
            }
        }
    }
};


// class Solution {
// public:
//     int findDuplicate(const vector<int>& A) {
//         int n = A.size();
//         int result = 0;
//         for(int i = 0; i < n; ++i){
//             result ^= A[i];
//         }
//         for(int i = 1; i < n; ++i){
//             result ^= i;
//         }
//         return result;
//     }
// };