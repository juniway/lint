// qsort_nonrecursive.cpp
// idea:
// 1) use stack to save the left and right bound
// 2) use array to mock stack

void quicksort_norecursion(vector<int>&arr) {
    int mystack[2000]; // suppose stack would surpass 1000
    // save the begin and end of sub-array
    int top = -1;
    mystack[++top] = 0;
    mystack[++top] = arr.size() - 1;
    while(top > 0) { // stack is not empty
        int high = mystack[top--], low = mystack[top--];
        int middle = mypartition(arr, low, high);
        if(middle+1 < high) { // push right sub-array into stack
            mystack[++top] = middle+1;
            mystack[++top] = high;
        }
        if(low < middle-1) { // push left sub-array into stack
            mystack[++top] = low;
            mystack[++top] = middle-1;
        }
    }
}

int mypartition(vector<int>&arr, int low, int high) {
    int pivot = arr[low];//选第一个元素作为枢纽元
    while(low < high) {
        while(low < high && arr[high] >= pivot)high--;
        arr[low] = arr[high];//从后面开始找到第一个小于pivot的元素，放到low位置
        while(low < high && arr[low] <= pivot)low++;
        arr[high] = arr[low];//从前面开始找到第一个大于pivot的元素，放到high位置
    }
    arr[low] = pivot;//最后枢纽元放到low的位置
    return low;
}