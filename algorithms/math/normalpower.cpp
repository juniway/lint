#include <iostream>
using namespace std;

long long normalPower(int base, int power) {
    long long res = 1;
    while (power > 0) {
        res *= base;
        res %= 1000;
        power--;
    }

    return res % 1000;
}

// fast power
long long fastPower(int base, int power) {
    long long res = 1;
    while (power > 0) {
        if (power & 1) {
            res = res * base % 1000;
        }
        power >>= 2;
        base = base * base % 1000;
    }
    return res;
}

void testNormalPower() {
    int base, power;
    while(true) {
        cin >> base >> power;
        if (base == 0 && power == 0) break;
        cout << normalPower(base, power) << endl;
    }
}

int main(int argc, char *argv[]) {
    testNormalPower();
    return 0;
}
