// [LeetCode 64]  
// Problem:
// Max sum of sub array
// sub array is contiguous
// Dynamic programming

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int max_subsum(vector<int> A){
    int n = A.size();
    int endhere = A[0];
    int result = A[0];
    for(int i = 1; i < n; ++i){
        endhere = max(endhere + A[i], A[i]);
        result = max(result, endhere);
    }

    return result;
}


int max_subsum1(vector<int> arr, int &start, int &end) 
{
    int i , dp , max;
    int n = arr.size();

    dp = max = arr[n-1]; // dp is cursum, max is maxsum
    start = end = n-1;

    int temp = n-1;
    // end = n - 1;
    for(i = n - 2 ; i >= 0 ; --i)
    {
        if(dp > 0) dp += arr[i];
        else
        {
            dp = arr[i];    // 抛弃之前的子序列，从当前i开始重新向前搜索
            temp = i;       // 记录当前点(作为子数组结束点)，即i
        }
        if(dp > max)        // 更新最大子序列
        {
            max = dp;
            end = temp;
            start = i;      // 最大和增加，此时的i一定是最右端
        }
    }
    return max;
}

// 两个sum之差最大，就是这个连续子数组
int max_subsum2(vector<int> A){
    int n = A.size();
    int sum = A[0]; // 前N项的和
    int minSum = min(0, sum); // minSum记录前N项的和中最小的

    int answer = A[0];
    for(int i = 1; i < n; ++i){
        sum += A[i];
        answer = max(answer, sum - minSum);
        minSum = min(minSum, sum);
    }
    return answer;
}

// divide and conquer
int max_sub3(int A[], int n){
    if(n == 1)
        return A[0];

    int mid = n >> 1;

    int answer = max(max_sub3(A, mid), max_sub3(A + mid, n - mid));
    int now = A[mid - 1], may = now;
    for(int i = mid - 2; i >= 0; --i){
        may = max(may, now += A[i]);
    }
    now = may;
    for(int i = mid; i < n; ++i){
        may = max(may, now += A[i]);
    }

    return max(answer, may);
}


int main(){
    // int start = 0, end = 0;
    // int array[10] = {-5, -1, 2, 11, -3, -5, 4, 5, -8, 17};
     // vector<int> vec1 = {-5, -1, -3, -5, -8, -11, -18};

    // maxSum(vec1, start, end);
    // cout << "end = " << end << endl;

    // printf("max_sub: %d\n", max_subarr(vec1));
    // for(int i = start; i <= end; ++i){
    //     printf("%d ", vec1[i]);
    // }
    // printf("\n");
    
    vector<int> vec2 = {2, 3, -2, 4, -5, 7, -3};
    cout << "max product:" << maxprod1(vec2) << endl;
    // for(int i = start; i <= end; ++i){
    //     printf("%d ", vec1[i]);
    // }
    // printf("\n");
    return 0;
}
