[LeetCode 44] Wildcard Matching
Implement wildcard pattern matching with support for '?' and '*'.
'?' Matches any single character.
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
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false

Difficult: Hard

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

class Solution {
public:
    bool isMatch(string s, string p) {
        int pcur = 0;
        int scur = 0;
        int pstar = -1;
        int sstar = -1;
        while(scur < s.length()) {  // pcur<p.length() cannot present for *?
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
            if((*p == '?')||(*p == *s)){
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