#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::max;
using std::min;
using std::cout;

// recursion
int knapsack(vector<int>& v, vector<int>& w, int V, int n) {
    if (n == 0 || V == 0) return 0;

    if (v[n - 1] > V) return knapsack(v, w, V, n - 1);
    return max(w[n-1] + knapsack(v, w, V - v[n - 1], n - 1), knapsack(v, w, V, n - 1));
}

// memoization
int knapsack(vector<int>& v, vector<int>& w, int V, int n, vector<int>& memo) {
    if (memo[n] < 0) {
        if (n == 0 || V == 0) return 0;
        if (v[n - 1] > V) memo[n] = knapsack(v, w, V, n- 1);
        else
        memo[n] = max(w[n-1] + knapsack(v, w, V - v[n - 1], n - 1), knapsack(v, w, V, n - 1));
    }

    return memo[n];
}


// O(N*W)
// v : value, w : weight
// dp[i][j] (j <= W) represents the max value can get at ith item, for capacity j
// the 1st item is meaningless
int knapsackW(vector<int>& w, vector<int>& v, int W) {
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j <= W; j++) {
            if (w[i] <= j)
                dp[i+1][j] = max(dp[i][j], dp[i][j-w[i]] + v[i]);
            else dp[i + 1][j] = dp[i][j];
        }
    }
    return dp[n][W];
}

int knapsackW1(vector<int>& w, vector<int>& v, int W) {
    int n = w.size();
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0) dp[i][j] = 0;
            else if (w[i - 1] <= j)
                dp[i][j] = max(dp[i - 1][j], dp[i][j - w[i - 1]] + v[i - 1]);
            else dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][W];
}

// O(N*V)
// dp on value
// m[i][j] (j <= V) represent when we get max value j at ith item, the min weight required.
int knapsackV(vector<int>& w, vector<int>& v, int W) {
    int V = 0;
    for (auto x:v) {
        V += x;
    }
    vector<vector<int>> m(v.size() + 1, vector<int>(V+1, 1000));
    for (int j = 0; j <= w.size(); j++) {
        m[j][0] = 0;
    }
    for (int i = 0; i < v.size(); i++) {
        for (int j = V; j >= v[i]; j--) {
            m[i+1][j] = min(m[i][j], m[i][j-v[i]] + w[i]);
        }
    }

    for (int j = V; j >= 0; j--) {
        if(m[v.size()][j] <= W)
            return j;
    }
    return 0;
}

// tab
int knapsack(vector<int>& v, vector<int>& w, int V){
    vector<int> m(V + 1);
    for (int i = 0; i < v.size(); i++) {
        for (int j = V; j >= v[i]; j--) {
            m[j] = max(m[j], m[j - v[i]] + w[i]);
        }
    }
    return m[V];
}

int knapsackV1d(vector<int>& w, vector<int>& v, int W) {
    int V = 0;
    for (auto x : v) {
        V += x;
    }
    vector<int> m(V + 1, 0x3f3f3f3f);
    m[0] = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = V; j >= v[i]; j--) {
            m[j] = min(m[j], m[j - v[i]] + w[i]);
        }
    }
    for (int j = V; j >= 0; j--) {
        if (m[j] < W) return j;
    }
    return 0;
}

void testKnapsack() {
    vector<vector<int>> ws { // weight
        {3, 2, 2}, // W = 5
        {10, 20, 30}, // W = 50
    };
    vector<vector<int>> vs { // value
        {5, 10, 20},
        {60, 100, 120},
    };

    // int res0 = knapsack(vv[0], ww[0], 5);
    // int res1 = knapsack(vv[1], ww[1], 50);
    // std::cout << "res0: " << res0 << "\n";
    // std::cout << "res1: " << res1 << "\n";
    //
    // // recursion
    // int res2 = knapsack(vv[0], ww[0], 5, 4);
    // int res3 = knapsack(vv[1], ww[1], 50, 3);
    // std::cout << "res2: " << res2 << "\n";
    // std::cout << "res3: " << res3 << "\n";
    //
    // vector<int> memo (5 + 1, -1);
    // int res4 = knapsack(vv[0], ww[0], 5, 4, memo);
    //
    // vector<int> memo1 (50 + 1, -1);
    // int res5 = knapsack(vv[1], ww[1], 50, 3, memo1);
    // std::cout << "res4: " << res4 << "\n";
    // std::cout << "res5: " << res5 << "\n";
    //

    vector<int> w1{1};
    vector<int> v1{10};
    int rrr = knapsackW(w1, v1, 4);
    cout << rrr << "\n";
    // knapsack W
    // int resW1 = knapsackW(ws[0], vs[0], 5); // W = 5
    // int resW2 = knapsackW(ws[1], vs[1], 50);
    // std::cout << "resW1: " << resW1 << "\n";
    // std::cout << "resW2: " << resW2 << "\n";

    // knapsack V
    int resV1 = knapsackV(w1, v1, 5);
    // int resV2 = knapsackV(ww[1], vv[1], 50);
    std::cout << "resV1: " << resV1 << "\n";
    // std::cout << "resV2: " << resV2 << "\n";

    vector<int> w2{1, 3, 4};
    vector<int> v2{10, 30, 60};
    int resV2 = knapsackV1(w2, v2, 5);
    std::cout << "resV2: " << resV2 << "\n";
}

int main(int argc, char *argv[]) {
    testKnapsack();
    return 0;
}
