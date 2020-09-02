/*
 * Leetcode 33: Search in rotated array
 * */
#include <iostream>
#include <vector>
using namespace std;

// search a target value in a rotated sorted array
// [4, 5, 6, 0, 1, 2, 3]
// target: 5
// target: 1
int search(vector<int> &A, int target) {
    int begin = 0, end = A.size() - 1;
    while(begin <= end) {
        int mid = begin + (end - begin) / 2;
        if (A[mid] == target) return mid;
        if (A[mid] > A[begin]) {
            if (target >= A[begin] && target <= A[mid]) {
                end = mid;
            } else {
                begin = mid + 1;
            }
        } else if (A[mid] < A[begin]) {
            if(target >= A[mid] && target <= A[end]) {
                begin = mid;
            } else {
                end = mid - 1;
            }
        } else {
            begin += 1;
        }
    }
    return begin;
}

int search1(vector<int> &A, int target) {
    int begin = 0, end = A.size() - 1;
    while(begin < end) {
        int mid = begin + (end - begin) / 2;
        if(A[mid] >= A[begin]) {
            if (target >= A[begin] && target <= A[mid]) {
                end = mid;
            } else {
                begin = mid + 1;
            }
        } else {
            if(target >= A[mid] && target <= A[end]) {
                begin = mid;
            } else {
                end = mid - 1;
            }
        }
    }
    return begin;
}
void testSearch() {
    vector<int> A {1, 3, 1, 1, 1};
    cout << search(A, 1) << endl;
    // cout << search(A, 3) << endl;
    // cout << search(A, 5) << endl;
}

int main(int argc, char *argv[]) {
    testSearch();
    return 0;
}
