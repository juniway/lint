#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// TODO:
// https://leetcode-cn.com/problems/number-of-2s-in-range-lcci/solution/gen-ju-gui-lu-by-zyphd/
int get_result(int n) {
    int result = 0;
    int digit = log10(n) + 1;
    if (digit == 1) {
        if (n >= 2) result = 1;
        else result = 1;
    }
    else {
        int k = (n / (int)pow(10, digit - 1)) % 10;
        if (k == 0) result = 0;
        if (k == 1) result = (digit - 1) * pow(10, digit - 2);
        if (k == 2) result = n % (int)pow(10, digit - 1) + 1 + (n % 10) * (digit - 1) * pow(10, digit - 2);
        if (k > 2)
            result = pow(10, digit - 1) + (n % 10) * (digit - 1) * pow(10, digit - 2);
    }

    return result;
};

int numberOf2sInRange(int n) {
    int result = 0;

    int d = log10(10) + 1;
    for (int i = 0; i < d; i++) {
        int res = get_result(n / (int)pow(10, i));
        result += res;
    }

    return result;
}

void testNumberOf2s() {
    cout << numberOf2sInRange(9) << endl;
    cout << numberOf2sInRange(12) << endl;
    cout << numberOf2sInRange(20) << endl;
    cout << numberOf2sInRange(99) << endl;
    cout << numberOf2sInRange(999) << endl;
}

int main(int argc, char *argv[]) {
    testNumberOf2s();
    return 0;
}
