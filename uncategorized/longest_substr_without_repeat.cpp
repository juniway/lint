/*
Problem:
Given a string, find the length of the longest substring without repeating characters. 
For example, 
the longest substring without repeating characters for "abcabcbb" is "abc", 
which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/

start   k+1             i
a   	b   	c   	a       b   	c   	c   	b
|_______________|       |
	   max_len          |
	    |_______________|
	        i - start

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ht[256] = {0};
		int max_len = 0;
		int start = 0;

		for(int i = 0; i < s.length(); ++i){
			if(ht[s[i]] == 1){ // Find a repeat
				max_len = max(max_len, i - start);

				// update the new start point k + 1
				// k is the index of the first appearence of the repeating character
				// and reset flag array
				// for example, abccab, when it comes to 2nd c,
				// it update start from 0 to 3, reset flag for a,b
				for(int k = start; k < i; ++k){
					if(s[k] == s[i]){
						start = k + 1; // get the index
						break;
					}
					ht[s[k]] = 0; // reset flag for a, b
					
				}
			}
			else{
				ht[s[i]]++;
			}
		}

		max_len = max((int)s.length() - start, max_len);

		return max_len;
    }
};