/* Leetcode 992
 * Subarrays with K Different Integers
 *
 * */
#include <climits>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int subarraysWithKDistinct(vector<int>& A, int K) {
    if (A.size() < K) return 0;
    vector<int> m(A.size() + 1, 0);
    int begin = 0, end = 0, cnt = 0, res = 0, result = 1;
    while(end != A.size()) {
        if (m[A[end++]] == 1) cnt++;
        while(m[A[end]] > 1 || cnt > K) {
            if (cnt > K) {
                result = 1;
                cnt--;
            } else {
                result++;
            }
            m[A[begin++]]--;
        }

        if (cnt == K) {
            res += result;
        }
    }
    return res;
}

void testSubarrayWithKDistinct() {
    vector<int> A {1, 2, 1, 3, 4};
    cout << subarraysWithKDistinct(A, 3) << "\n";
}

int main(int argc, char *argv[]) {
    testSubarrayWithKDistinct();
    return 0;
}
