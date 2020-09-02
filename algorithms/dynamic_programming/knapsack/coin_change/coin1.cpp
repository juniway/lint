#include <iostream>
#include <vector>
using namespace std;

int countWays(vector<int>& coins, int i, int amount) {
    if (amount == 0) return 1;
    if (amount < 0) return 0;
    if (i == coins.size()) return 0;
    return countWays(coins, i, amount - coins[i]) + countWays(coins, i + 1, amount);
}

int countWays(vector<int>& coins, int amount) {
    if (coins.empty()) return amount == 0;
    int n = coins.size();
    vector<vector<int>> dp(n, vector<int> (amount, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= amount; j++) {
            if (j == 0) dp[i][j] = 1;
            else {
                int x = i >= 1 ? dp[i - 1][j] : 0; // not include
                int y = j - coins[i] >= 0 ? dp[i][j - coins[i]] : 0; // include
                dp[i][j] = x + y;
            }
        }
    }
    return dp[n - 1][amount];
}

void testCountWays() {
    vector<int> coins = {3, 4, 5};
    cout << countWays(coins, 0, 2) << endl;

    vector<int> coins1 = {1};
    cout << countWays(coins1, 1) << endl;
}

int main(int argc, char *argv[]) {
    testCountWays();
    return 0;
}
