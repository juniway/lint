#include <iostream>
#include <vector>

using namespace std;

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 2) + fibonacci(n - 1);
}

// memoization
int fibonacciM(int n, vector<int>& m) {
    if (m[n] < 0) return m[n];
    if (n <= 2) m[n] = 1;
    else {
        m[n] =  fibonacciM(n - 2, m) + fibonacciM(n - 1, m);
    }

    return m[n];
}

// tabulation
int fibonacciT(int n) {
    if (n <= 0) return n;
    vector<int> m(n+1);
    m[0] = 0, m[1] = 1;
    for (int i = 2; i <= n; i++) {
        m[n] = m[n-2] + m[n-1];
    }
    return m[n];
}

// optimizae
int fibonacciO(int n) {
    if (n <= 1) return n;
    int two = 0;
    int one = 1;

    for (int i = 2; i <= n; i++) {
        int val = one + two;
        two = one;
        one = val;
    }

    return one;
}

void testFibo() {
    int n = 7;
    vector<int> m(n+1, -1);
    m[0] = 0, m[1] = 1;
    cout << fibonacciM(n, m) << endl;
    cout << fibonacciO(n) << endl;
}

int main(int argc, char *argv[]) {
    testFibo();
    return 0;
}
