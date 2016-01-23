[LeetCode 169] Majority Element

Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
You may assume that the array is non-empty and the majority element always exist in the array.

class Solution {
public:
    int majorityElement(vector<int>& A) {
        int n = A.size();
        int current = A[0], count = 0;
        for(int i = 0; i < n; ++i){
            if(count == 0){
                current = A[i];
                count = 1;
            }
            else{
                count = (current == A[i])?++count:--count;
            }
        }
        return current;
    }
};