// http://theoryofprogramming.com/2014/12/28/binary-heaps/
/* ==========  ========== ========== ========= */
//        Binary Min Heap Data Structure       //
//           Array Implementation              //
//                                             //
//         Functions follow Pascal Case        //
//           Convention and Variables          //
//         follow Camel Case Convention        //
//                                             //
//            Author - Vamsi Sangam            //
//            Theory of Programming            //
/* ========== ========== ========== ========== */
   
#include <stdio.h>
#include <stdlib.h>
  
struct Node
{
    int label, value;
};
  
// Adds an element to the heap and returns the size - O(log N)
int EnqueueNode(struct Node minHeap[], int size, struct Node newValue)
{
    ++size;
    minHeap[size] = newValue;
   
    int i = size;
    struct Node temp;
   
    while (i >= 1) {
        if (minHeap[i / 2].value > minHeap[i].value) {
            // Parent node is greater than Child Node
            // Heap Property violated
            // So, swap
            temp = minHeap[i / 2];
            minHeap[i / 2] = minHeap[i];
            minHeap[i] = temp;
   
            i = i / 2;
        } else {
            // Parent is less or equal to the child
            // Heap property not violated
            // So, Insertion is done, break
            break;
        }
    }
   
    return size;
}
  
// Applies the heapify procedure - O(log N)
void Heapify(struct Node minHeap[], int size, int index)
{
    int i = index;
    struct Node temp;
   
    while ((2 * i) <= size) {
        // Left Child exists

        int parent = minHeap[i].value;
        int leftchd = minHeap[2 * i].value;
        int rightchd = minHeap[2 * i + 1].value;
   
        if ((2 * i) + 1 > size) {
            // Right child does not exist, but left does
              
            if (parent > leftchd) {
                // Left child is smaller than parent
                temp = minHeap[i];
                minHeap[i] = minHeap[2 * i];
                minHeap[2 * i] = temp;
            }
              
            break;
            // Once you reach this level where it does not
            // have a right child, the heap ends here
            // taking it to the next iteration is pointless
        }
   
        //Both Children exist
        if (parent > leftchd || parent > rightchd) {
            // One of the other child is lesser than parent
            // Now find the least amoung 2 children
   
            if (leftchd <= rightchd) {
                // Left Child is lesser, so, swap(parent, leftchd)
                temp = minHeap[2 * i];
                minHeap[2 * i] = minHeap[i];
                minHeap[i] = temp;
   
                // And go down the heap, until there is no left child
                // which mean we reach the leaf node, and heapify stops
                i = 2 * i;
            } 
            else if (leftchd > rightchd) {
                // Right Child is lesser, so, swap(parent, rightchd)
                temp = minHeap[(2 * i) + 1];
                minHeap[(2 * i) + 1] = minHeap[i];
                minHeap[i] = temp;
   
                // And go down the heap, until there is no left child
                // which mean we reach the leaf node, and heapify stops
                i = (2 * i) + 1;
            }
        } else {
            // Parent is lesser than its children
            break;
        }
    }
}
  
// Deletes the Node and returns the size - O(log N)
int DeleteNode(struct Node minHeap[], int size, int index)
{
    // Swap the indexed element with the last
    struct Node temp = minHeap[index];
    minHeap[index] = minHeap[size];
    minHeap[size] = temp;
   
    int i = index;
    --size;
   
    Heapify(minHeap, size - 1, i);
   
    return size;
}
  
// Build Heap Procedure - O(N)
void BuildHeap(struct Node minHeap[], int size)
{
    int i;
   
    // Simply call heapify() for all nodes
    // except the last one...!
    for (i = size / 2; i >= 1; --i) {
        Heapify(minHeap, size, i);
    }

    // if 0 based index, then
    // for(i = size / 2 - 1; i >= 0; --i){
    //     Heapify(minHeap, size, i);
    // }
}

void BuildHeap(int a[], int size){
    for(int i = size / 2 - 1; i >= 0; --i)
        heapify(a, size, i);
}

