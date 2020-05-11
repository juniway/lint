#include <iostream>
#include <array>
#include <vector>

using std::vector;
using std::cout;

void PrintArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int conquerAndCount(int a[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(a+low, a+mid+1);
    vector<int> right(a+mid+1, a+high+1);

    int i = 0, j = 0, k = low, inversions = 0;
    while(i < n1 && j < n2) {
        if(left[i] <= right[j]) a[k++] = left[i++];
        else {
            a[k++] = right[j++];
            int count = (mid + 1) - (low + i);
            inversions += count;
        }
    }

    while (i < n1) {
        a[k++] = left[i++];
    }

    while (j < n2) {
        a[k++] = right[j++];
    }

    return inversions;

}

int divide(int a[], int low, int high) {
    if (low >= high) return 0;
    int mid = low + (high - low)/2;
    int leftInversions = divide(a, low, mid);
    int rightInversions = divide(a, mid + 1, high);
    int mergeInversions = conquerAndCount(a, low, mid, high);

    return leftInversions + rightInversions + mergeInversions;
}

void CountReversePairs(int a[], int n) {
    int total = divide(a, 0, n - 1);
    cout << "total: " << total << "\n";
}

void TestCountReversePairs() {
    int a[]{1, 5, 4, 8, 10, 2, 6, 9, 12, 11, 3, 7};
    CountReversePairs(a, 12);
}

int main(int argc, char *argv[]) {
    TestCountReversePairs();
    return 0;
}
