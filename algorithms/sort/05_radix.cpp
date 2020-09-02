
// Radix sort compare each digit of the number
int[] radixSort(int[] a) {
    int[] b = null;
    for(int p = 0; p < w/d; p++) {
        int c[] = new int[1 << d];
            // the next three for loops implement counting-sort
        b = new int[a.length];
        for(int i = 0; i < a.length; i++)
            c[(a[i] >> d * p) & ((1 << d) - 1)]++;
        for(int i = 1; i < 1 << d; i++)
            c[i] += c[i - 1];
        for(int i = a.length - 1; i >= 0; i--)
            b[--c[(a[i] >> d * p) & ((1 << d) - 1)]] = a[i];
        a = b;
    }
    return b;
}


int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}