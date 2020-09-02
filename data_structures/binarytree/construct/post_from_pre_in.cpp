#include <iostream>

int search(int arr[], int x, int n) {
    for(int i = 0; i < n; i++) {
        if (arr[i] == x) return i;
    }
    return -1;
}

void printPostOrder(int in[], int pre[], int n) {
    int root = search(in, pre[0], n);
    if (root != 0) printPostOrder(in, pre + 1, root);
    if (root != n - 1) printPostOrder(in + root + 1, pre + root + 1, n - root - 1);
    std::cout << pre[0] << " ";
}

void testPrintPostOrder() {
    int in[]{4, 2, 5, 1, 3, 6};
    int pre[]{1, 2, 4, 5, 3, 6};
    printPostOrder(in, pre, 6);
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    testPrintPostOrder();
    return 0;
}
