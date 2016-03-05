// [LeetCode 5] Longest Palindromic Substring
// Given a string S, find the longest palindromic substring in S. 
// You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.

// 分析:
// 1. Naive Approach
// Naively, we can simply examine every substring and check if it is palindromic. The time complexity is O(n^3).

// 2. Dynamic Programming
// Let s be the input string, i and j are two indices of the string. 
// Define a 2-dimension array "table" and let table[i][j] denote whether a substring from i to j is palindrome.

// 分析：
// 定义bool isPal[i][j]表示s[i:j]是否为回文，isPal[i][j] = true需要同时满足两个条件: 
// 1. s[i] ==s[j]
// 2. i+1>j-1（i, j之间只差一个元素） 或 isPal[i+1][j-1] == true (即s[i+1 : j-1]是回文)

string longest_pal_substr(string s){
	int n = s.size();
	vector<vector<bool>> table(n, vector<bool>(n));
	for(int i = 0; i < n; ++i){
		table[i][i] = 1;
	}

	string longest_str;
	// two consecutive same letter is a palimdrome
	for(int i = 1; i < n; ++i){
		if(s[i] == s[i - 1]){
			table[i - 1][i] = 1;
			longest_str = s.sub_str(i - 1, i);
		}
	}

}

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if(n <= 1) return s;
        int start = 0, maxLen = 1;
        bool isPal[1000][1000] = {false};
        // vector<vector<bool>> isPal(n, vector<bool>(n));
        // for(int i = 0; i < n; ++i){
        // 	isPal[i][i] = true;
        // }

        for(int i = n-1; i>= 0; i--) {
            for(int j = i; j < n; j++) {
                if((i+1> j-1 || isPal[i+1][j-1]) && s[i]==s[j]) {
                    isPal[i][j] = true;
                    if(j-i+1>maxLen) {
                        maxLen = j - i + 1;
                        start = i;
                    }
                }
            }
        }
        return s.substr(start, maxLen);
    }
};


Assume for simplicity that the palindrome is a length that is an odd number. Also, we treat a single character as a palindrome of length 1.
Runtime:
Worst-Case: O(N^2)
Best-Case: O(N)
The worst case is achieved when the string is a single repeated character because every substring is a palindrome.
The best case is achieved when the string contains no palindromes.
Typically if a string only contains a single palindrome (the fewer the better), the closer to O(N) it will run. 
This is because every time it checks a position in the string, it checks the character before and after that position, 
and if they don't match then it stops looking for the palindrome. Positions in the string can be discarded after 
only one lookup if that position doesn't have a palindrome, so if there are no palindromes you only do N comparisons.


分析：
常规的求解方法有2种：动态规划法，中心扩展判断法，这2种算法都是O(n^2)的时间复杂度。
动态规划法
      假设dp[i][j]的值为true，表示字符串s中下标从 i 到 j 的字符组成的子串是回文串。那么可以推出：
    dp[i][j] = dp[i + 1][j - 1] && s[i] == s[j]。
    这是一般的情况，由于需要依靠i+1, j-1，所以有可能 i + 1 = j - 1, i + 1 = (j - 1) -1，因此需要求出基准情况才能套用以上的公式：
    a. i + 1 = j - 1，即回文长度为1(奇数)时，dp[i][i] = true;
    b. i + 1 = (j - 1) -1，即回文长度为2(偶数)时，dp[i][i + 1] = （s[i] == s[i + 1]）。
    有了以上分析就可以写出代码了。需要注意的是动态规划需要额外的O(n^2)的空间。(内存可能超过要求)
class Solution {
public:
    string longestPalindrome(string s) {
        size_t n = s.length();
        bool **dp = new bool*[n];
        for (size_t i = 0; i < n; ++i){
            dp[i] = new bool[n];
        }
        vector<vector<bool>> dp(n, vector<bool>(n));
                
        //为基准情况赋值, len = 1 和 len = 2
        int startPos = 0;
        int max = 1;
        for (size_t i = 0; i < n; ++i){
            dp[i][i] = true;
            if (i + 1 < n){
                if (s[i] == s[i+1]){
                    dp[i][i+1] = true;
                    startPos = i;
                    max = 2;
                }
                else dp[i][i+1] = false;
            }
        }
        
        //动规求解,前面已求len = 1, len = 2的情况
        for (int len = 3; len <= n; ++len){
            for (int i = 0; i < n - len + 1; ++i){ // i 表示palindrome的begin, j表示end
                int j = i + len - 1;
                if (dp[i+1][j-1] && s[i] == s[j]){
                    dp[i][j] = true;
                    int curLen = j - i + 1;
                    if (curLen > max){
                        startPos = i;
                        max = curLen;
                    }
                }
                else dp[i][j] = false;
            }
        }
        
        //释放二维数组
        for (size_t i = 0; i < n; ++i)
           delete[] dp[i];
        
        delete[] dp;        
        return s.substr(startPos, max);
    }

};


 2. 中心扩展法
      因为回文字符串是以中心轴对称的，所以如果我们从下标 i 出发，用2个指针向 i 的两边扩展判断是否相等，那么只需要对0到
