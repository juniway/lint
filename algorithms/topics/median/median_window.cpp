#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector<double> medianWindow(vector<int>& nums, int k) {
    vector<double> res;
    multiset<int> window(nums.begin(), nums.begin() + k);
    auto mid = next(window.begin(), k / 2);
    for (int i = k; ; i++) {
        res.push_back(((double)*mid + *prev(mid, 1 - window.size() % 2)) / 2);

        if (i == nums.size()) return res;
        // insert
        window.insert(nums[i]);
        if (nums[i] < *mid)
            mid--;
        // erase
        if (nums[i - k] <= *mid) {
            mid++;
        }
        window.erase(window.lower_bound(nums[i - k]));
    }
}
