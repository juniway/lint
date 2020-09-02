#include <iostream>
#include <vector>
using namespace std;

// return the size
int selectActivity(vector<vector<int>>& activities) {
    sort(begin(activities), end(activities), [](vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    });

    int n = activities.size();
    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (activities[j][1] <= activities[i][0]) {
                dp[i] = max(dp[i], dp[j]);
            }
        }
        dp[i]++;
    }

    return *max_element(dp.begin(), dp.end());
}

// return sequence
vector<vector<int>> selectActivity1(vector<vector<int>>& activities) {
    sort(begin(activities), end(activities), [](vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    });

    int n = activities.size();
    vector<vector<vector<int>>> dp(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (activities[j][1] <= activities[i][0] && dp[i].size() < dp[j].size()) {
                dp[i] = dp[j];
            }
        }
        dp[i].push_back(activities[i]);
    }

    vector<vector<int>> res;
    for (auto & sf : dp) {
        if (res.size() < sf.size())
            res = sf;
    }

    return res;
}

vector<vector<int>> selectActivity2(vector<vector<int>>& activities) {
    sort(begin(activities), end(activities), [](vector<int>& a, vector<int>& b) {
        // if (a[0] == b[0]) return a[1] > b[1];
        return a[0] < b[0];
    });

    int n = activities.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, INT_MAX));
    dp[0][0] = INT_MIN, dp[0][1] = INT_MIN;
    int lisLen = 0;
    for (int i = 0; i < n; i++) {
        int j = upper_bound(begin(dp), begin(dp) + lisLen + 1, vector<int>{activities[i][1], activities[i][0]}) - dp.begin();
        if (dp[j - 1][0] < activities[i][0] && dp[j - 1][0] < activities[i][1] && activities[i][1] < dp[j][0]) {
            // for (auto v : dp) cout << v[0] << ", " << v[1] << " "; cout << endl;
            // cout << "j: " << j << ", " << activities[i][1] << ": " << dp[j - 1] << ", " << dp[j] << endl;
            dp[j][0] = activities[i][1];
            dp[j][1] = activities[i][0];
            lisLen = max(lisLen, j);
        }
    }

    cout << "lisLen: " << lisLen << endl;

    vector<vector<int>> res;
    for (int i = 1; i <= n; i++) {
        if (dp[i][0] < INT_MAX)
            res.push_back({dp[i][1], dp[i][0]});
    }

    // cout << "res: " << res << endl;

    return res;
}

vector<vector<int>> selectActivity3(vector<vector<int>>& activities) {
    sort(begin(activities), end(activities), [](vector<int>& a, vector<int>& b) {
        // if (a[0] == b[0]) return a[1] > b[1];
        return a[0] < b[0];
    });
    // for (auto p : activities) cout << "{" << p[0] << ", " << p[1] << "}, "; cout << endl;

    int n = activities.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    int lisLen = 0;
    for (int i = 0; i < n; i++) {
        // cout << "want to find the lower obund of: " << "{" << activities[i][1] << ", " << activities[i][0] << "}" << endl;
        // for (auto it = dp.begin(); it != dp.begin() + lisLen + 1; it++) cout << (*it)[0] << " " << (*it)[1] << ", "; cout << endl;
        int j = lower_bound(begin(dp) + 1, begin(dp) + lisLen + 1, vector<int>{activities[i][1], activities[i][0]}) - dp.begin();
        // cout << "j: " << j << endl;
        if (dp[j - 1][0] < activities[i][0]) {
            dp[j][0] = activities[i][1];
            dp[j][1] = activities[i][0];
            lisLen = max(lisLen, j);
        }
        // for (auto v : dp) cout << v[0] << " " << v[1] << ", "; cout << endl;
    }

    cout << "lisLen: " << lisLen << endl;

    vector<vector<int>> res;
    for (int i = 1; i <= n; i++) {
        if (dp[i] != vector<int>{0, 0})
            res.push_back({dp[i][1], dp[i][0]});
    }

    // cout << "res: " << res << endl;

    return res;
}

void testSelectActivity() {
    vector<vector<int>> activities = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9},
        {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}
    };

    // for (auto p : activities) cout << "{" << p[0] << ", " << p[1] << "}, "; cout << endl;
    // cout << selectActivity(activities) << endl;
    // cout << selectActivity2(activities) << endl;
    auto res = selectActivity2(activities);
    for (auto p : res) cout << "{" << p[0] << ", " << p[1] << "}, ";
    cout << endl;

    auto res1 = selectActivity3(activities);
    for (auto p : res1) cout << "{" << p[0] << ", " << p[1] << "}, ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testSelectActivity();
    return 0;
}
