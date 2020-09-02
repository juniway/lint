#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int minDiff(vector<int>& a) {
    int sum = accumulate(a.begin(), a.end(), 0);

    vector<bool> dp(sum/2 + 1, false);
    dp[0] = true;

    int s = 0;
    for(auto v : a) {
        s += v;
        for (int j = min(sum/2 + 1, s); j >= v; j--) {
            dp[j] = dp[j] + dp[j - v];
        }
    }

    int diff = -1;
    for (int i = sum/2; i >= a[0]; i--) {
        if (dp[i]) {
            diff = sum - 2 * i;
            break;
        }
    }

    return diff;
}

void testMinDiff() {
    vector<int> a {1, 5, 3, 2};
    cout << minDiff(a) << endl;
}

int main(int argc, char *argv[]) {
    testMinDiff();
    return 0;
}
