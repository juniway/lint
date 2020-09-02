#include <iostream>
#include <vector>
using namespace std;

int multiply(int A, int B) {
    if (A < B) return multiply (B, A);
    int ans = 0;
    for (int i = 0; B != 0; i++) {
        if (A & 1) {
            ans += (A << i);
        }
        B >>= 1;
    }
    return ans;
}

void testMultiply() {
    cout << multiply(1, 10) << endl;
}

int main(int argc, char *argv[]) {
    testMultiply();
    return 0;
}
