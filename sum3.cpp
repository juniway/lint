class Solution{
public:
    vector<vector<int>> threeSum(vector<int> &nums){
        const int n = nums.size();
        if(n < 3) return {};
        sort(nums.begin(), nums.end());
        vector<vector<int>> triples;

        for(int i = 0; i < n;){
            int start = i + 1, end = n -1;
            while(start < end){
                int sum = nums[i] + nums[start] + nums[end];
                if(sum == 0){
                    triples.push_back({nums[i], nums[start], nums[end]});
                    ++start;
                    --end;
                }
                while(start < end)
            }
        }
    }
}
