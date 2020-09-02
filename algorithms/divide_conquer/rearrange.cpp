#include <iostream>

void rearrange(int a[], int start, int end) {
    if (start >= end) return;
    int mid = start + (end - start)/2;
    int x = start + (mid - start)/2 + 1;
    int y = mid + 1;

    for (int i = x, j = y; i <= mid; i++, j++){
        std::swap(i, j);
    }
    rearrange(a, start, mid);
    rearrange(a, mid + 1, end);
}

void testRearrange() {
    int a[]{1, 3, 5, 7, 2, 4, 6, 8};
    rearrange(a, 0, 8);

    for (int i = 0; i < 8; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    testRearrange();
    return 0;
}
