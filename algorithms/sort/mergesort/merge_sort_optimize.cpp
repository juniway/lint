#include <iostream>
#include <vector>

using namespace std;

void merge(int a[], int aux[], int low, int mid, int high) {
    // copy to aux[]
    for (int i = low; i <= high; i++) {
        aux[i] = a[i];
    }

    // merge back to a[]
    // 步骤是：
    // 从 aux[] 中拿出元素，从 a[] 的开头一个个填
    // i 指向左半部分的起始，j 指向右半部分的起始。 边界条件：确保 i 和 j 不要超过自己部分的右边界
    // 如果 aux[i] > aux[j]，那么先把 aux[i] 拷贝到 a[k] 中
    int i = low, j = mid+1;
    for (int k = low; k <= high; k++) {
        if      (i > mid)              a[k] = aux[j++];
        else if (j > high)             a[k] = aux[i++];
        else if (aux[j] < aux[i])      a[k] = aux[j++];
        else                           a[k] = aux[i++];
    }
}

void merge(vector<int>& a, vector<int>& aux, int left, int mid, int right) {
    aux = a;
    int i = left, j = mid + 1, k = left;
    while(i <= mid && j <= right) {
        if (aux[i] <= aux[j]) a[k++] = aux[i++];
        else a[k++] = aux[j++];
    }

    while (i <= mid) a[k++] = aux[i++];
    while (j <= right) a[k++] = aux[j++];
}

void mergeSort(vector<int>& a, vector<int>& aux, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, aux, left, mid);
    mergeSort(a, aux, mid + 1, right);
    merge(a, aux, left, mid, right);
}

// optimize
void mergeSort(vector<int>& a) {
    vector<int> aux(a.size());
    mergeSort(a, aux, 0, a.size() - 1);
}

void testMergeSort() {
    vector<int> a {3, 7, 8, 4, 1, 9, 5};
    mergeSort(a);

    for (auto x : a) cout << x << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testMergeSort();
    return 0;
}
