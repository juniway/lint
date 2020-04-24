// qsort_nonrecursive.cpp
主要思想是用栈来保存子数组的左右边界，一下代码中用数组模拟栈


void quicksort_unrecursion(vector<int>&arr)
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