[LeetCode 03] Longest Substring Without Repeating Characters
/*

Given a string, find the length of the longest substring without
repeating characters. For example, the longest substring without
repeating letters for "abcabcbb" is "abc", which the length is 3.
For "bbbbb" the longest substring is "b", with the length of 1.

*/
// 12 ms
class Solution {
public:
    int lengthOfLongestSubstring(string s) { // Longest Substring Without Repeating Characters
        int ht[256] = {0}; // 用ht[s[i]] 记录s[i]是否出现过
        int max_len = 0;
        int start = 0;

        for(int i = 0; i < s.length(); ++i){
            if(ht[s[i]] != 0){ // when encounter a repeat
                max_len = max(max_len, i - start);

                // the loop update the new start point
                // and reset flag array
                //              0 1 2 3 4 5
                //              | | | | | |
                // for example, a c b c a b, when it comes to 2nd c,
                //                    i
                // it update start from 0 to 3, reset flag for ht[a..]
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

// 16ms
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        vector<int> bitmap(128, -1); // 用 bitmap[s[i]] 存s[i]在string中的位置
        int res = 0;
        int start = 0, lastStart = 0;
        for(int i = 0; i < n; i++){
            if(bitmap[s[i]] != -1){ // 在 bitmap 中发现s[i]已经出现过(当前位置是i)
                res = max(res, i - start);
                lastStart = start;
                start = bitmap[s[i]] + 1;
                for(int j = lastStart; j < bitmap[s[i]]; j++) // 从start点遍历到s[i]第一次出现的位置,然后把这位置之前出现的字符都重置
                    bitmap[s[j]] = -1;
            }
            bitmap[s[i]] = i;
        }
        res = max(res, n - start); // 不要忘了最后的判断
        return res;
    }
};
// 60 ms
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> um;//um记录遍历过程中每个字符最后出现的位置
        int res = 0;
        int start = 0; //start记录当前不重复子串的起点，i是当前位置

        for(int i = 0; i < s.length(); ++i){
            if(um.find(s[i]) != um.end() && um[s[i]] >= start) //如果当前维护的不重复子串中出现了s[i]
                start = um[s[i]] + 1;   //更新start
            else  //如果当前维护的不重复子串中没有出现s[i]
                res = max(res, i - start + 1); //更新结果，取较大者

            um[s[i]] = i; //更新um
        }
        return res;
    }
};

算法时间复杂度O(n)，空间复杂度O(1)。因为ASCLL码字符个数128个，
这里用unorder_map打表记录每个字符在字符串中最后出现的位置，
unordered_map的空间消耗最大为128，所以时间复杂度是常数级的。
unordered_map的查找插入操作的时间复杂度都是O(1)，所以整个算法的时间度为O(n)。
需要注意的是，unordered_map是无序容器，在找是否出现重复字符的时候，
一定要在当前考察的子串的范围内查找，所以条件 && um[s[i]]  >= j不能漏。
当然这里也可以用一个128长度的数组替换unordered_map，
好处是数组时有序的。见以下代码：

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int hs[128];
        int res=0,i=0,j=0;
        memset(hs,-1,128*sizeof(int));

        while(i<s.size()){
            if( hs[s[i]-0]>=j )
                j=hs[s[i]-0]+1;
            else
                res=max(res,i-j+1);

            hs[s[i]-0]=i;
            i++;
        }
        return res;
    }
};