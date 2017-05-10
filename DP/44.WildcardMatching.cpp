[LeetCode 44] Wildcard Matching
Implement wildcard pattern matching with support for '.' and '*'.
'.' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → false

Difficult: Hard

It seems that some readers are confused about why the regex pattern ".*" matches the string"ab". ".*" means repeat the preceding element 0 or more times.
Here, the "preceding" element is the dot character in the pattern, which can match any characters.
Therefore, the regex pattern".*" allows the dot to be repeated any number of times, which matches any string (even an empty string).
Think carefully how you would do matching of '*'.Please note that '*' in regular expression is different from wildcard matching, as we match the previous
character 0 or more times. But, how many times? If you are stuck, recursion is your friend.

// Analysis:
// Generally, in the while loop(s not end):
/*
a.  if p is *: try to store * position of p and s, also move p+1 only. try match.
    (if match fail, such as p end but s not, We'll go back here)
b.  if p is ? or characters match: go further p++, s++;
c.  if(first two fail, match fail. if has a star before):
    p go back (remains), s position+1(each time +1 till s end), try again.
d.  if all above fail, return false;

after the while loop, s must end, p may not end.
only possible true condition is: if (p has only '*' remaining)
*/

参考：http://blog.csdn.net/linhuanmars/article/details/21145563

注意：这里的a*表示a可以重复0次或者多次。

解法1： brute force

分两种情况：
(1)p[j+1]不是'*'。情况比较简单，只要判断当前s的i和p的j上的字符是否一样（如果有p在j上的字符是'.',也是相同），如果不同，返回false，否则，递归下一层i+1，j+1;
(2)p[j+1]是'*'。那么此时看从 s[i] 开始的子串，有两种可能，
如果 s[i], s[i+1], ... s[i+k] 都等于 p[j]，这些都有可能是合适的匹配（可能匹配也可能不匹配），那么需要把它们分别与 p 中*之后的序列来比较，也即 is_match(p, p+2)
对于剩下的(i, j+2),(i+1, j+2),...,(i+k, j+2) 都要尝试（ j+2 是因为跳过当前和下一个'*'字符）。

