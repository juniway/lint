#include <iostream>
#include <vector>

using namespace std;

// 1. recursive
// int pow(int x, int n) {
//     if (n == 0) return 1;
//     return x*pow(x, n-1);
// }

// 2. divide and conquer
// int pow(int x, int n) {
//     if (n == 0) return 1;
//     if (n % 2 == 0) return pow(x, n/2)*pow(x, n/2);
//     else return x*pow(x, n/2)*pow(x, n/2);
// }

// 3. cache
int pow2(int x, int n) {
    if (n == 0) return 1;
    int tmp = pow2(x, n/2);
    if (n % 2 == 0) return tmp * tmp;
    else return x*tmp*tmp;
}

// 4. iterative
int pow1(int x, int n) {
    long long res = 1;
    while (n-- > 0) {
        res *= x;
    }
    return res;
}

int pow(int x, int n) {
    long long res = 1;
    while(n > 0) {
        if (n % 2 == 1) {
            res = res * x;
        }
        n = n / 2;
        x *= x;
    }
    return res;
}

void testPow() {
    vector<vector<int>> nums = {
        {5, 2},
        {1, 1},
        {1, 100},
    };

    for (int i = 0; i < nums.size(); i++) {
        cout << pow(nums[i][0], nums[i][1]) << endl;
    }
}

int main(int argc, char *argv[]) {
    testPow();
    return 0;
}
