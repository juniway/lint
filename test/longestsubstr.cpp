#include <iostream>
#include <string>
#include <memory.h>

using namespace std;

// class Solution{
// public:
//     int lengthOfLongestSubstring(string s){
//         int hash[128];
//         memset(hash, -1, 128 * sizeof(int));
// 
//         int maxlen = 0;
//         int start = 0;
//         for(int i = 0; i < (int)s.length(); ++i){
//             if(hash[s[i]] != -1){ // repeat
//                 if(maxlen < i - start) maxlen = i - start;
//                 for(int k = start; k < hash[s[i]]; ++k){
//                     hash[k] = -1; // reset
//                 }
//             if(hash[s[i]] + 1 > start)
//                 start = pos + 1;
//             }
//             hash[s[i]] = i;
//         }
//         maxlen = max((int)s.length() - start, maxlen);
// 
//         return maxlen;
//     }
// };

// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         int hash[256];
//         for(int i=0; i<256; i++) hash[i] = -1;
//         int start = 0, ans = 0;
//         int i;
//         for(i=0; i<s.size(); i++){
//             if( -1 != hash[s[i]] ){
//                 if(ans < i-start) ans = i-start;
//                 for(int j = start; j < hash[s[i]]; j++) 
//                     hash[j] = -1;
//                 if(hash[s[i]] + 1 > start )
//                     start = hash[s[i]] +1;
//             }
//             hash[s[i]] = i;
//         }
//         if(ans < i-start) ans = i-start;
//         return ans;
//     }
// };

class Solution {
public:
    int lengthOfLongestSubstring(string s) { // Longest Substring Without Repeating Characters
        int ht[256] = {0}; // 用ht[s[i]] 记录s[i]是否出现过
        int max_len = 0;
        int start = 0;

        for(int i = 0; i < s.length(); ++i){
            if(ht[s[i]] != 0){ // encounter a repeat
                max_len = max(max_len, i - start);

                // the loop update the new start point
                // and reset flag array
                //              0 1 2 3 4 5
                //              | | | | | |
                // for example, a c b c a b, when it comes to 2nd c,
                //              s     i
                // it update start(s) from 0 to 3, reset flag for all char before a[i]
                for(int k = start; k < i; ++k){
                    if(s[k] == s[i]){ // c == c: k == 1, i == 3
                        start = k + 1; // get the index: start == 2
                        break;
                    }
                    else{
                        ht[s[k]] = 0; // reset flag for elments before s[k]
                    }
                }
            }
            else{ // not a repeat
                ht[s[i]]++;
            }
        }
        max_len = max((int)s.length() - start, max_len);

        return max_len;
    }
};

int main() {
    string str = "aaa";
    Solution s ;
    cout << s.lengthOfLongestSubstring(str) << endl;
    return 0;
}

