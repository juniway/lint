#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void k_largest(vector<int> a, int k){    // n = a.size()
    int i;
    vector<int> ans;
    priority_queue<int, vector<int>, greater<int>> p;     // this is a min_heap, store maximum number
    
    
    for(i = 0; i < k; i++) // push k elements into the priority queue
        p.push(a[i]);

    //cout<<p.top()<<endl;

    const static int n = a.size();
    // for the next n-k elements, compare them with the element in priority_queue
    for(i = k; i < n; i++)
        if(a[i] > (p.top())){
            p.pop();
            p.push(a[i]);
       }
    
    // store the elements into a vector
    for(; !p.empty(); p.pop())
        ans.push_back(p.top());
       
    
    for(i=0;i<(int)ans.size();i++)
        printf("%d ",ans[i]);
    puts("");
}

void swap(int* a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(vector<int> &a, int start, int end){

    int small = start - 1;
    for (int i = start; i < end; ++i) {
        if(a[i] < a[end]){
            ++small;
            if(small != i){
                swap(&a[small], &a[i]);
            }
        }
    }
    ++small;
    printf("small:%d\n", small);

    swap(&a[small], &a[end]);


/*
    // Standard partition algorithm
    small = start;
    for (int i = start; i < end; i++)
    {
        if (a[i] < a[end])
        {
            swap(&a[i], &a[j]);
            small++;
        }
    }
    swap(&a[small], &a[end]);
    return small;

*/
    return small;
}


// the complexity for quicksort method to find kth smallest/largest number is:
// average O(N), worst case O(N^2)
int find_kth_smallest(vector<int>& A, int start, int end, int k){

    if(start == end){
        return A[start];
    }
    int index = partition(A, start, end);

    int size = index - start + 1;

    printf("index:%d, k:%d\n", size, k);

    // return 0;

    if(k == size){
        return A[size - 1];
    }
    else if(k < size){
        return find_kth_smallest(A, start, index - 1, k);
    }
    else{
        return find_kth_smallest(A, index + 1, end, k - size);
    }

}




// int quickselect(int* a, int low, int high, int k)
// {
//     if (low == high)
//         return a[low];
//     int mid = partition(a, low, high);
//     int sizeOfLeftSubArray = mid - low + 1;
//     if (sizeOfLeftSubArray > k)
//     {
//         return quickselect(a, low, mid-1, k);
//     }
//     else if (sizeOfLeftSubArray < k)
//     {
//         return quickselect(a, mid+1, high, k-sizeOfLeftSubArray);
//     }
//     else
//     {
//         return a[mid];
//     }
// }


int main(){
    vector<int> a{6, 8, 2, 3, 5, 1, 11, 4, 10, 7};
    int k = 3;


    int mom = MedianOfMedian(a, 5);
    printf("mom = %d.\n", mom);

    // k_largest(a,k);
    int result = find_kth_smallest(a, 0, a.size() - 1, k);

    printf("the %dth smallest number is %d\n", k, result);
    return 0;
}
