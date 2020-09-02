#include <iostream>
#include <vector>
using namespace std;

int binary_search0(vector<int>& A, int k) {
    int left = 0, right = A.size() - 1;
    while(left <= right) {
        int mid = (left + right)/2;
        cout << "A[" << mid << "] = " << A[mid] << endl;
        if (k < A[mid]) right = mid - 1;
        else if (k > A[mid]) left = mid + 1;
        else return mid;
    }

    cout << left << " " << right << endl;
    return -1;
}

int binary_search1(vector<int>& A, int k) {
    int left = 0, right = A.size();
    int mid;
    while(left < right) {
        mid = (left + right) / 2;
        cout << left << " " << right << ": " << mid << endl;
        if (k < A[mid]) right = mid;
        else if (k > A[mid]) left = mid + 1;
        else return mid;
    }

    cout << "end: " << left << " " << right << ": " << mid << endl;
    return -1;
}


// no return
int binary_search2(vector<int>& A, int k) {
    int left = 0, right = A.size() - 1;
    int mid;
    while(left < right) {
        mid = (left + right) / 2;
        cout << "end: " << left << " " << right << ": " << mid << endl;
        if (k <= A[mid]) right = mid;
        else left = mid + 1;
    }

    cout << "end: " << left << " " << right << ": " << mid << endl;
    return -1;
}

int binary_search3(vector<int>& A, int k) {
    int left = 0, right = A.size() - 1;
    int mid;
    while(left + 1 < right) {
        mid = (left + right) / 2;
        cout << "end: " << left << " " << right << ": " << mid << endl;
        if (k <= A[mid]) right = mid;
        else left = mid + 1;
    }

    cout << "end: " << left << " " << right << ": " << mid << endl;
    return right == k? right:-1;
}

// search 1 in [1, 3, 5]
// search 0 in [1, 3, 5]
int binary_search(vector<int>& A, int target) {
    int begin = 0, end = A.size() - 1;
    while (begin + 1 < end) {
        int mid = begin + (end - begin) / 2;
        if (A[mid] < target) begin = mid;
        else    end = mid;
    }
    if (A[begin] == target)  return begin;
    if (A[end] == target)    return end;
    return -1;
}

void testBinarySearch() {
    vector<int> A {1, 3, 5};
    // cout << binary_search(A, 1) << endl;
    // cout << binary_search(A, 3) << endl;
    // cout << binary_search(A, 4) << endl;
    // cout << binary_search1(A, 1) << endl << endl;
    // cout << binary_search1(A, 3) << endl << endl;
    // cout << binary_search1(A, 4) << endl << endl;
    // cout << binary_search1(A, 0) << endl << endl;
    cout << binary_search3(A, 0) << endl << endl;
    cout << binary_search3(A, 1) << endl << endl;
    cout << binary_search(A, 0) << endl << endl;
    cout << binary_search(A, 3) << endl << endl;
    // cout << binary_search1(A, 8) << endl;
    // cout << binary_search1(A, 11) << endl;
    // cout << binary_search1(A, 12) << endl;
    // cout << binary_search1(A, 2) << endl;
}

int main(int argc, char *argv[]) {
    testBinarySearch();
    return 0;
}
