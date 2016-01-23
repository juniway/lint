/*
[LeetCode 01] Two Sum
Given an array of integers, find two numbers such that they add up to a specific 
target number.

The function twoSum should return indices of the two numbers such that they 
add up to the target, where index1 must be less than index2. 
Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers = {2, 7, 11, 15}, target = 9
Output: index1 = 1, index2 = 2

Related:
[LeetCode 15] 3 Sum
[LeetCode 16] 3 Sum Closest
[LeetCode 18] 4 Sum
[LeetCode...] k Sum


*/
// http://www.lifeincode.net/programming/leetcode-two-sum-3-sum-3-sum-closest-and-4-sum-java/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Time:  O(n)
// Space: O(n)

// 1.
class Solution1{
public:
    /*
     * @param numbers : An array of Integer
     * @param target : target = numbers[index1] + numbers[index2]
     * @return : [index1+1, index2+1] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &A, int target) {
        unordered_map<int, int> hash;

        int n = A.size();
        for (int i = 0; i < n; ++i) {
            // Check if "target - nums[i]" exists or not
            int val = target - A[i];
            if (hash.find(val) != hash.end()) { // found
                return {hash[val] + 1, i + 1};
            }
            hash[A[i]] = i;
        }

        return {};
    }
};

// 2. 
class Solution2{
public:
    /*
     * @param numbers : An array of Integer
     * @param target : target = numbers[index1] + numbers[index2]
     * @return : [index1+1, index2+1] (index1 < index2)
     */
    vector<int> twoSum(vector<int> &A, int target) {
        // write your code here
        unordered_map<int, int> mapp;
        vector<int> result;
        for(int i = 0; i < (int)A.size(); ++i){
            mapp[A[i]] = i;
        }
        
        for(int i = 0; i < (int)A.size(); ++i){
            const int gap = target - A[i];
            if(mapp.find(gap) != mapp.end() && mapp[gap] > i){
                result.push_back(i + 1);
                result.push_back(mapp[gap] + 1);
                break;
            }
        }
        return result;
    }
};

// 3.
// sort the array first
// then use two indexer, i = 0, and j = n -1 
class Solution3 {
public:
    vector<int> twoSum(vector<int>& A, int target) {
        int n = A.size();
        vector<int> sortedArray(A);
        sort(begin(sortedArray), end(sortedArray));
        // int lb = lower_bound(sortedArray.begin(), sortedArray.end(), target) - sortedArray.begin();
        int lb = n - 1;
        int i = 0, j = n - 1;
        while(i < j && j >= 0 && j <= lb){
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

int main(){
	vector<int> vec = {1, 2, 3, 3};
	Solution2 s;
	auto result = s.twoSum(vec, 6);

	for(auto& i: result){
		cout << i << " ";
	}
	cout << endl;

}
