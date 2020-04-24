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
  
// Applies the heapify procedure - O(log N)
void Heapify(struct Node minHeap[], int size, int index)
{
    int i = index;
    struct Node temp;
   
    while ((2 * i) <= size) {
        // Left Child exists

        // 1-based array
        int parent = minHeap[i].value;
        int leftchd = minHeap[2 * i].value;
        int rightchd = minHeap[2 * i + 1].value;
   
        if ((2 * i) + 1 > size) {
            // Right child does not exist, but left does
              
            if (parent > leftchd) {
                // Left child is smaller than parent
                swap(minheap[i], minheap[left]);
                // temp = minHeap[i];
                // minHeap[i] = minHeap[2 * i];
                // minHeap[2 * i] = temp;
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
                swap(minheap[i], minheap[2*i])
                // temp = minHeap[2 * i];
                // minHeap[2 * i] = minHeap[i];
                // minHeap[i] = temp;
   
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

// Build Heap Procedure - O(N)
void BuildHeap(struct Node minHeap[], int size)
{
    int i;
   
    // Simply call heapify() for all nodes
    // except the last one...!
    // 1-based
    for (i = size / 2; i >= 1; --i) {
        Heapify(minHeap, size, i);
    }

    // if 0 based index, then
    // for(i = size / 2 - 1; i >= 0; --i){
    //     Heapify(minHeap, size, i);
    // }
}

// Adds an element to the heap and returns the size - O(log N)
int InsertNode(struct Node minHeap[], int size, struct Node newValue)
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
            // So, InsertNodeion is done, break
            break;
        }
    }
   
    return size;
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
  


void BuildHeap(int a[], int n){
    for(int i = n / 2 - 1; i >= 0; --i)
        heapify(a, n, i);
}

void minHeapify(int a*, int n, int index){
    // 0-based
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    while(left <= n){
        if(right > n){ // there is no right child
            if(a[index] > a[left]){ // if parent > left child, bubble the child up
                swap(&a[index], &a[left]);
            }
            break;
        }
        if(a[index] > a[left] || a[index] > a[right]){ // parent > left or parent > right, bubble the child up
            if(a[left] <= a[right]){
                swap(&a[iindex], &a[left]);
                index = 2 * index + 1;
            }
            else{
                swap(&a[index], &a[right]);
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
    // Extra size just to demonstrate InsertNodeion
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
      
    printf("\n\nInsertNode an element -\n");
    scanf("%d%d", &node.label, &node.value);
    n = InsertNode(minHeap, n, node);
   
    printf("\nHeap After InsertNode -\n");
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



