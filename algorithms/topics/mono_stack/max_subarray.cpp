#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int maxSubarray(vector<int>& nums) {
    vector<int> sum; // prefix sum
    sum.push_back(0);
    nums.push_back(-1);

    for (int i = 0; i < nums.size() - 1; i++) {
        sum.push_back(sum[i] + nums[i]);
        cout << sum[i] << endl;
    }

    int ans = 0;
    stack<int> st;
    for (int i = 0; i <= nums.size(); i++) {
        while (!st.empty() && nums[i] < nums[st.top()]) {
            int cur = st.top(); st.pop();
            int si = st.empty() ? sum[i] : sum[i] - sum[st.top() + 1];
            ans = max(ans, si * nums[cur]);
        }
        st.push(i);
    }

    return ans;
}

void testMaxSubarray() {
    vector<int> nums = {4, 6, 2, 1};
    cout << maxSubarray(nums) << endl;
}

int main(int argc, char *argv[]) {
    testMaxSubarray();
    return 0;
}
