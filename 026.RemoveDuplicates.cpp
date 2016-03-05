[LeetCode 26] Remove Duplicates from Sorted Array
[LeetCode 19] Remove Nth Node From End of list
[LeetCode 27] Remove Element
[LeetCode 80] Remove Duplicates From Sorted Array II
[LeetCode 82] Remove Duplicates From Sorted List II
[LeetCode 83] Remove Duplicates From Sorted List 
[LeetCode 203] Remove Linked List Elements

Remove Duplicates from Sorted Array I
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
Do not allocate extra space for another array, you must do this in place with constant memory.
For example,
Given input array A = [1, 1, 2],
Your function should return length = 2, and A is now [1, 2].

Analysis:

1. 双指针, 一个指针 i 扫描数组, 一个指针 end 记录没有重复数字的新数组的尾部
(1) A[end]=A[i], A[i]为重复数字, 跳过
(2) A[end]!=A[i], 将A[i]放到A[end+1]位置, end++

A = [1, 1, 2]
     	^
     	end

class Solution {
public:
    /**
     * @param A: a list of integers
     * @return : return an integer
     */
    int removeDuplicates(vector<int> &A) {
        // write your code here
        const int n = A.size();
        if(n < 2) return n;
        
        int end = 1;

        // end denotes the end of the new array, 
        // it is the slot that next non-duplicate number will be put in
        // end denotes  the end of the duplicates
        // for example: A{1, 1, 2, 2, 3}
        // end = 1, 3
        for(int i = 1; i < n; ++i){
            if(A[end - 1] != A[i]){
                A[end++] = A[i];
            }
        }
        return end;
    }
};


2. 

// f1: Just using vector, sort + unique

sort(vec.begin(), vec.end());
iter = unique(vec.begin(), vec.end());
vec.erase(iter, vec.end());

len = distance(vec.begin(), iter);

// f2: Convert to set (using a constructor)
set<int> s( vec.begin(), vec.end() );
vec.assign( s.begin(), s.end());

// f3: Convert to set (manually)
set<int> s;
for (int i : vec) s.insert(i);
vec.assign( s.begin(), s.end() );

// f4: Convert to unordered_set (using a constructor)
unordered_set<int> s(vec.begin(), vec.end());
vec.assign(s.begin(), s.end());
sort(vec.begin(), vec.end());

// f5: Convert to unordered_set (manually)
unordered_set<int> s;
for (int i : vec) s.insert(i);
vec.assign(s.begin(), s.end());
sort(vec.begin(), vec.end());


I did the test with a vector of 100,000,000 ints chosen randomly in ranges [1,10], [1,1000], and [1,100000]

The results (in seconds, smaller is better):

range         f1       f2       f3       f4      f5
[1,10]      1.6821   7.6804   2.8232   6.2634  0.7980
[1,1000]    5.0773  13.3658   8.2235   7.6884  1.9861
[1,100000]  8.7955  32.1148  26.5485  13.3278  3.9822

/*
std::unique()
Remove consecutive duplicates in range

std::vector<int> myvector {10, 20, 20, 20, 30, 30, 20, 20, 10};
std::vector<int>::iterator it;
it = std::unique (myvector.begin(), myvector.end());   // 10 20 30 20 10 -  -  -  -
                                                       //                ^
myvector.resize( std::distance(myvector.begin(),it) ); // 10 20 30 20 10

*/


