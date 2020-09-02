#include <iostream>
#include <vector>
using namespace std;

int minCoins(int V, vector<int>& deno) {
    vector<int> dp(V + 1, 0);
    for (int i = 1; i <= V; i++) {
        int minC = INT_MAX;
        for (int j = 0; j < deno.size(); j++) {
            if (deno[j] <= i) {
                minC = min(minC, dp[i - deno[j]] + 1);
            }
        }
        dp[i] = minC;
    }
    return dp[V];
}

int minCoins1(int V, vector<int>& deno) {
    vector<int> dp(V + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < deno.size(); j++) {
            if (deno[j] <= i) {
                int minj = dp[i - deno[j]];
                if (minj != INT_MAX && minj + 1 < dp[i])
                    dp[i] = minj + 1;
            }
        }
    }

    return dp[V];
}

// get the coins
// reference: https://www.codesdope.com/course/algorithms-coin-change/
vector<int> minCoin2(int V, vector<int>& deno) {
    vector<int> dp(V + 1, INT_MAX);
    dp[0] = 0;
    vector<int> S(V + 1, 0);
    for (int i = 1; i <= V; i++) {
        int coin = 0;
        for (int j = 0; j < deno.size(); j++) {
            if (i >= deno[j]) {
                int minC = dp[i - deno[j]];
                if (minC != INT_MAX && minC + 1 < dp[i]) {
                    dp[i] = minC + 1;
                    coin = j;
                }
            }
        }
        S[i] = coin;
    }

    vector<int> res;
    int l = V;
    while (l > 0) {
        res.push_back(deno[S[l]]);
        l = l - deno[S[l]];
    }
    return res;
}

void testMinCoins() {
    vector<pair<int, vector<int>>> denos = {
        {200, {1, 2, 5, 10, 20, 50, 100, 500, 1000}}, // expect: 100, 100
        {11, {9, 6, 5, 1}}, // expect: 6, 5
    };

    for (auto deno : denos) {
        auto res = minCoins1(deno.first, deno.second);
        cout << res << endl;
        auto res2 = minCoin2(deno.first, deno.second);
        for (auto v : res2) cout << v << " "; cout << endl;
    }
}

int main(int argc, char *argv[]) {
    testMinCoins();
    return 0;
}
