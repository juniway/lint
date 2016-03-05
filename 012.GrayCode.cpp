/*
Medium Gray Code Show result 

34% Accepted
The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, find the sequence of gray code. A gray code sequence must begin with 0 and with cover all 2n integers.

Have you met this question in a real interview? Yes
Example
Given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note
For a given n, a gray code sequence is not uniquely defined.

[0,2,3,1] is also a valid gray code sequence according to the above definition.

Challenge
O(2n) time.
*/

class Solution {
public:
    /**
     * @param n a number
     * @return Gray code
     */
    vector<int> grayCode(int n) {
        // Write your code here
        vector<int> result;
        const size_t size = 1 << n; // 2^n 
        result.reserve(size);
        for (size_t i = 0; i < size; ++i){
            result.push_back(binary_to_gray(i));
        }
        return result;
    }
private:
    static unsigned int binary_to_gray(unsigned int n){
        return n ^ (n >> 1);
    }
};
