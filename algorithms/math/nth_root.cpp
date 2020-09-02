#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double power(double x, int y) {
    double res = 1;
    while (y != 0) {
        if (y & 1)
            res *= x;
        x = x * x;
        y >>= 1;
    }

    return res;
}

double findNthRoot(double x, int n) {
    double low, high;
    if (x >= 0 && x <= 1) { // x is in [0, 1]
        low = x;
        high = 1;
    } else { // x is in (1, +∞)
        low = 1;
        high = x;
    }

    double epsilon = 0.0000001;
    double guess = (low + high) / 2;
    while(std::fabs(power(guess, n) - x) >= epsilon) {
        if (power(guess, n) > x)
            high = guess;
        else low = guess;
        guess = (low + high) / 2;
    }

    return guess;
}

void testNthRoot() {
    cout << fixed << setprecision(16) << findNthRoot(5, 2) << endl;
    // cout << power(2.2, 3) << endl;
}

int main(int argc, char *argv[]) {
    testNthRoot();
    return 0;
}
