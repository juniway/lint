/*
Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.

Have you met this question in a real interview? Yes
Example
Given [1,2,3] which represents 123, return [1,2,4].

Given [9,9,9] which represents 999, return [1,0,0,0].

*/

class Solution {
public:
    /**
     * @param digits a number represented as an array of digits
     * @return the result
     */
    vector<int> plusOne(vector<int> &digits) { 
        add(digits, 1);
        return digits;
    }
private:
    // 0 <= digit <= 9 
    void add(vector<int> &digits, int digit) {
        int c = digit; // carry, 进位
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) { 
            *it += c;
            c = *it / 10;
            *it %= 10;
        }
        if (c > 0) 
        digits.insert(digits.begin(), 1); 
        
    }
};
