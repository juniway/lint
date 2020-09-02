#include <iostream>
#include <queue>
#include <iterator>
#include <vector>
using namespace std;

int lis(vector<int>& a, int i, int prevLen) {
    if (i == a.size()) return 0;
    int excl = lis(a, i + 1, prevLen);
    int incl = 0;
    if (a[i] > prevLen)
        incl = 1 + lis(a, i + 1, a[i]);
    return max(excl, incl);
}

// dp
int lis1(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 0);
    dp[0] = 1; // end with a[0] has length 1
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] > dp[i])
                dp[i] = dp[j];
        }
        dp[i]++;
    }

    return *max_element(begin(dp), end(dp));
}

// dp + result sequence
// O(N^2)
vector<int> lis2(vector<int>& a) {
    int n = a.size();
    vector<vector<int>> dp(n);
    dp[0].push_back(a[0]);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j].size() > dp[i].size())
                dp[i] = dp[j];
        }
        dp[i].push_back(a[i]);
    }

    vector<int> res;
    for (auto & p : dp) {
        if (res.size() < p.size())
            res = p;
    }

    return res;
}

// lower_bound
// O(nlogn)
int lis3(vector<int>& a) {
    vector<int> res;
    for (int i = 0; i < a.size(); i++) {
        auto it = lower_bound(res.begin(), res.end(), a[i]);
        if (it == res.end()) res.push_back(a[i]);
        else *it = a[i];
    }

    return res.size();
}

// note: d[i] where i represent the length of the sub sequence!
// therefore, base case d[i] = 0
// that's why we start from dp.begin() + 1 and dp(n + 1, 0)
vector<int> lis33(vector<int>& a) {
    vector<int> dp(a.size() + 1, 0);
    vector<int> f(a.size(), 0);
    int answer = 0;
    for (int i = 0; i < a.size(); i++) {
        f[i] = lower_bound(dp.begin() + 1, dp.begin() + answer + 1, a[i]) - dp.begin();
        // for (auto v : dp) cout << v << " "; cout << endl;
        cout << "j: " << f[i] << endl;
        answer = max(answer, f[i]);
        dp[f[i]] = a[i];
        for (auto v : dp) cout << v << " "; cout << endl;
    }

    // cout << "======= f[i] ==========\n";
    // for (int i = 0; i < f.size(); i++) {
    //     cout << f[i] << " > ";
    // }
    // cout << endl;

    vector<int> res;
    int require = answer;
    for (int i = a.size() - 1; i >= 0; i--) {
        if (f[i] == require) {
            res.push_back(a[i]);
            require--;
        }
    }

    reverse(begin(res), end(res));
    return res;
}

// upper_bound
// O(nlogn)
int lis4(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = INT_MIN;
    for (int i = 0; i < n; i++) {
        int j = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        if (dp[j - 1] < a[i] && a[i] < dp[j])
            dp[j] = a[i];
    }

    int res = 0;
    for (int i = 0; i <= n; i++) {
        if (dp[i] < INT_MAX)
            res = i;
    }

    return res;
}

vector<int> lis44(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = INT_MIN;
    for (int i = 0; i < n; i++) {
        int j = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        if (dp[j - 1] < a[i] && a[i] < dp[j])
            dp[j] = a[i];
    }

    vector<int> res;
    for (int i = 1; i <= n; i++) {
        if (dp[i] < INT_MAX)
            res.push_back(dp[i]);
    }

    return res;
}

// binary search
int lis5(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, INT_MAX);
    dp[0] = INT_MIN;

    int LisLength = 0;
    for (int i = 0; i < n; i++) {
        int low = 0, high = LisLength, mid;
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (dp[mid] < a[i])
                low = mid + 1;
            else high = mid - 1;
        }
        dp[low] = a[i];
        if (LisLength < low)
            LisLength = low;
    }

    return LisLength;
}

void testLis() {
    vector<vector<int>> a = {
        {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15},
        {1, 15, 1, 10, 13, 1, 1, 19, 8},
        {1, 2, 3, 4, 5},
    };

    for (auto & seq : a) {
        cout << lis4(seq) << endl;
        auto res = lis44(seq);
        for (int v : res) cout << v << " "; cout << endl;
        auto res1 = lis33(seq);
        for (int v : res1) cout << v << " "; cout << endl;
        cout << lis5(seq) << endl;
        cout << "\n";
    }
    // cout << lis(a, 0, INT_MIN) << endl;
    // cout << lis1(a) << endl;
    //
    // auto res = lis2(a);
    // for (auto v : res) cout << v << " "; cout << endl;
    //
    // cout << lis3(a) << endl;

    // auto res1 = lis33(a);
    // for (auto v : res1) cout << v << " "; cout << endl;
}

int main(int argc, char *argv[]) {
    testLis();
    return 0;
}
