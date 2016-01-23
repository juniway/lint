/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.

Have you met this question in a real interview? Yes
Example
For example, given array S = {-1 0 1 2 -1 -4}, A solution set is:

(-1, 0, 1)
(-1, -1, 2)
Note
Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)

The solution set must not contain duplicate triplets.

*/

// Time Complexity:
// O(nlogn + n^2) = O(n^2);

// Use two pointers 

class Solution {
public:    
    /**
     * @param numbers : Give an array numbers of n integer
     * @return : Find all unique triplets in the array which gives the sum of zero.
     */
    vector<vector<int> > threeSum(vector<int> &nums) {
        // write your code here
        const int n = nums.size();
        if(n < 3) return {};
        
        sort(nums.begin(), nums.end());
        
        vector<vector<int>> triples;
        for(int i = 0; i < n; ){
            int start = i + 1, end = n - 1;
            
            while(start < end){
            	int sum = nums[i] + nums[start] + nums[end];
                if(sum == 0){
                    triples.push_back({nums[i], nums[start], nums[end]});
                    start++;
                    end--;
                    while(start < end && nums[start] == nums[start - 1])
                        start++;
                    while(start < end && nums[end] == nums[end + 1])
                        end--;
                }
                else if(sum < 0){
                    ++start;
                    while(start < end && nums[start] == nums[start - 1])
                        ++start;
                }
                else if(sum > 0){
                    --end;
                    while(start < end && nums[end] == nums[end + 1])
                        --end;
                }
            }
            ++i;
            while(i < n && nums[i] == nums[i - 1])
                ++i;
            
        }
        return triples;
    }
};


vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> triples;
    sort(nums.begin(), nums.end());
    int i = 0, last = n - 1;
    while (i < last) {
        int a = nums[i], j = i+1, k = last;
        while (j < k) {
            int b = nums[j], c = nums[k], sum = a+b+c;
            if (sum == 0) triples.push_back({a, b, c});
            if (sum <= 0) while (nums[j] == b && j < k) j++;
            if (sum >= 0) while (nums[k] == c && j < k) k--;
        }
        while (nums[i] == a && i < last) i++;
    }
    return triples;
}

