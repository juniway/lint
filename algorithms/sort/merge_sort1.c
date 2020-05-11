#include <iostream>
using namespace std;


void merge(int* a, int left, int mid, int right);

void merge_sort(int* a, int low, int high){
    if(low < high){
        int mid = low + (high - low)/2;
        merge_sort(a, low, mid);
        merge_sort(a, mid+1, high);
        merge(a, low, mid, high);
    }
}

void merge(int* a, int low, int mid, int high){
    int h, i, j, k;
    int *b = new int[high-low];
    h = low;
    i = low;
    j = mid + 1;

    while((h <= mid) && (j <= high)){
        if(a[h] <= a[j]){
            b[i] = a[h];
            ++h;
        }
        else{
            b[i]=a[j];
            ++j;
        }
        i++;
    }

    if(h>mid){ // if h > mid, then it means all elements in left are set in final arr, we only need to put all elements in right to arr
        for(k = j; k <= high; k++){
            b[i] = a[k];
            ++i;
        }
    }
    else{ // if h <= mid, then it means all elements in right are set in final arr, we only need to put all elements in left to arr
        for(k = h; k <= mid; k++){
            b[i] = a[k];
            ++i;
        }
    }

    for(k = low; k <= high; k++) // copy all elements back to array a[]
        a[k] = b[k];

    delete b;
}



void merge_sort(vector<int> &nums, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge_sort(nums, low, mid);
        merge_sort(nums, mid + 1, high)
        merge(nums, low, mid, high);
    }
}

vector<int> merge(vector<int> &nums, int low, int mid, int high) {
    vector<int> res;
    int i = low, j = high, k = mid;
    while (i < j)
}

int main(){

    int arr[]={7, 28, 11, 25, 55, 34, 17, 9, 3, 13};
    int size = sizeof arr/sizeof arr[0];

    // merge sort
    merge_sort(arr, 0, size-1);

    cout<<"The sorted list (using MERGE SORT) is :"<<endl;

    for(int i=0; i<size; i++)
        cout<<arr[i]<<"  ";
    cout<<endl;

    return 0;
}
