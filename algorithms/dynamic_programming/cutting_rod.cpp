#include <iostream>
#include <vector>
using namespace std;

/* n is the rod length
 * price[i] is price for each length
*/
// recursive
int cuttingRod(int price[], int n) {
    if (n <= 0) return 0;

    int maxVal = INT_MAX;
    for (int i = 0; i < n; i++) {
        maxVal = max(maxVal, price[i] + cuttingRod(price, n - i + 1));
    }

    return maxVal;
}

// memo
// memo[i] means the max value when length is i
int cuttingRod(int price[], int n, vector<int>& memo) {
    if (memo[n] > 0) return memo[n];
    if (n <= 0) return 0;

    int maxVal = INT_MIN;
    for (int i = 0; i < n; i++) {
        maxVal = max(maxVal, price[i] + cuttingRod(price, n - i - 1, memo));
    }
    memo[n] = maxVal;

    return memo[n];
}

int cuttingRodM(int price[], int n) {
    vector<int> m(n + 1, 0);
    int res =  cuttingRod(price, n, m);
    for(auto x:m) {
        cout << x << " ";
    }
    cout << endl;
    return res;
}

int cuttingRodT(int price[], int n) {
    vector<int> m(n+1, 0);
    for (int i = 1; i <= n; i++) {
        int maxVal = INT_MIN;
        for (int j = 0; j < i; j++) {
            maxVal = max(maxVal, m[i-j-1] + price[j]);
        }
        m[i] = maxVal;
    }
    return m[n];
}

int maxProd(int n) {
    if (n == 0 || n == 1) return 0; // must have at least 1 cut
    int max_val = 0;
    for (int i = 1; i < n; i++) {
        max_val = max(i*(n-i), i*maxProd(n-i));
    }

    return max_val;
}

int max(int a, int b, int c) {
    auto max_ab = a>b?a:b;
    return max_ab>c?max_ab:c;
}

int maxProdT(int n) {
    vector<int> m(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        int max_val = 0;
        for (int j = 1; j < i; j++) {
            max_val = max(max_val, j*(i - j), j*m[i-j]);
        }
        m[i] = max_val;
    }

    return m[n];
}

int maxProdT1(int n) {
    vector<int> m(n + 1, 0);
    for (int i = 0; i <= n; i++) m[i] = i;
    // m[1] = 0;
    for (int i = 2; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            m[i] = max(m[i], j*m[i-j]);
        }
    }

    return m[n];
}

int maxProdT2(int n) {
    vector<int> m(n + 1, 0);
    for (int i = 0; i <= n; i++) m[i] = i-1;
    // m[1] = 0;
    for (int i = 2; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            m[i] = max(m[i], j*(i-j), j*m[i-j]);
        }
    }

    return m[n];
}

void testMaxProdT() {
    for (int i = 1; i <= 15; i++) {
        cout << i << " - " << maxProdT(i) << " - " << maxProdT1(i) << " - " << maxProdT2(i) << endl;
    }
}

void testCuttingRod() {
    vector<int> price{1, 5, 8, 9, 10, 17, 17, 20};
    // cout << cuttingRodM(&price[0], 8) << endl;
    cout << cuttingRodT(&price[0], 8) << endl;
}

int main(int argc, char *argv[]) {
    // testCuttingRod();
    testMaxProdT();
    return 0;
}
