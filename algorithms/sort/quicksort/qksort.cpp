#include <iostream>
#include <vector>

using namespace std;


int partition(vector<int>& a, int left, int right) {
    int l = left + 1, r = right;
    while (l <= r) {
        if (a[l] > a[left] && a[r] < a[left]) {
            swap(a[l++], a[r--]);
        }
        if (a[l] <= a[left]) l++;
        if (a[r] >= a[left]) r--;
    }
    swap(a[left], a[r]);
    return r;
}

// right as the pivot
int partition2(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = (left - 1); // index of smaller element
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i+1;
}

// left as the pivot
int partition3(vector<int>& arr, int left, int right) {
    int pivot = arr[left];
    int i = left; // index of smaller element
    for (int j = left + 1; j <= right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i], arr[left]);
    return i;
}


int partition1(vector<int>& a, int left, int right) {
    int i = left + 1, j = right;
    while (i < j) {
        if (a[i] <= a[left]) i++;
        else if (a[j] >= a[left]) j--;
        else {
            swap(a[i++], a[j--]);
        }
    }

    if (a[i] > a[left])
        i--;
    swap(a[i], a[left]);

    return i;
}

void quickSort(vector<int>& a, int left, int right) {
    if (left >= right) return;

    int pivot = partition3(a, left, right);
    quickSort(a, left, pivot - 1);
    quickSort(a, pivot + 1, a.size() - 1);
}

void quickSort(vector<int>& a) {
    quickSort(a, 0, a.size() - 1);
}

void testQuickSort() {
    // vector<int> a{4, 4, 3, 9, 6, 11, 1};
    // vector<int> a{3, 7, 1, 4, 0, 5, 9, 6, 2, 8};
    // vector<int> a{7, 3, 1, 5, 4};
    vector<int> a{3,2,3,1,2,4,5,5,6};
    // vector<int> a{3, 5, 1, 7, 4};
    quickSort(a, 0, a.size() - 1);

    for(auto x : a) cout << x << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testQuickSort();
    return 0;
}
