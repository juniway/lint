// Merge sort without space optimization
// allocate two tmp array for each divide!

#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& a, int left, int mid, int right) {
    vector<int> low(a.begin() + left, a.begin() + mid + 1);
    vector<int> high(a.begin() + mid + 1, a.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < low.size() && j < high.size()) {
        if (low[i] <= high[j]) a[k++] = low[i++];
        else a[k++] = high[j++];
    }
    while (i < low.size()) {
        a[k++] = low[i++];
    }
    while (j < high.size()) {
        a[k++] = high[j++];
    }
}

void mergeSort(vector<int>& a, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

void printVector(vector<int> &A) {
    for(auto v : A)
        cout << v << " ";
    cout << endl;
}

void testMergeSort() {
    vector<int> a {3, 7, 8, 4, 1, 9, 5};
    printVector(a);
    mergeSort(a, 0, a.size() - 1);
    printVector(a);
}

int main(int argc, char *argv[]) {
    testMergeSort();
    return 0;
}
