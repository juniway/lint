
// link: http://www.codinghelmet.com/?path=exercises/kth-smallest
/*
1. Divide the array into N/C columns of elements,
   for small odd C.

2. Find the median of each column by sorting it.

3. Take only the medians and repeat steps 1-2 recursively
   until only one value remains. That value is picked as the pivot.

4. Iterate through the array and count number of elements
   strictly smaller than the pivot (S), larger than the pivot (L)
   and equal to the pivot (E=N-S-L).

5. If N>K, move all values smaller than the pivot
   to the beginning of the array and recursively run
   the whole algorithm on that sub-array.

6. If N+E>K, conclude that Kth element is equal
   to the current pivot so return the pivot value
   and terminate the algorithm.

7. Otherwise, move all values larger than the pivot
   to the beginning of the array and recursively run
   the whole algorithm on that sub-array.

*/

// this algorithm is called: Median of Medians Algorithm
// It’s discovered by 5 great computer scientists:
// Manuel Blum (Blum speedup theorem), 
// Robert Floyd (Floyd-Warshall shortest path algorithm), 
// Vaughan Pratt (Pratt primality certificate), 
// Ron Rivest (RSA cryptography algorithm), 
// Robert Tarjan (graph algorithms and data structures). 
- See more at: http://www.ardendertat.com/2011/10/27/programming-interview-questions-10-kth-largest-element-in-array/#sthash.RaExvoEi.dpuf

int FindKthSmallest(vector<int>& a, int k){
    int value = 0;
    int n = a.size();
    int c = 5;  // Constant used to divide the array into columns

    while (true){

        // Extract the median of medians and take it as the pivot
        int pivot = MedianOfMedian(a, c);

        // Now count how many smaller and larger elements are there
        int smallerCount = 0;
        int largerCount = 0;
        CountElements(a, n, pivot, out smallerCount, out largerCount);

        // Finally, partition the array
        if (k < smallerCount)
        {
            Partition(a, n, pivot, true);
        }
        else if (k < n - largerCount)
        {
            value = pivot;
            break;
        }
        else
        {
            k -= n - largerCount;
            n = Partition(a, pivot, false);
        }

    }

    return value;

}
int MedianOfMedian(vector<int>&a, int c){
    int n = a.size();
    while (n > 1){
        int pos = 0;
        int tmp = 0;

        for (int start = 0; start < n; start += c){
            int end = start + c;
            if (end > n)    // Last column may have
                end = n;    // less than c elements

            // Sort each column, selection sort
            int min;
            for (int i = start; i < end - 1; i++){
                min = i;
                for (int j = i + 1; j < end; j++){
                    if (a[j] < a[i]){
                        min = j;
                    }
                }
                tmp = a[i];
                a[i] = a[min];
                a[min] = tmp;
            }

            // Pick the column's median and promote it
            // to the beginning of the array
            end = (start + end) / 2;    // Median position
            tmp = a[end];
            a[end] = a[pos];
            a[pos++] = tmp;
            printf("pos = %d\n", pos);
        }
        n = pos;    // Reduce the array and repeat recursively
        printf("n = %d\n", n);
    }

    return a[0];    // Last median of medians is the pivot

}

void Partition(int[] a, int& n int pivot, bool extractSmaller)
{
    int pos = 0;
    for (int i = 0; i < n; i++)
        if ((extractSmaller && a[i] < pivot) || (!extractSmaller && a[i] > pivot))
        {
            int tmp = a[i];
            a[i] = a[pos];
            a[pos++] = tmp;
        }
    n = pos;
}


int partition(int arr[], int l, int r, int k);

// A simple function to find median of arr[].  This is called
// only for an array of size 5 in this program.
int findMedian(int arr[], int n)
{
    sort(arr, arr+n);  // Sort the array
    return arr[n/2];   // Return middle element
}

int kthSmallest(int arr[], int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1; // Number of elements in arr[l..r]

        // Divide arr[] in groups of size 5, calculate median
        // of every group and store it in median[] array.
        int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups;
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n) //For last group with less than 5 elements
        {
            median[i] = findMedian(arr+l+i*5, n%5); 
            i++;
        }    

        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        int medOfMed = (i == 1)? median[i-1]:
                                 kthSmallest(median, 0, i-1, i/2);

        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int pos = partition(arr, l, r, medOfMed);

        // If position is same as k
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  // If position is more, recur for left
            return kthSmallest(arr, l, pos-1, k);

        // Else recur for right subarray
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }

    // If k is more than number of elements in array
    return INT_MAX;
}