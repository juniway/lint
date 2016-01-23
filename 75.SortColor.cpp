[LeetCode 75] Sort Colors
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent,
with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's,
then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?'

分析：题目说了一大堆，就是让对一个数组排序，数组中的元素只有0、1、2，并且要求只能遍历一遍数组，常数空间复杂度。
借助于快速排序的partition思想，以1为枢纽元对数组进行划分，使0在数组的左边，2在数组的右边，1在数组的中间。

class Solution {
public:
    void sortColors(vector<int> &A) {
        //zeroEnd是放0那部分的尾部索引，twoEnd是放2那部分的首部索引
        //碰到0放到zeroEnd+1处，碰到2放到twoEnd-1处，碰到1指针后移
        int n = (int)A.size();
        int zeroEnd = -1, twoBegin = n, i = 0;
        while(i < twoBegin){
            if(A[i] == 0 && i != ++zeroEnd)
                swap(A[zeroEnd], A[i]);
            else if(A[i] == 2 && i != --twoBegin)
                swap(A[twoBegin], A[i]);
            else
                i++;
        }
    }
};

思路：
1. 计数排序
因为范围已知，而且范围巨小，所以计数排序也可以，不过要计数要扫描一次，输出的时候还要扫描一次
class Solution {
public:
    void sortColors(vector<int> &A) {
        const int COLORNUM = 3;
        int counts[COLORNUM] = { 0 }; // 记录每个颜色出现的次数
        for (int i = 0; i < n; i++)
            counts[A[i]]++;
        for (int i = 0, index = 0; i < COLORNUM; i++)
            for (int j = 0; j < counts[i]; j++)
                A[index++] = i;
    }
};

2. 双指针
左边的指针red跟踪red，右边的指针blue跟踪blue
用cur指针从左边向右边扫描，如果碰到red就换到左边，如果碰到blue就换到右边
如果即不是red也不是blue，cur就往后移动
class Solution {
public:
    void sortColors(vector<int> &A) {
        int red = 0, blue = n - 1, cur = 0;
        while(cur <= blue){
            if(A[cur] == 0) swap(A[cur++], A[red++]);
            else if(A[cur] == 2)swap(A[cur], A[blue--]);
            else cur++;
        }
    }
};

3.用patition函数 equal_to函数和bind1st or bind2nd
class Solution {
public:
    void sortColors(int A[], int n) {
        partition(partition(A, A + n, bind1st(equal_to<int>(), 0)), A + n,
                    bind1st(equal_to<int>(), 1));
    }
};
or
class Solution {
public:
    void sortColors(int A[], int n) {
        partition(partition(A, A + n, bind2nd(equal_to<int>(), 0)), A + n,
                    bind2nd(equal_to<int>(), 1));
    }
};

4.
重新实现partition(), 这里C++11的patition使用的是前向迭代器, 而C++98使用的是双向迭代器
ForwardIterator是前向迭代器模板，pred是函数模板，Unary是指只接受一个参数，predicate是指
这个函数是用来预测的，返回bool类型，可以看出，patition的作用是凡是pred返回true的元素一律
交换到容器前半部分，返回的位置是后半部分的第一个元素，而不是前半部分的最后一个元素

class Solution {
public:
    void sortColors(int A[], int n) {
        partition(partition(A, A + n, bind1st(equal_to<int>(), 0)), A + n,
        bind1st(equal_to<int>(), 1));
    }
    private:
    template<typename ForwardIterator, typename UnaryPredicate>
    ForwardIterator partition(ForwardIterator first, ForwardIterator last,UnaryPredicate pred){
        auto pos = first;
        for (; first != last; ++first)
            if (pred(*first))
                swap(*first, *pos++);
        return pos;
    }
};