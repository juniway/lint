struct MaxHeap {
    int size;
    int* array;
};

// MaxHeap 实际上就是一个 Array，只不过，写成 struct 的话，通用性更高一些。

struct MaxHeap* createAndBuildHeap(int *array, int size) {
    int i;
    struct MaxHeap* maxHeap = (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   // initialize size of heap
    maxHeap->array = array; // Assign address of first element of array

    // Start from bottommost and rightmost internal mode and heapify all
    // internal modes in bottom up way
    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}

// recursive
void maxHeapify(struct MaxHeap* maxHeap, int index){
    int n = maxHeap->size;
    // for 1-based array:
    // left = 2 * index
    // right = 2 * index + 1

    // for 0-based array:
    // Initialize parent is the root node
    int parent = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // See if left child of root exists and is greater than root
    if (left < n && maxHeap->array[left] > maxHeap->array[parent])
        parent = left;

    // See if right child of root exists and is greater than
    // the parent so far
    if (right < maxHeap->size && maxHeap->array[right] > maxHeap->array[parent])
        parent = right;

    // Change root, if needed
    if (parent != index){
        swap(&maxHeap->array[parent], &maxHeap->array[idx]);
        maxHeapify(maxHeap, parent);
    }
}


// void maxHeapify(int a[], int size, int i){
//     int parent = i;
//     int left = i * 2 + 1;
//     int right = i * 2 + 2;
//     if(left < size && a[left] > a[parent]){
//         parent = left;
//     }
//     if(right < size && a[right] > a[parent]){
//         parent = right;
//     }

//     if(parent != i){
//         swap(a[parent], a[i]);
//         maxHeapify(maxHeap, size, parent);
//     }
// }

// void minHeapify(int a*, int n, int index){
//     int left = 2 * index + 1;
//     int right = 2 * index + 2;
//     while(left <= n){
//         if(right > n){ // if no right child
//             if(a[index] > a[left]){ // if parent > left child, bubble the child up
//                 swap(&a[index], &a[left]);
//             }
//             break;
//         }
//         if(a[index] > a[left] || a[index] > a[right]){ // parent > left or parent > right, bubble the child up
//             if(a[left] <= a[right]){
//                 swap(&a[iindex], &a[left]);
//                 index = 2 * index + 1;
//             }
//             else{
//                 swap(&a[index], &a[right]);
//                 index = 2 * index + 2;
//             }
//         }
//     }
// }

void heapsort(int *a, int size){
    BuidHeap(a, size);
    while(size > 0){
        swap(a[0], a[size - 1]);
        --size;
        maxHeapify(a, 0);
    }
}

// The main function to sort an array of given size
void heapSort(int* array, int size) {
    // Build a heap from the input data.
    struct MaxHeap* maxHeap = createAndBuildHeap(array, size);

    // Repeat following steps while heap size is greater than 1.
    // The last element in max heap will be the minimum element
    while (maxHeap->size > 1) {
        // The largest item in Heap is stored at the root. Replace
        // it with the last item of the heap followed by reducing the
        // size of heap by 1.
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size;  // Reduce heap size

        // Finally, heapify the root of tree.
        maxHeapify(maxHeap, 0);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(arr)/sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, size);

    heapSort(arr, size);

    printf("\nSorted array is \n");
    printArray(arr, size);
    return 0;
}

void heap_sort(int a*, int n){
    createAndBuildHeap();
    swap();
}