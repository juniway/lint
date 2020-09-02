#include <iostream>
using namespace std;

int power(int x, int n) {
    long long res = 1;
    while(n != 0) {
        if (n & 1) res *= x;
        x = x * x;
        n >>= 1;
    }

    return res;
}

int findNthRootFloor(int x, int n, int low, int high) {
    int mid = low + (high + low) / 2;
    if (power(mid, n) <= x && power(mid + 1, n) > x) return mid;
    else if (power(mid, n) < x)
        return findNthRootFloor(x, n, mid + 1, high);
    else return findNthRootFloor(x, n, low, mid - 1);

    return low;
}

int findNthRootFloor1(int x, int n) {
    // if x > 1, the root should be in a range [1, ...)
    int low = 1, high = x;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (power(mid, n) <= x)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return high;
}


void testNthRootFloor() {
    cout << findNthRootFloor(36, 3, 0, 36) << endl;
    cout << findNthRootFloor1(36, 3) << endl;
}

int main(int argc, char *argv[]) {
    testNthRootFloor();
    return 0;
}
