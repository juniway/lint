// Leetcode 76
#include <iostream>
#include <vector>
#include <deque>

using std::vector;
using std::deque;
using std::cout;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> res;
    deque<int> dq;
    for (int i = 0; i < n; i++) {
        if (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(nums[dq.front()]);
    }
    return res;
}

vector<int> maxSlidingWindow1(vector<int>& nums, int k) {
    vector<int> ans;
    deque<int> dq;
    if(nums.empty()) return ans;
    for (int i = 0; i < k; i++) {
        while(!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
    }

    for (int i = k; i < nums.size(); i++) {
        ans.push_back(nums[dq.front()]);
        while(!dq.empty() && dq.front() < (i - k + 1)) dq.pop_front();
        while(!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
    }

    ans.push_back(nums[dq.front()]);
    return ans;
}

void testMaxSlidingWinMax() {
    vector<int> a{7, 2, 4};
    auto res = maxSlidingWindow1(a, 2);

    for (auto x: res) {
        cout << x << " ";
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    testMaxSlidingWinMax();
    return 0;
}
