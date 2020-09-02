#include <iostream>
#include <vector>
using namespace std;

int leftChild(int i) {
    return 2 * i + 1;
}

int rightChild(int i) {
    return 2 * i + 2;
}

void maxHeapify(vector<int>& a, int i, int n) {
    int parent = i, left = leftChild(i), right = rightChild(i);
    if (left < n && a[left] > a[parent]) {
        parent = left;
    }

    if (right < n && a[right] > a[parent]) {
        parent = right;
    }

    if (parent != i) {
        swap(a[i], a[parent]);
        maxHeapify(a, parent, n);
    }
}

void percolateDown(vector<int>& a, int i, int size) {
    int min, left = leftChild(i), right = rightChild(i);
    while (left < size) {
        min = left;
        if (right < size && a[left] < a[right]) min = right;
        if (a[min] > a[i]) {
            swap(a[min], a[i]);
            i = min;
            left = leftChild(i);
            right = rightChild(i);
        } else {
            break;
        }
    }
}

void bubbleUp(vector<int>& a, int x) {
    a.push_back(x);
    int i = a.size() - 1;
    int parent = i / 2;
    while (i > 0 && a[i] > parent) {
        swap(a[i], a[parent]);
        i = parent;
        parent = i / 2;
    }
}

void PercolateDown(vector<int>& num, int index, int size) {
    int min;
    while (index * 2 + 1 < size) {
        min = index * 2 + 1;
        if (index * 2 + 2 < size) {
            if (num[min] < num[index * 2 + 2]) {
                min = index * 2 + 2;
            }
        }

        if (num[min] <= num[index]) {
            break;
        } else {
            swap(num[index], num[min]);
            index = min;
        }
    }
}

void buildMaxHeap(vector<int>& a) {
    for(int i = a.size() / 2 - 1 ; i >= 0; i--) {
        // cout << i << ":" << a[i] << endl;
        // maxHeapify(a, i, a.size());
        PercolateDown(a, i, a.size());
    }
}

void heapSort(vector<int>& a) {
    buildMaxHeap(a);
    int i = a.size() - 1;
    while(i > 0) {
        swap(a[0], a[i]);
        i--;
        cout << i + 1 << endl;
        maxHeapify(a, 0, i+1);
    }
    cout << endl;
}

void testBuild() {
    // vector<int> a {16, 14, 10, 8, 7, 9, 3, 2, 4};
    // vector<int> a {9, 8, 3, 7, 16, 14, 2, 10, 4};
    vector<int> a {4, 6, 3, 5, 2, 1};
    buildMaxHeap(a);
    heapSort(a);
    for(auto x: a) {
        cout << x << " ";
    }
    cout << endl;
    // bubbleUp(a, 17);
    // for(auto x: a) {
    //     cout << x << " ";
    // }
    // cout << endl;
}

int main(int argc, char *argv[]) {
    testBuild();
    return 0;
}
