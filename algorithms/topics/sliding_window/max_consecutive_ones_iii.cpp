#include <climits>
#include <vector>
#include <iostream>

using std::vector;
using std::cout;

int longestOnes(vector<int>& A, int K) {
    int begin = 0, end = 0, maxLen = 0;

    while(end < A.size()) {
        if (A[end++] == 0) K--;
        while (K < 0) {
            if (A[begin++] == 0) K++;
        }

        maxLen = std::max(maxLen, end - begin);
    }

    return maxLen;
}

int longestOnes1(vector<int>& A, int K) {
    int begin = 0, end = 0;
    while(end < A.size()) {
        if (A[end++] == 0) K--;
        if (K < 0 ) {
            if(A[begin] == 0)
                K++;
            begin++;
        }
    }

    return end - begin;
}

int flipBits(vector<int>& A) {
    int end = 0, cur = 0, maxLen = INT_MIN, zeros = 0;
    while (end < A.size()) {
        if (A[end++] == 1) cur++;
        else {
            zeros++;
            cur = 0;
        }
        maxLen = std::max(maxLen, cur);
    }

    return maxLen + zeros;
}

void testLongestOnes() {
    // vector<int> A {1,1,1,0,0,0,1,1,1,1,0};
    vector<int> A{1,1,0,0,0,1};
    cout << longestOnes1(A, 2) << "\n";
}

void testFlipBits() {
    vector<int> A{0, 1, 0, 0, 1, 1, 0}; // n = 7
    vector<int> A1{0, 0, 0, 1, 0, 1}; // n = 6

    cout << flipBits(A) << "\n";
    cout << flipBits(A1) << "\n";
}

int main(int argc, char *argv[]) {
    // testLongestOnes();
    testFlipBits();
    return 0;
}
