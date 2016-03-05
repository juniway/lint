// [LeetCode 17] Letter Combinations of a Phone Number
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        int n = digits.length();
    	if(n <= 0) return vector<string>();
    	vector<string> lettComb;
        string dict[] = {"", " ", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        string comb(n,'\0');
        findLettComb(digits, 0, dict, comb, lettComb);
        return lettComb;
    }
    
    void findLettComb(string &digits, int index, string dict[], string &comb, vector<string> &lettComb) {
        if(index == digits.size()) {
            lettComb.push_back(comb);
            return;
        }
        
        string lett = dict[digits[index] - '0'];
        for(int i = 0; i < lett.length(); i++) {
            comb[index] = lett[i];
            findLettComb(digits, index+1, dict, comb, lettComb);
        }
    }
};

