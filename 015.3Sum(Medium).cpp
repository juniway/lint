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


class Solution {
public:
    vector<vector<int>> threeSum(vector<int> & nums){
        int n = nums.size();
        vector<vector<int>> triples;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 2; ++i){
            if(i > 0 && nums[i] == nums[i - 1]) continue;
            twoSum(nums, i + 1, 0 - nums[i], triples);
        }
        return triples;
    }

    // sorted array
    void twoSum(vector<int> &nums, int start, int target, vector<vector<int>> &res){
        int i = start, j = (int)nums.size() - 1;

        while(i < j){
            int sum = nums[i] + nums[j];
            if(sum == target) {
                res.push_back({nums[start - 1], nums[i], nums[j]});
                ++i;
                --j;
                while(nums[i] == nums[i - 1]) ++i;
                while(nums[j] == nums[j + 1]) --j;
            }
            else if(sum < target) ++i;
            else --j;
        }
    }

    // hash map
    // void twoSum(vector<int> &nums, int start, int target, vector<vector<int>> &res){
    //     unordered_map<int, int> hash;
    //     for(int i = start + 1; i < nums.size(); ++i){
    //         int val = target - nums[i];
    //         if(hash.find(val) != hash.end()){
    //             res.push_back({nums[start], nums[i], val});
    //         }
    //         hash[val] = i;
    //     }
    // }
};



// Use two pointers
// Runtime: 53 ms
class Solution {
public:
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

// Runtime: 57 ms
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
            if (sum <= 0) while (nums[j] == b && j < k) j++; // skip duplicate
            if (sum >= 0) while (nums[k] == c && j < k) k--; // skip duplicate
        }
        while (nums[i] == a && i < last) i++; // skip duplicate
    }
    return triples;
}




