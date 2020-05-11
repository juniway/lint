#include <iostream>
#include <bitset>
#define N 100
using namespace std;

// If we know the value range of element of the array,
// we can use bitset to sort the array, very fast.
void bitmap_sort(int a[], int n) {
    bitset<N> bitmap;
    for (int i = 0; i < length; i++)
        bitmap.set(a[i], 1);
    for (int i = 0; i < N; ++i) {
       if (bitmap[i])
          cout << i << " ";
    }
    cout << endl;
}

int main() {
    int a[] = {12, 5, 1, 89, 64, 49, 77, 91, 3, 0, 32, 50, 99};
    int length = sizeof(a) / sizeof(int);
    bitmap_sort(a, length);
}
