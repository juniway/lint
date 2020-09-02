#include <iostream>
#include <vector>
using namespace std;

// find smallest even in [1, 3, 5, 6, 8, 10]
int findEven0(vector<int>& A) {
    int left = 0, right = A.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (A[mid] % 2 == 0) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return A[left];
}

int findEven(vector<int>& A) {
    int left = 0, right = A.size() - 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (A[mid] % 2 == 0) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return A[left];
}

void testFind() {
    vector<int> A{1, 3, 5, 6, 8, 10};
    // cout << findEven(A) << endl;
    cout << findEven(A) << endl;
}

int main(int argc, char *argv[]) {
    testFind();
    return 0;
}
