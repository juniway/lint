
分析：
merge sort 时间复杂度是 O(nlogn)，但是由于通常要用到辅助内存，因此空间复杂度是 O(N)。

bool isSorted(int a[], int low, int high) {
    int *sorted_end = std::is_sorted_until(a+low, a+mid);
    int sorted_size = std::distance(a, sorted_end);
    if (sorted_size == mid - low) return true;
    return false;
}

// 用一个辅助数组 aux[] 来记录每一步 merge 的中间结果，最终把排序好的结果拷回原数组，aux[] 的大小跟原数组一样大。
// 为了避免每次 merge 时都重新分配 aux 内存，可以把 aux 放在最外层先分配好，然后通过函数参数的方式传进来

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

void sort(int a[], int aux[], int low, int high) {
    if (high <= low) return;
    int mid = low + (high - low) / 2;
    sort(a, aux, low, mid);
    sort(a, aux, mid + 1, high);
    merge(a, aux, low, mid, high);
}

void sort(int a[], int length) {
    int *aux = new int[length];
    sort(a, aux, 0, length - 1);
}