#include <iostream>

using namespace std;

uint32_t swapbits(uint32_t n, int i, int j) {
    uint32_t biti = (n >> i) & 1;
    uint32_t bitj = (n >> j) & 1;
    uint32_t x = biti ^ bitj;
    x = (x << i) | (x << j);
    return x ^ n;
}

int swapBits1(int n, int i, int j) {
    //left-shift 1 i and j times and using XOR
    n ^= 1 << i;
    cout << "n: " << n << endl;
    n ^= 1 << j;
    return n;
}

void testSwapBits() {
    cout << swapbits(12, 1, 2) << endl; // expected: 10
    cout << swapBits1(12, 1, 2) << endl; // expected: 10
}

int main(int argc, char *argv[]) {
    testSwapBits();
    return 0;
}
