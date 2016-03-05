#include <iostream>
#include <string>
#include <memory.h>

using namespace std;

class Solution{
public:
    int lengthOfLongestSubstring(string s){
        int hash[128];
        memset(hash, -1, 128 * sizeof(int));

        int maxlen = 0;
        int start = 0;
        for(int i = 0; i < (int)s.length(); ++i){
            if(hash[s[i]] != -1){ // repeat
                if(maxlen < i - start) maxlen = i - start;
                for(int k = start; k <= hash[s[i]]; ++k){
                    hash[s[k]] = -1; // reset
                }
                start = hash[s[i]] + 1;
                
            }
            else{
                hash[s[i]] = i;
            }
        }
        maxlen = max((int)s.length() - start, maxlen);

        return maxlen;
    }
};
int main() {
    string str = "aa";
    Solution s ;
    cout << s.lengthOfLongestSubstring(str) << endl;
    return 0;
}

