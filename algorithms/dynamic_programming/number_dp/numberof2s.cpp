#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int numberOf2sInRange(int n) {
    if (n < 2) return 0;
    int digit = log10(n) + 1;
    vector<vector<int>> dp(digit + 1, vector<int>(2));
    dp[1][0] = (n % 10 >= 2) ? 1 : 0;
    dp[1][1] = 1;

    for (int i = 2; i <= digit; i++) {
        int k = (n / (int)pow(10, i - 1)) % 10;
        dp[i][0] = k * dp[i - 1][1] + dp[i - 1][0];
        if (k == 2) {
            dp[i][0] += n % (int)pow(10, i - 1) + 1;
        } else if (k > 2) {
            dp[i][0] += (int)pow(10, i - 1);
        }
        dp[i][1] = 10 * dp[i - 1][1] + (int)pow(10, i - 1);
    }
    return dp[digit][0];
}

void testNumberOf2s() {
    cout << numberOf2sInRange(9) << endl;
    cout << numberOf2sInRange(99) << endl;
    cout << numberOf2sInRange(999) << endl;
}

int main(int argc, char *argv[]) {
    testNumberOf2s();
    return 0;
}
