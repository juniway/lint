#### [LeetCode 01] Two Sum
>Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,
Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
UPDATE (2016/2/13):
The return format had been changed to zero-based indices. Please read the above updated description carefully.
http://www.lifeincode.net/programming/leetcode-two-sum-3-sum-3-sum-closest-and-4-sum-java/



**Analysis**
Condition:
 1. We should take no assumption that the input array is in order.
 2. The returned indexes should be in order.

Idea:
Loop the array and use a helper data struct (e.g. map) to record the visited elements (and its index in original array).
When we are looping, we continuously query the map to find our target element.

// Time:  O(n)
// Space: O(n)

// 1. unordered map, sort isn't need

```c++
// <k, v> pair is <val, index>
class Solution1{
public:
    /*
     * target = numbers[index1] + numbers[index2]
     * @return : [index1+1, index2+1] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &A, int target) {
        unordered_map<int, int> hash;
        int n = A.size();
        for (int i = 0; i < n; ++i) {
            int val = target - A[i];
            if (hash.find(val) != hash.end()) { // found
                return {hash[val] + 1, i + 1};
            }
            hash[A[i]] = i; // not found, store the visited element
        }

        return {};
    }
};
```

// 2. sort the array first
// Use two indexers, i = 0, and j = n -1

```c++
class Solution2 {
public:
    vector<int> twoSum(vector<int>& A, int target) {
        int n = A.size();
        vector<int> sortedArray(A);
        sort(begin(sortedArray), end(sortedArray));
        // int lb = lower_bound(sortedArray.begin(), sortedArray.end(), target) - sortedArray.begin();
        int i = 0, j = n - 1;
        while(i < j && j >= 0 && j <= n - 1){ // j <= lowerbound
            int sum = sortedArray[i] + sortedArray[j];
            if(sum == target){
                break;
            }
            else if(sum > target){
                j--;
            }
            else{
                i++;
            }
        }

        vector<int> indices;
        for(int s = 0; s <= n - 1; ++s){
            if(A[s] == sortedArray[i]){
                indices.push_back(s+1);
            }
            else if(A[s] == sortedArray[j]){
                indices.push_back(s+1);
            }
        }
        return indices;
    }
};
```

// 3. Golang solution

```go
func twoSum(nums []int, target int) []int {
    visited := make(map[int]int) // <element, index>
    res := make([]int, 2)
    for i, v := range nums {
        rem := target - v
        if idx, ok := visited[rem]; ok {
            res[0], res[1] = idx, i
            if idx > i {
                res[0], res[1] = i, idx
            }
            // sort.Ints(res)
            return res
        } else {
            visited[v] = i
        }
    }
    return res
}
```

**Simple driver Program:**

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main(){
    vector<int> vec = {1, 2, 3, 3};
    Solution2 s;
    auto result = s.twoSum(vec, 6);

    for(auto& i: result){
        cout << i << " ";
    }
    cout << endl;
}
```