n-1的下标都做此操作，就可以求出最长的回文子串。但需要注意的是，回文字符串有奇偶对称之分，即"abcba"与"abba"2种类型，
因此需要在代码编写时都做判断。
     设函数int Palindromic (string &s, int i ,int j) 是求由下标 i 和 j 向两边扩展的回文串的长度，那么对0至n-1的下标，调用2次此函数：
     int lenOdd =  Palindromic( str, i, i ) 和 int lenEven = Palindromic (str , i , j )，即可求得以i 下标为奇回文和偶回文的子串长度。
     接下来以lenOdd和lenEven中的最大值与当前最大值max比较即可。
     这个方法有一个好处是时间复杂度为O(n2)，且不需要使用额外的空间。

// 48 ms
class Solution {
public:

    string longestPalindrome(string s) {
       
        size_t n = s.length();
        int startPos = 0;
        int max = 1;
        for (int i = 0; i < n; ++i){
            int oddLen = 0, evenLen = 0, curLen;
            oddLen = Palindromic(s, i, i);
            if(i + 1 < n)
            evenLen = Palindromic(s, i, i+1);
            
            curLen = oddLen > evenLen? oddLen : evenLen;
            
            if (curLen > max){
                max = curLen;
                if (max & 0x1)
                  startPos = i - max / 2;
                else 
                  startPos = i - (max - 1) / 2;
            }
        }
        
        return s.substr(startPos, max);
    }
    
    int Palindromic(const string &str, int i, int j){
        size_t n = str.length();
        int curLen = 0;
        while (i >= 0 && j < n && str[i] == str[j]){
            --i;
            ++j;
        }
        curLen = j - i - 1;

        return curLen;
    }
};

// 96ms
class Solution {
public:
    string longestPalindrome(string s) {
        	int n = s.length();
        	// if (n == 0) return "";
        	// if (n == 1) return s;
            if(n <= 1) return s;
        	string longest = s.substr(0, 1); // since string is not empty, the palindrome has at least one char
        	for (int i = 0; i < n; i++) {

                // palindrome has "aba" style
        		string tmp = longestpal_at_pos(s, i, i);
        		if (tmp.length() > longest.length()) {
        			longest = tmp;
        		}
         
                // palindrome has "abba" style
        		tmp = longestpal_at_pos(s, i, i + 1);
        		if (tmp.length() > longest.length()) {
        			longest = tmp;
        		}
        	}
         
        	return longest;
    }

    // Given a center, either one char or two char, 
    // Find longest palindrome
    string longestpal_at_pos(string s, int begin, int end) {
    	while (begin >= 0 && end <= (int)s.length() - 1 && s[begin] == s[end]) {
    		begin--;
    		end++;
    	}
    	return s.substr(begin + 1, end - begin - 1);
    }
};

// Use Manacer's algorithm to find them in O(n)
// 12ms, beats 72.64%
// http://articles.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
// https://www.quora.com/How-can-we-find-the-number-of-palindromic-substrings-in-a-string-in-linear-time
class Solution {
public:
    string longestPalindrome(string& s) {
            string T = preProcess(s);
            int n = T.length();
            vector<int> P(n);
            int C = 0, R = 0;
            for (int i = 1; i < n - 1; ++i) {
                int i_mirror = 2*C-i; // equals to i' = C - (i-C)

                P[i] = (R > i) ? min(R - i, P[i_mirror]) : 0;

                // Attempt to expand palindrome centered at i
                while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                    ++P[i];
                }

                // If palindrome centered at i expand past R,
                // adjust center based on expanded palindrome.
                if (i + P[i] > R) {
                    C = i;
                    R = i + P[i];
                }
            }

            // Find the maximum element in P.
            int max_len = 0, center_index = 0;
            for (int i = 1; i < n - 1; ++i) {
                if (P[i] > max_len) {
                    max_len = P[i];
                    center_index = i;
                }
            }

            return s.substr((center_index - 1 - max_len) / 2, max_len);
        }
    private:
        string preProcess(string s) {
            int n = s.length();
            if (n == 0) {
                return "^$";
            }
            string ret = "^";
            for (int i = 0; i < n; i++)
                ret += "#" + s.substr(i, 1);

            ret += "#$";
            return ret;
        }
};