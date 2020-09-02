#include <iostream>
#include <vector>

using std::vector;
using std::cout;

void fillPrefixSum(int a[], int n, int prefixSum[]) {
    prefixSum[0] = a[0];
    for (int i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + a[i];
    }
}

void testPrefixSum() {
    int a[]{10, 4, 16, 20};
    int n = (sizeof a)/sizeof a[0];
    vector<int> prefixSum(n);
    fillPrefixSum(a, n, &prefixSum[0]);

    for (auto x:prefixSum) {
        cout << x << " ";
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    testPrefixSum();
    return 0;
}
