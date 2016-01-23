

class Solution {
private:
    vector < vector<int>> ans;
    vector<vector<int>> kSum(vector<int>& nums, int K, int target,int startPosition){
        unordered_set<int> visited;
        vector<vector<int>> tempVector;
        if (K==2)
        {
            vector<int> temp;
            int i = startPosition, j = nums.size() - 1;
            while (i<j)
            {
                if (nums[i]+nums[j]==target)
                {
                    if (visited.find(nums[i])==visited.end())
                    {
                        visited.insert(nums[i]);
                        temp.push_back(nums[i]);
                        temp.push_back(nums[j]);
                        tempVector.push_back(temp);
                        temp.clear();
                    }
                    i++;
                    j--;
                }
                else if (nums[i] + nums[j] < target)
                {
                    i++;
                }
                else{
                    j--;
                }
            }
            return tempVector;
        }
        else
        {
            for (size_t i = startPosition; i <= nums.size()-K; i++)
            {
                if (visited.find(nums[i])==visited.end())
                {
                    visited.insert(nums[i]);
                    vector<vector<int>>temp=kSum(nums, K - 1, target - nums[i], i + 1);
                    for (auto& vec : temp)
                    {
                        vec.insert(vec.begin(), nums[i]);
                        tempVector.push_back(vec);
                    }
                }
            }
            return tempVector;
        }
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size()<3)
        {
            return ans;
        }
        std::sort(nums.begin(), nums.end());
        ans = kSum(nums, 3, 0, 0);
        return ans;
    }
};