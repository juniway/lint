
/*
[LeetCode] 4Sum
Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
Note:
Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d)
The solution set must not contain duplicate quadruplets.
    For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

    A solution set is:
    (-1,  0, 0, 1)
    (-2, -1, 1, 2)
    (-2,  0, 0, 2)

*/

/*
Analysis:
既然已经做了2sum, 3sum, 3sum closest。自然能推广到4sum。但这里希望能推广到更普遍的k-sum问题。这里使用递归的思路：

1. k-sum问题可以转化为(k-1)-sum问题：对于数组中每个数A[i]，在A[i+1:n-1]中寻找target-A[i]的(k-1)-sum问题。
2. 直到k=2时，用2sum的双指针扫描来完成。

去重复解的技巧和3Sum问题一模一样。

http://bangbingsyb.blogspot.com/2014/11/leetcode-4sum.html
*/

// 递归求 kSum()
// Runtime: 80 ms
class Solution{
public:
	vector<vector<int>> fourSum(vector<int> &num, int target){
		vector<vector<int>> allSol;
		vector<int> sol;
		sort(num.begin(), num.end());
		kSum(num, 0, num.size() - 1, target, 4, sol, allSol);
		return allSol;
	}

	void kSum(vector<int> &num, int start, int end, int target, int k, vector<int> &sol, vector<vector<int>> &allSol){
		if(k <= 0) return;
		if(k == 1){
			for(int i = start; i <= end; ++i){
				if(num[i] == target){
					sol.push_back(num[i]);
					allSol.push_back(sol);
					sol.pop_back();
					return;
				}
			}
		}

		if(k == 2){
			twoSum(num, start, end, target, sol, allSol);
			return;
		}

		for(int i = start; i <= end - k + 1; ++i){
			if(i > start && num[i] == num[i - 1])
				continue;
			sol.push_back(num[i]);
			kSum(num, i + 1, end, target - num[i], k - 1, sol, allSol);
			sol.pop_back();
		}
	}

	void twoSum(vector<int> &num, int start, int end, int target, vector<int> &sol,	vector<vector<int>> &allSol){
		while(start < end){
			int sum = num[start] + num[end];
			if(sum == target){
				sol.push_back(num[start]);
				sol.push_back(num[end]);
				allSol.push_back(sol);
				sol.pop_back();
				sol.pop_back();
				start++;
				end--;
				while(num[start] == num[start - 1]) start++;
				while(num[end] == num[end + 1]) end--;
			}
			else if(sum < target) start++;
			else end--;
		}
	}
};


// 循环展开 4sum
// Runtime: 72 ms

class Solution {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        vector<vector<int>> tetrads;
        if(nums.size() < 4) return tetrads;
        sort(nums.begin(), nums.end());

        for(int i = 0; i < (int)nums.size() - 3; ++i){
            if(i > 0 && nums[i] == nums[i - 1]) continue;
            for(int j = i + 1; j < (int)nums.size() - 2; ++j){
                if(j > 1 && i != j - 1 && nums[j] == nums[j - 1]) continue;
                twoSum(nums, i, j + 1, target - nums[i] - nums[j], tetrads);
            }
        }
        return tetrads;
    }

    void twoSum(vector<int> &nums, int start0, int start1, int target, vector<vector<int>> &tetrads){
        int i = start1, j = (int)nums.size() - 1;
        while(i < j){
            int sum = nums[i] + nums[j];
            if(sum == target){
                tetrads.push_back({nums[start0], nums[start1 - 1], nums[i], nums[j]});
                ++i; --j;
                while(nums[i] == nums[i - 1]) ++i;
                while(nums[j] == nums[j + 1]) --j;
            }
            else if(sum < target) ++i;
            else --j;
        }
    }
};
