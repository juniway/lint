#include <iostream>
#include <vector>
using namespace std;

vector<int> MaxSubSum(vector<int>& a) {
    int begin = 0, end = 0, localSum = 0, maxSum = 0;
    int e;
    while (end < a.size()) {
        localSum += a[end];
        if (localSum < a[end]) {
            localSum = a[end];
            begin = end;
        }
        if (maxSum < localSum) {
            maxSum = localSum;
            e = end;
        }
        end++;
    }

    return {begin, e};
}

void testMaxSubarraySum() {
    vector<int> a {-2,1,-3,4,-1,2,1,-5,4};
    // cout << MaxSubSum(a) << endl;
    auto res = MaxSubSum(a);
    cout << res[0] << ", " << res[1] << endl;
}

int main(int argc, char *argv[]) {
    testMaxSubarraySum();
    return 0;
}