void minHeapify(int a*, int size, int index){
    int left_i = 2 * index + 1;
    int right_i = 2 * index + 2;
    while(left_i <= size){
        if(right_i > size){
            if(a[index] > a[left_i]){
                swap(&a[index], &a[left_i]);
            }
            break;
        }
        if(a[index] > a[left_i] || a[index] > a[right_i]){
            if(a[left_i] <= a[right_i]){
                swap(&a[iindex], &a[left_i]);
                index = 2 * index + 1;
            }
            else{
                swap(&a[index], &a[right_i]);
                index = 2 * index + 2;
            }
        }
    }
}
   
int main()
{
    int n, i;
   
    printf("Enter the Initial size of the Min Heap -\n");
    scanf("%d", &n);
    struct Node minHeap[n + 2];
    // Extra size just to demonstrate Insertion
    // and use the array as 1-indexed
      
    printf("Enter %d elements -\n", n);
   
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &minHeap[i].label, &minHeap[i].value);
    }
   
    BuildHeap(minHeap, n);
   
    printf("\nHeap -\n");
    for (i = 1; i <= n; ++i) {
        printf("%d, %d\n", minHeap[i].label, minHeap[i].value);
    }
   
    struct Node node;
      
    printf("\n\nInsert an element -\n");
    scanf("%d%d", &node.label, &node.value);
    n = EnqueueNode(minHeap, n, node);
   
    printf("\nHeap After Insert -\n");
    for (i = 1; i <= n; ++i) {
        printf("%d, %d\n", minHeap[i].label, minHeap[i].value);
    }
   
    printf("\n\nDelete an Element at index-\n");
    scanf("%d", &i);
    n = DeleteNode(minHeap, n, i);
   
    printf("\nHeap After Delete -\n");
    for (i = 1; i <= n; ++i) {
        printf("%d, %d\n", minHeap[i].label, minHeap[i].value);
    }
   
    return 0;
}



struct MaxHeap
{
    int size;
    int* array;
};

struct MaxHeap* createAndBuildHeap(int *array, int size)
{
    int i;
    struct MaxHeap* maxHeap = 
              (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   // initialize size of heap
    maxHeap->array = array; // Assign address of first element of array

    // Start from bottommost and rightmost internal mode and heapify all
    // internal modes in bottom up way
    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}

void maxHeapify(struct MaxHeap* maxHeap, int index)
{
    int parent = index;  // Initialize parent as root
    int left = 2 * (index + 1) - 1;  // left = 2*idx + 1
    int right = 2 * (index + 1); // right = 2*idx + 2
 
    // See if left child of root exists and is greater than root
    if (left < maxHeap->size && maxHeap->array[left] > maxHeap->array[parent])
        parent = left;
 
    // See if right child of root exists and is greater than
    // the parent so far
    if (right < maxHeap->size && maxHeap->array[right] > maxHeap->array[parent])
        parent = right;
 
    // Change root, if needed
    if (parent != idx)
    {
        swap(&maxHeap->array[parent], &maxHeap->array[idx]);
        maxHeapify(maxHeap, parent);
    }
}


void maxHeapify(int *a, int size, int i){
    int parent = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    if(left < size && a[left] > a[parent]){
        parent = left;
    }
    if(right < size && a[right] > a[parent]){
        parent = right;
    }

    if(parent != i){
        swap(a[parent], a[i]);
        maxHeapify(maxHeap, size, parent);
    }
}

void heapsort(int *a, int size){
    BuidHeap(a, size);
    while(size > 0){
        swap(a[0], a[size - 1]);
        --size;
        maxHeapify(a, 0);
    }
}

// The main function to sort an array of given size
void heapSort(int* array, int size)
{
    // Build a heap from the input data.
    struct MaxHeap* maxHeap = createAndBuildHeap(array, size);
 
    // Repeat following steps while heap size is greater than 1. 
    // The last element in max heap will be the minimum element
    while (maxHeap->size > 1)
    {
        // The largest item in Heap is stored at the root. Replace
        // it with the last item of the heap followed by reducing the
        // size of heap by 1.
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size;  // Reduce heap size
 
        // Finally, heapify the root of tree.
        maxHeapify(maxHeap, 0);
    }
}

int main()
{
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
    swap()
}