#include <iostream>
using namespace std;

long long decimal2binary(int n) {
    long long res = 0;
    int i = 1;
    while (n > 0) {
        res += (n & 1) * i;
        n >>= 1;
        i *= 10;
    }

    return res;
}

int binary2decimal(long long n) {
    int res = 0, base = 1;
    while (n > 0) {
        res += base * (n % 10);
        n = n / 10;
        base *= 2;
    }

    return res;
}

void testDecimal2Binary() {
    cout << decimal2binary(12) << endl;
    cout << binary2decimal(1100) << endl;
}

int main(int argc, char *argv[]) {
    testDecimal2Binary();
    return 0;
}