解法2： dynamic programming
接下来我们考虑如何优化 brute force 算法，熟悉动态规划的朋友可能发现了，其实这个思路已经很接近动态规划了。
动态规划基本思想就是把我们计算过的历史信息记录下来，等到要用到的时候就直接使用，不用重新计算。
在这个题里面，假设我们维护一个布尔数组 res[i][j]，代表s的前i个字符和p的前j个字符是否匹配(注意这里res的维度是s.length()+1,p.length()+1)。
递推公式跟上面类似，分三种情况：
(1) p[j+1] 不是'*'。情况比较简单，只要判断如果当前s的i和p的j上的字符一样（如果有p在j上的字符是'.',也是相同），并且res[i][j]==true，则res[i+1][j+1]也为true，res[i+1][j+1]=false;
(2) p[j+1]是'*'，但是p[j]!='.'。那么只要以下条件有一个满足即可对res[i+1][j+1]赋值为true：
    1) res[i+1][j]为真（'*'只取前面字符一次）;
    2) res[i+1][j-1]为真（'*'前面字符一次都不取，也就是忽略这两个字符）;
    3) res[i][j+1] && s[i]==s[i-1] && s[i-1]==p[j-1](这种情况是相当于i从0到s.length()扫过来，如果p[j+1]对应的字符是‘*’那就意味着接下来的串就可以依次匹配下来，如果下面的字符一直重复，并且就是‘*’前面的那个字符）。
(3) p[j+1]是'*'，并且p[j]=='.'。因为".*"可以匹配任意字符串，所以在前面的res[i+1][j-1]或者res[i+1][j]中只要有i+1是true，那么剩下的res[i+1][j+1],res[i+2][j+1],...,res[s.length()][j+1]就都是true了。
这道题有个很重要的点，就是实现的时候外层循环应该是p, 然后待匹配串s内层循环扫过来。代码如下：

两种算法中，动态规划的时间复杂度是O(n^2),空间复杂度也是O(n^2)。而brute force的递归算法最坏情况是指数量级的复杂度。

1. recursive

bool isMatch(const char *s, const char *p) {
    if (*p == 0) return *s == 0;
    if (*(p+1) != '*') {
        if (*s != 0 && (*p == *s || *p == '.')) return isMatch(s+1, p+1);
        else return false;
    } else  { // *s == *p
        while (*s != 0 && (*s == *p || *p == '.')) {
            if (isMatch(s, p+2)) return true;
            s++;
        }
        return (isMatch(s, p+2));
    }
}

bool isMatch(const char *s, const char *p) {
    assert(s && p);
    if (*p == '\0') return *s == '\0';

    // next char is not '*': must match current character
    if (*(p+1) != '*') {
        assert(*p != '*');
        return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch(s+1, p+1);
    }

    // next char is '*'
    while ((*p == *s) || (*p == '.' && *s != '\0')) {
        if (isMatch(s, p+2)) return true;
        s++;
    }
    return isMatch(s, p+2);
}

bool isMatch(const string& w, const string& s){
    int pos = 0;
    while(pos < w.size() && pos < s.size() && (w[pos] == '?' || w[pos] == s[pos])
        ++pos;
    if(pos == w.size()) return pos == s.size();
    if(w[pos] == '*'){
        for(int i = 0; pos + i < s.size(); ++i){
            if(isMatch(w.substr(pos + 1), s.substr(pos + i)));
                return true;
        }
    }
}

bool bitMatch(char *s, char *p){
    return( *s == *p || *p == '.' && *s != '\0');
}

bool isMatch(char* s, char* p) {
    if(*p == '\0') return (*s == '\0');
    if(*(p+1) == '*'){
        if(isMatch(s, p + 2)) return true;
        while(bitMatch(s, p)){
            if(isMatch(++s, p + 2))return true;
        }
    } else if(bitMatch(s, p))return isMatch(s + 1, p + 1);
    return false;
}


2. iterative
class Solution {
public:
    bool isMatch(string s, string p) {
        int pcur = 0;
        int scur = 0;
        int pstar = -1;
        int sstar = -1;
        while(scur < s.length()) {  // pcur < p.length() cannot present for *?
            if(pcur < p.length() && p[pcur]=='*') {
                pstar = pcur;
                sstar = scur;
                pcur++;
                continue;
            }
            if(pcur < p.length() && (p[pcur] == '?' || p[pcur] == s[scur])){
                pcur++;
                scur++;
                continue;
            }
            if(pstar != -1) {   // not matched, return last *, move s one step, try again
                sstar++;
                scur = sstar;
                pcur = pstar+1;
                continue;
            }
            return false;
        }
        while(pcur < p.length() && p[pcur] == '*') {
            pcur++; // eliminate last consecutive *s, if p not end
        }
        return pcur == p.length();    // true if p ends
    }
};

class Solution {
public:
    bool isMatch(const string& S, const string& P){
        const char *s = S.c_str();
        const char *p = P.c_str();
        return helper(s, p);
    }

    bool helper(const char *s, const char *p){
        const char* star = NULL;
        const char* ss = s;
        while(*s != '\0'){
            if((*p == '?') || (*p == *s)){
                s++;
                p++;
                continue;
            }
            if(*p == '*'){
                star = p++;
                ss = s;
                continue;
            }
            if(star != 0){
                p = star + 1;
                s = ++ss;
                continue;
            }
            return false;
        }
        while(*p == '*') p++;
        return *p == '\0';
    }
};

3. dp

bool isMatch(string s, string p) {
    if(s.length() == 0 && p.length() == 0)
        return true;
    if(p.length() == 0)
        return false;
    bool res[][] = new bool[s.length()+1][p.length()+1];
    res[0][0] = true;
    for(int j=0;j<p.length();j++) {
        if(p.[j]=='*') {
            if(j>0 && res[0][j-1]) res[0][j+1]=true;
            if(j<1) continue;
            if(p.[j-1]!='.') {
                for(int i=0;i<s.length();i++) {
                    if(res[i+1][j] || j>0 && res[i+1][j-1] || i>0 && j>0 && res[i][j+1]&&s.[i]==s.[i-1]&&s.[i-1]==p.[j-1])
                        res[i+1][j+1] = true;
                }
            } else {
                int i=0;
                while(j>0 && i<s.length() && !res[i+1][j-1] && !res[i+1][j])
                    i++;
                for(;i<s.length();i++) {
                    res[i+1][j+1] = true;
                }
            }
        }
        else {
            for(int i=0;i<s.length();i++) {
                if(s.[i)==p.[j) || p.[j)=='.')
                    res[i+1][j+1] = res[i][j];
            }
        }
    }
    return res[s.length()][p.length()];
}