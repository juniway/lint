// [LeetCode 179] Largest Number
// Given a list of non negative integers, arrange them such that they form the largest number.
// For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.
// Note: The result may be very large, so you need to return a string instead of an integer.

// 解题思路：
// 排序（Sort）
// 排序思路：对于两个备选数字a和b，如果str(a) + str(b) > str(b) + str(a)，则a在b之前，否则b在a之前
// 按照此原则对原数组从大到小排序即可, 时间复杂度O（nlogn）

// 注意一个特殊情况，就是组合后的字符串以0开始，需要把开始的0都去掉。

// 易错样例：
// Input:     [0,0]
// Output:    "00"
// Expected:  "0"


// Time:  O(nlogn)
// Space: O(1)

// 8ms, beats 53.3%
class Solution {
public:
    /**
     *@param A: A list of non negative integers
     *@return: A string
     */
    string largestNumber(const vector<int> &A) {
        // sort numbers
        
        vector<string> words;
        for(auto e: A){
            words.push_back(to_string(e));
        }
        sort(words.begin(), words.end(), [](const string& i, const string& j) {
            return i+j > j+i;
        });

        // combine the numbers
        string max_number;
        for (auto& i : words) {
            max_number.append(i);
        }

        // special case: start with zero (e.g. [0, 0])
		return max_number[0]=='0' ? "0" : ans;
    }
};

// 28ms, beats 13.59%
// class Solution {
// public:
//     string largestNumber(vector<int> &num) {
//         sort(num.begin(), num.end(), [](int a, int b){
//             return to_string(a)+to_string(b) > to_string(b)+to_string(a);
//         });
//         string ans;
//         for(int i=0; i<num.size(); i++){
//             ans += to_string(num[i]);
//         }
//         return ans[0]=='0' ? "0" : ans;
//     }
// };

// 优化：
// 虽然直接比较两个字符串在编写上非常简单，但是这样需要完整地转换两个字符串，
// 其实这在大多数情况是不需要的，大多数情况下只要比较前几个数字就可以判断出大小了

//3 change sort function, but still use return (s+t)>(t+s) 
//2 test auto & e :string vs auto e: string, 8ms, 93.3%, so no difference
//1 use simple custom sort function, works, 8ms, 93.3%

// 4ms, beats 93.8%
class Solution {
private:
static bool customStringSort(string s, string t){
    const char * i = s.c_str();
    const char * j = t.c_str();

    while(*i==*j){
        i++; j++;
    }
    if(*i =='\0' &&  *j == '\0') return 0;
    else if(*i == '\0') return (s+t)>(t+s);
    else if(*j == '\0') return (s+t)>(t+s);
    else return *i>*j;
}

public:
    string largestNumber(vector<int>& nums) {
        if(nums.empty()) return string();
        vector<string> words;
        for(auto e: nums)
            words.push_back(to_string(e));

        sort(words.begin(), words.end(), &Solution::customStringSort);

        if(stoi(words[0])==0)
        return "0";

        string res;
        for(auto e: words){
            res+=e;
        }
        return res;
    }
};