#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

bool isSubsetSum(vector<int>& a, int sum, int n) { // n is size
    if (sum == 0) return true;
    // if (n == 0 && sum != 0) return false;
    if (n < 0 || sum < 0) return false;
    if (sum < a[n-1]) return false;
    return isSubsetSum(a, sum, n - 1) + isSubsetSum(a, sum - a[n-1], n -1);
}

bool partition(vector<int>& a) {
    int sum = 0;
    for(auto x : a) sum += x;

    if (sum % 2 != 0) return false;
    return isSubsetSum(a, sum/2, a.size());
}

// bottom up
// dp[sum] for elements that sums up to sum
bool partition1(vector<int>& a) {
    int sum = accumulate(a.begin(), a.end(), 0);
    if (sum % 2 != 0) return false;
    int halfSum = sum / 2 ;

    vector<bool> dp(halfSum + 1, false);
    dp[0] = true;

    for (int j = 0; j < a.size(); j++)
        for (int i = halfSum; i >= a[j]; i--) {
            dp[i] = dp[i] + dp[i - a[j]];
    }

    return dp[halfSum];
}

bool findPartition(vector<int>& a) {
    int n = a.size();
    int sum = accumulate(a.begin(), a.end(), 0);
    if (sum % 2 != 0) return false;

    vector<vector<bool>> part(sum/2 + 1, vector<bool>(n + 1, false));
    for (int i = 0; i <= n; i++) {
        part[0][i] = true;
    }

    for (int i = a[0]; i <= sum / 2; i++) {
        for (int j = 1; j <= n; j++) {
            part[i][j] = part[i][j-1]; // exclude
            if (i >= a[j - 1])
                part[i][j] = part[i][j] + part[i - a[j-1]][j];
        }
    }

    return part[sum/2][n];
}

void testSubsetSum() {
    vector<int> a {1, 5, 11, 5};

    cout << boolalpha << partition(a) << endl;
    cout << boolalpha << partition1(a) << endl;
    cout << boolalpha << findPartition(a) << endl;
}

int main(int argc, char *argv[]) {
    testSubsetSum();
    return 0;
}
