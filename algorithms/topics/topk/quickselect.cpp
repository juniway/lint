#include <iostream>
#include <vector>

using namespace std;

// kth largest = (N - k)th smallest
int partition(vector<int>& a, int left, int right) {
    int i = left + 1, j = right;
    while (i <= j) {
        if (a[i] >= a[left]) i++;
        if (a[j] <= a[left]) j--;
        if (a[i] > a[left] && a[j] < a[left]) {
            swap(a[i++], a[j--]);
        }
    }

    swap(a[j], a[left]);
    return j;
}


int kthlargest(vector<int>& a, int k) {
    int left = 0, right = a.size() - 1, kth;
    while(true) {
        int idx = partition(a, left, right);
        if (idx == k - 1) {
            kth = a[idx];
            break;
        } else if (idx < k - 1) {
            left = idx + 1;
        } else {
            right = idx - 1;
        }
    }
    return kth;
}


void testKthLargest() {
    vector<int> a {1, 2, 3, 4, 5};
    cout << kthlargest(a, 2) << endl;
}

int main(int argc, char *argv[]) {
    testKthLargest();
    return 0;
}
