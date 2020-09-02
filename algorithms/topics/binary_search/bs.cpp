#include <iostream>
#include <vector>
using namespace std;

int binarySearch(vector<int> A, int target) {
    int low = 0, high = A.size() - 1;
    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (A[mid] <= target) { // upper bound
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    cout << "low: " << low << ", high: " << high << endl;
    if (A[high] <= target) return high;
    return low;
}

int binarySearch1(vector<int> A, int target) {
    int low = 0, high = A.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (A[mid] == target) return mid;
        else if (A[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << "low: " << low << ", high: " << high << endl;
    return -1;
    if (A[low] <= target) return low;
    return high;
}
void testBS() {
    vector<int> A = {5, 5, 5, 5};
    cout << binarySearch(A, 5) << endl;
}

int main(int argc, char *argv[]) {
    testBS();
    return 0;
}
