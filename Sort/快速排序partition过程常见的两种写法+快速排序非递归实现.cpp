http://www.cnblogs.com/TenosDoIt/p/3665038.html

快速排序partition过程常见的两种写法+快速排序非递归实现
这里不详细说明快速排序的原理，
快速排序主要是partition的过程，partition最常用有以下两种写法

第一种：

int mypartition(vector<int>&arr, int low, int high){
    int pivot = arr[low]; // 选第一个元素作为枢纽元
    while(low < high){
        while(low < high && arr[high] >= pivot)high--;
        arr[low] = arr[high]; // 从后面开始找到第一个小于pivot的元素，放到low位置
        while(low < high && arr[low] <= pivot)low++;
        arr[high] = arr[low]; // 从前面开始找到第一个大于pivot的元素，放到high位置
    }
    arr[low] = pivot; // 最后枢纽元放到low的位置
    return low;
}


第二种：

int mypartition(vector<int>&arr, int low, int high){
    int pivot = arr[high]; // 选最后一个元素作为枢纽元
    int location = low - 1; // location指向比pivot小的元素段的尾部
    for(int i = low; i < high; i++) // 比枢纽元小的元素依次放在前半部分
       if(arr[i] < pivot)
           swap(arr[i], arr[++location]);
    swap(arr[high], arr[location+1]);
    return location + 1;
}


当第二种方法也可以选择第一个元素作为枢纽(当我们对链表进行快排时选用这种做法)，对上面代码稍作改动即可，具体改动见注释
int mypartition(vector<int>&arr, int low, int high)
 {
     int pivot = arr[low];//选第一个元素作为枢纽元
     int location = low;//location指向比pivot小的元素段的尾部
     for(int i = low+1; i <= high; i++)//比枢纽元小的元素依次放在前半部分
     if(arr[i] < pivot)
         swap(arr[i], arr[++location]);
     swap(arr[low], arr[location]);//注意和前面的区别，是为了保证交换到头部的元素比pivot小
     return location;

 }


快排主函数如下：
void quicksort(vector<int>&arr, int low, int high){
    if(low < high){
        int middle = mypartition(arr, low, high);
        quicksort(arr, low, middle-1);
        quicksort(arr, middle+1, high);
    }
}


快排非递归实现

主要思想是用栈来保存子数组的左右边界，一下代码中用数组模拟栈
void quicksort_unrecursion(vector<int>&arr)//快速排序非递归
 {
     int mystack[2000];//假设递归不超过1000层
     //栈中保存下次需要排序的子数组的开始位置和结束位置
     int top = -1;
     mystack[++top] = 0;
     mystack[++top] = arr.size() - 1;
     while(top > 0)//栈非空
     {
         int high = mystack[top--], low = mystack[top--];
         int middle = mypartition(arr, low, high);
         if(middle+1 < high)//右边子数组入栈
         {
             mystack[++top] = middle+1;
             mystack[++top] = high;
         }
         if(low < middle-1)//左边子数组入栈
         {
             mystack[++top] = low;
             mystack[++top] = middle-1;
         }
     }
 }
